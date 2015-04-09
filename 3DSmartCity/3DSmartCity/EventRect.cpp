#include "StdAfx.h"
#include "EventRect.h"
#include "3DSmartCityView.h"
#include <osgUtil/Tessellator>
#include<stdlib.h>
#include <string>
#include <osg/CullFace>
#include <osg/Depth>
#include <math.h>
#include <cmath>
CEventRect::CEventRect(osg::ref_ptr<osgEarth::MapNode> mapNode1,CDisDlg ** addlg)
{
	this->DisDlgShow=addlg;
	
	isStartTest1=false;
	firstdbc=0;
	polygon=new osg::Geode;
	xiaoqiu=new osg::Geode;
	this->mapNode1=mapNode1;
	vertexrect=new osg::Vec3Array;
	state=new osg::StateSet;
	geom=new osg::Geometry;
	RectLine=new osg::Geode;
	LineRoot=new osg::Group;
	jilu=0;
}
CEventRect::~CEventRect(void)
{

}
void CEventRect::isStartTestArea(bool isTest)
{
	isStartTest1=isTest;
	

}
bool CEventRect::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::Viewer *viewer=dynamic_cast<osgViewer::Viewer*>(&aa);
	const osgEarth::SpatialReference *m_pGeoSRS =mapNode1->getTerrain()->getSRS();
	if(isStartTest1&&viewer)
	{
		switch(ea.getEventType())
		{

			case (osgGA::GUIEventAdapter::DOUBLECLICK):
			{

					osg::Vec3d point=osg::Vec3(0,0,0);
					osgUtil::LineSegmentIntersector::Intersections intersections;
					if(viewer->computeIntersections(ea.getX(),ea.getY(),intersections))
					{
						point=intersections.begin()->getWorldIntersectPoint();//世界坐标XYZ
					
					}

					if(firstdbc==0)
					{
						firstdbc=1;
						
						beginpoint.set(point.x(),point.y(),point.z());
						vertexrect->push_back(beginpoint);//起点;
						xiaoqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(beginpoint,0.5)));

						if(viewer->getSceneData()->asGroup()->containsNode(xiaoqiu)==false)
						{
							viewer->getSceneData()->asGroup()->addChild(xiaoqiu);
						}

					}
					else if(firstdbc==1)
					{
						endpoint.set(point.x(),point.y(),point.z());
						xiaoqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(endpoint,0.5)));
						xiaoqiu->dirtyBound();

						if(viewer->getSceneData()->asGroup()->containsNode(xiaoqiu)==false)
						{
							viewer->getSceneData()->asGroup()->addChild(xiaoqiu);
						}
						firstdbc=2;
						//颜色
						
						//点
						vertexrect->push_back(endpoint);
						//法线

						//划多边形
						state->setMode(GL_BLEND,osg::StateAttribute::ON);  
						state->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);  
						state->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED );  
						//设置渲染优先级  
						state->setRenderBinDetails(101, "RenderBin");  
						osg::CullFace* cf = new osg::CullFace;  
						state->setAttributeAndModes(cf,osg::StateAttribute::OFF);  

						osg::ref_ptr<osg::Depth> depth = new osg::Depth;  
						depth->setFunction(osg::Depth::ALWAYS);  
						depth->setRange(0.0,0.0);     
						state->setAttributeAndModes(depth.get(),osg::StateAttribute::ON ); 


						geom->setStateSet(state);
						geom->setVertexArray(vertexrect);

						//颜色
						osg::Vec4Array* colors = new osg::Vec4Array;  
						osg::Vec4 color(1.0,1.0,0.0,1.0);  
						colors->push_back(color);  
						geom->setColorArray(colors);  
						geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);  
						geom->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON,0,vertexrect->size()));

						//法线
						osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;  
						geom->setNormalArray(normals.get());
						geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);  
						osg::Vec3 normal = osg::Z_AXIS;  
						normals->push_back(normal);
						osg::ref_ptr<osgUtil::Tessellator> tes = new osgUtil::Tessellator();  
						tes->setBoundaryOnly(false);  
						tes->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD); //设置环绕规则 
						tes->setTessellationType(osgUtil::Tessellator::TESS_TYPE_DRAWABLE);  
						tes->retessellatePolygons(*geom);//使用分格化 
						polygon->addDrawable(geom);
						viewer->getSceneData()->asGroup()->addChild(polygon);
						//计算面积
						float area;
						area=GetAera(vertexrect);
						

				
						area=(double)(int)((area)*100)/100;
						char buffer[20];
						sprintf_s(buffer,"%f",area);
						CStringA str=buffer;
						CStringA strname="测量的面积为：";
						if (!(*DisDlgShow)->IsWindowVisible())
						{
							if ((*DisDlgShow)==NULL)
							{
								(*DisDlgShow)=new CDisDlg();
								(*DisDlgShow)->Create(IDD_DisDlg);
								(*DisDlgShow)->initDlg(mLabels3,mapNode3);
							}		
							(*DisDlgShow)->ShowWindow(SW_NORMAL);
						}
						int  cx  =  GetSystemMetrics(  SM_CXSCREEN  );
						int  cy  =  GetSystemMetrics(  SM_CYSCREEN  ); 
						(*DisDlgShow)->MoveWindow(cx/2,cy/2,500,200,1);

						(*DisDlgShow)->m_dis=str;
						(*DisDlgShow)->m_name=strname;
						(*DisDlgShow)->SendMessage(WM_UPDATEDATA_DIS, false);		
					}
					else if(firstdbc==2)
					{
						firstdbc=1;


						if(viewer->getSceneData()->asGroup()->containsNode(polygon))
						{
							viewer->getSceneData()->asGroup()->removeChild(polygon);
							polygon=0;
							polygon=new osg::Geode;
							geom=0;
							geom=new osg::Geometry;
						}
						if(viewer->getSceneData()->asGroup()->containsNode(xiaoqiu))
						{
							viewer->getSceneData()->asGroup()->removeChild(xiaoqiu);
							xiaoqiu=0;
							xiaoqiu=new osg::Geode;
							geom=0;
							geom=new osg::Geometry;

						}	

						for(int i=0;i<=jilu+20;i++)
						{									
							//LineRoot->removeChild(i);
							
							viewer->getSceneData()->asGroup()->removeChild(LineRoot);
							//viewer->getSceneData()->asGroup()->removeChild(RectLine);
							//viewer->getSceneData()->asGroup()->removeChild(polygon);
							if(viewer->getSceneData()->asGroup()->containsNode(LineRoot)==false)
							{
							
							polygon=0;
							polygon=new osg::Geode;
							LineRoot=0;
							LineRoot=new osg::Group;
							RectLine=0;
							RectLine=new osg::Geode;
							}
													
						}
						vertexrect->clear();
						vertexrect->push_back(point);//起点
						beginpoint.set(point.x(),point.y(),point.z());
						xiaoqiu->addDrawable(new osg::ShapeDrawable(new osg::Sphere(beginpoint,1)));
						if(viewer->getSceneData()->asGroup()->containsNode(xiaoqiu)==false)
						{
							viewer->getSceneData()->asGroup()->addChild(xiaoqiu);
						}

					}
				break;
				
			}
			case (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON):
				{

					if(firstdbc==1)
					{			
						osg::Vec3d point=osg::Vec3(0,0,0);
						osgUtil::LineSegmentIntersector::Intersections intersections;
						if(viewer->computeIntersections(ea.getX(),ea.getY(),intersections))
						{
							point=intersections.begin()->getWorldIntersectPoint();//世界坐标XYZ
							osgEarth::GeoPoint temp,temp1;
							temp.fromWorld(m_pGeoSRS,point);

							temp1.set(m_pGeoSRS,temp.x(),temp.y(),temp.z()+10,osgEarth::AltitudeMode::ALTMODE_RELATIVE);
							temp1.toWorld(point);
						}

						midpoint.set(point.x(),point.y(),point.z());
						//点
						vertexrect->push_back(midpoint);

						midpoint.set(0,0,0);


						osg::ref_ptr<osg::Vec4Array> color=new osg::Vec4Array;
						color->push_back(osg::Vec4(1.0,1.0,0.0,1.0));

						osg::ref_ptr<osg::Geometry> geomline=new osg::Geometry;
						
						RectLine->addDrawable(geomline.get());			
						geomline->setVertexArray(vertexrect);
						geomline->setColorArray(color);
						geomline->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
						geomline->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,vertexrect->size()));
						geomline->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0),osg::StateAttribute::ON);
						geomline->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
						LineRoot->addChild(RectLine.get());

						viewer->getSceneData()->asGroup()->addChild(LineRoot);
						
						jilu++;						
				}
				}
		}
		return true;
	}
	else
	{
		if(viewer->getSceneData()->asGroup()->containsNode(polygon))
		{
			viewer->getSceneData()->asGroup()->removeChild(polygon);
			polygon=0;
			polygon=new osg::Geode;
			geom=0;
			geom=new osg::Geometry;


		}
		if(viewer->getSceneData()->asGroup()->containsNode(xiaoqiu))
		{
			viewer->getSceneData()->asGroup()->removeChild(xiaoqiu);
			xiaoqiu=0;
			xiaoqiu=new osg::Geode;
			geom=0;
			geom=new osg::Geometry;

		}	

		for(int i=0;i<=jilu+20;i++)
		{									
			viewer->getSceneData()->asGroup()->removeChild(LineRoot);
			if(viewer->getSceneData()->asGroup()->containsNode(LineRoot)==false)
			{
				polygon=0;
				polygon=new osg::Geode;
				LineRoot=0;
				LineRoot=new osg::Group;
				RectLine=0;
				RectLine=new osg::Geode;
			}
		}
    }
	return false;
}

float CEventRect::LineInter(osg::Vec3d point1,osg::Vec3d point2)
{
	return 0.5*(point2.x()-point1.x())*(point2.y()+point1.y());
	//return sqrt(pow((point2.x()- point1.x()),2)+pow((point2.y()-point1.y()),2));
}

float CEventRect::GetAera(osg::ref_ptr<osg::Vec3Array> vetex)//计算不规则多边形面积
{
	if (vetex->size()== 0) return 0;   
	float area = 0;
		
	for (osg::Vec3Array::iterator iter=vetex->begin();iter<vetex->end()-1;++iter) 
	{   		
	   osg::Vec3Array::iterator iter2=iter;
	    iter2++;
	   if(iter2==vetex->end()-1)
		   break;	  
	   else
	   {
			area=area+LineInter(*iter,*iter2);
	   }		   
	}   
	osg::Vec3Array::iterator iter3=vetex->begin();
	osg::Vec3Array::iterator iter4=vetex->end()-1;
	area=area+ LineInter(*iter4,*iter3);
	
	return area >= 0 ? area : -area; 

}



