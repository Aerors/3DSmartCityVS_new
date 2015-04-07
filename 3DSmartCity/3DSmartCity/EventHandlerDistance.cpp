#include "StdAfx.h"
#include "EventHandlerDistance.h"
#include "3DSmartCityView.h"
#include "afxdialogex.h"
#include<stdlib.h>
#include <string>
using namespace osgEarth::Symbology;
using namespace osgEarth::Annotation;
//构造函数
CEventHandlerDistance::CEventHandlerDistance(osg::ref_ptr<osgEarth::MapNode> mapNode1,CDisDlg ** addlg,bool *isWindowClose)
{   
	this->isWindowClose1=isWindowClose;
	this->DisDlgShow=addlg;
	this->mapNode1=mapNode1;
	this->mapNode3=mapNode1;
	isPickWorld=false;//默认不点选;
	isTestJu=false;
	jieduan=0;
	Jilu=0;
	vertex=new osg::Vec3Array;
	lineStrip=new osg::Geode;
	lineStrip1=new osg::Geode;
	myRoot = new osg::Group;
	myRoot1 = new osg::Group;
	wenben=new osg::Geode;
	StartandEnd=new osg::Group;
}
//析构函数
CEventHandlerDistance::~CEventHandlerDistance(void)
{
	
}
std::string noteName;
bool CEventHandlerDistance::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::Viewer *viewer=dynamic_cast<osgViewer::Viewer*>(&aa);
	const osgEarth::SpatialReference *m_pGeoSRS =mapNode1->getTerrain()->getSRS();//获取坐标系
	double distwo;
	if(isTestJu&&viewer)
	{
		switch(ea.getEventType())
		{
        //处理鼠标左键双击事件
		case (osgGA::GUIEventAdapter::DOUBLECLICK):
		{
				
        //双击求交点;
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
		if(jieduan==0)
		{
			jieduan=1;
			vertex->push_back(point);//起点;
			startPoint.set(point.x(),point.y(),point.z());		
			osgEarth::Symbology::Style pin;		
			noteName="Start Point";
			GeoPoint TempStart;
			TempStart.fromWorld(m_pGeoSRS,startPoint);
			pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
		    StartandEnd->addChild(new osgEarth::Annotation::PlaceNode(mapNode3,TempStart,noteName,pin));
			viewer->getSceneData()->asGroup()->addChild(StartandEnd);		
		}
		else if(jieduan==1)
		{
			
			endPoint.set(point.x(),point.y(),point.z());				
			jieduan=2;
			osgEarth::GeoPoint  startlla;
			osgEarth::GeoPoint  endlla;
			//将XYZ转化成经纬度			
			startlla.fromWorld(m_pGeoSRS,startPoint);
			endlla.fromWorld(m_pGeoSRS,endPoint);
			int dis=GetDis(startPoint,endPoint);

			double deltalla=(endlla.y()-startlla.y())/(float)dis;
			double deltalon=(endlla.x()-startlla.x())/(float)dis;		
			osg::ref_ptr<osg::Vec4Array> color=new osg::Vec4Array;
			color->push_back(osg::Vec4(1.0,1.0,0.0,1.0));
			//插值,划的线依据海拔高度
			/*for(int i=1;i<dis;i=i++)
			{

				double templat=startlla.y()+i*deltalla;
				double templon=startlla.x()+i*deltalon;
				osgEarth::GeoPoint lowpoint,heightpoint;
				
				lowpoint.set(m_pGeoSRS,templon,templat,-1000,osgEarth::AltitudeMode::ALTMODE_ABSOLUTE);
				heightpoint.set(m_pGeoSRS,templon,templat,10000,osgEarth::AltitudeMode::ALTMODE_ABSOLUTE);
				osg::Vec3d lowpoint1;
				osg::Vec3d heightpoint1;

				lowpoint.toWorld(lowpoint1);
				heightpoint.toWorld(heightpoint1);

				osg::Vec3d interSec= IntersectPoint(lowpoint1,heightpoint1,mapNode1->getTerrainEngine());

				if(interSec==osg::Vec3d(0,0,0))
				{
					continue;
				}
				else
				{
					osgEarth::GeoPoint temp,temp1;
					
					temp.fromWorld(m_pGeoSRS,interSec);

					temp1.set(m_pGeoSRS,temp.x(),temp.y(),temp.z()+10,osgEarth::AltitudeMode::ALTMODE_RELATIVE);
					temp1.toWorld(interSec);
					vertex->push_back(interSec);
					color->push_back(osg::Vec4(1.0,1.0,0.0,1.0));
				}

				osg::ref_ptr<osg::Geometry> geom=new osg::Geometry;
				lineStrip->addDrawable(geom);
				geom->setVertexArray(vertex);
				geom->setColorArray(color);
				geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
				geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,vertex->size()));
				geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0),osg::StateAttribute::ON);
				geom->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
				viewer->getSceneData()->asGroup()->addChild(lineStrip);

				
			}*/
			//差值划线结束

			//单划线，两点之间划线
			vertex->push_back(endPoint);
			osg::ref_ptr<osg::Geometry> geom=new osg::Geometry;
			lineStrip->addDrawable(geom);
			geom->setVertexArray(vertex);
			geom->setColorArray(color);
			geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,vertex->size()));
			geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0),osg::StateAttribute::ON);
			geom->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
			//viewer->getSceneData()->asGroup()->addChild(lineStrip);
			myRoot->addChild(lineStrip);
			viewer->getSceneData()->asGroup()->addChild(myRoot);
			//两点之间划线结束;
			distwo=GetDis1(vertex);
			distwo=(double)(int)((distwo)*100)/100;
			char buffer[20];
			sprintf_s(buffer,"%f",distwo);
			CStringA str=buffer;
			CStringA strname="测量的距离为：";
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
			osgEarth::Symbology::Style pin;		
			noteName="\nEnd Point";
			GeoPoint TempStart;
			TempStart.fromWorld(m_pGeoSRS,endPoint);
			pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
			StartandEnd->addChild(new osgEarth::Annotation::PlaceNode(mapNode3,TempStart,noteName,pin));
			viewer->getSceneData()->asGroup()->addChild(StartandEnd);

		}
		else if(jieduan=2)
		{
			jieduan=1;
			//清空之前;						
			if(viewer->getSceneData()->asGroup()->containsNode(myRoot))
			{										
				viewer->getSceneData()->asGroup()->removeChild(myRoot);
				lineStrip=0;
				lineStrip=new osg::Geode;
				myRoot=0;
				myRoot=new osg::Group;
			}
			for(int i=0;i<=Jilu+20;i++)
			{									
				viewer->getSceneData()->asGroup()->removeChild(myRoot1);
				if(viewer->getSceneData()->asGroup()->containsNode(myRoot1)==false)
				{					
					myRoot1=0;
					myRoot1=new osg::Group;
					lineStrip1=0;
					lineStrip1=new osg::Geode;
				}

			}
			for(int i=0;i<Jilu+20;i++)
			{	

			viewer->getSceneData()->asGroup()->removeChild(StartandEnd);
			if(viewer->getSceneData()->asGroup()->containsNode(StartandEnd)==false)
			{				
				StartandEnd=0;
				StartandEnd=new osg::Group;
			}
			}
			vertex->clear();
			vertex->push_back(point);//起点
			startPoint.set(point.x(),point.y(),point.z());
			osgEarth::Symbology::Style pin;		
			noteName="Start Point";
			GeoPoint TempStart;
			TempStart.fromWorld(m_pGeoSRS,startPoint);
			pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
			StartandEnd->addChild(new osgEarth::Annotation::PlaceNode(mapNode3,TempStart,noteName,pin));
			viewer->getSceneData()->asGroup()->addChild(StartandEnd);	
			Jilu=0;
		}
		break;
		}
		//处理鼠标左键单击事件
		case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON):
		{
			if(jieduan==1)
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
			midPoint.set(point.x(),point.y(),point.z());
			vertex->push_back(midPoint);
			//添加中间点的距离
			distwo=GetDis1(vertex);
			distwo=(double)(int)((distwo)*100)/100;
			char buffer[20];
			sprintf_s(buffer,"%f",distwo);
			CStringA str=buffer;
			osgEarth::Symbology::Style pin;		
			noteName=str+"m";
			GeoPoint TempMid;
			TempMid.fromWorld(m_pGeoSRS,midPoint);
			pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
			StartandEnd->addChild(new osgEarth::Annotation::PlaceNode(mapNode3,TempMid,noteName,pin));
			viewer->getSceneData()->asGroup()->addChild(StartandEnd);
			//添加中间点距离结束
			midPoint.set(0,0,0);
			osg::ref_ptr<osg::Vec4Array> color=new osg::Vec4Array;
			color->push_back(osg::Vec4(1.0,1.0,0.0,1.0));
			osg::ref_ptr<osg::Geometry> geom=new osg::Geometry;
			lineStrip1->addDrawable(geom);			
			geom->setVertexArray(vertex);
			geom->setColorArray(color);
			geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,vertex->size()));
			geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0),osg::StateAttribute::ON);
			geom->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
			myRoot1->addChild(lineStrip1);
			viewer->getSceneData()->asGroup()->addChild(myRoot1);
			Jilu++;			
		}
		}
		}
		return true;
		}	
		  else 
		  {
			  if(viewer->getSceneData()->asGroup()->containsNode(myRoot))
			  {										
				  viewer->getSceneData()->asGroup()->removeChild(myRoot);
				  lineStrip=0;
				  lineStrip=new osg::Geode;
				  myRoot=0;
				  myRoot=new osg::Group;
			  }
			  for(int i=0;i<=Jilu+20;i++)
			  {									
				  viewer->getSceneData()->asGroup()->removeChild(myRoot1);
				  if(viewer->getSceneData()->asGroup()->containsNode(myRoot1)==false)
				  {					
					  myRoot1=0;
					  myRoot1=new osg::Group;
					  lineStrip1=0;
					  lineStrip1=new osg::Geode;
				  }
			  }
			  for(int i=0;i<Jilu+20;i++)
			  {	
				  viewer->getSceneData()->asGroup()->removeChild(StartandEnd);
				  if(viewer->getSceneData()->asGroup()->containsNode(StartandEnd)==false)
				  {				
					  StartandEnd=0;
					  StartandEnd=new osg::Group;
				  }
			  }
}
	return false;
}
//判断check选择框死否选中
void CEventHandlerDistance::isStartTest(bool isTest)
{
	isTestJu=isTest;
}
//计算两点间的距离
double CEventHandlerDistance::GetDis(osg::Vec3d from,osg::Vec3d to)
{
	return sqrt((to.x()-from.x())*(to.x()-from.x())+(to.y()-from.y())*(to.y()-from.y())+(to.z()-from.z())*(to.z()-from.z()));
}
//求交点
osg::Vec3d CEventHandlerDistance::IntersectPoint(osg::Vec3d XPosition,osg::Vec3d YPosition,osg::ref_ptr<osg::Node> Node)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	osg::ref_ptr<osgUtil::LineSegmentIntersector> ls=new osgUtil::LineSegmentIntersector(XPosition,YPosition);
	osg::ref_ptr<osgUtil::IntersectionVisitor> iv=new osgUtil::IntersectionVisitor(ls);
	if(Node)
	{
		Node->accept(*iv);		
	}
	if(ls->containsIntersections())
	{
		intersections=ls->getIntersections();
		return intersections.begin()->getWorldIntersectPoint();
	}
	return osg::Vec3d(0,0,0);
}
//求亮点间距离
double CEventHandlerDistance::GetDis1(osg::ref_ptr<osg::Vec3Array> vec)
{
	double dis=0;
	
	
	for(osg::Vec3Array::iterator iter=vec->begin();iter != vec->end();iter++)
	{
		osg::Vec3Array::iterator iter2=iter;
		iter2++;
		if(iter2==vec->end())
			break;
		else
		{
			dis=dis+GetDis(*iter,*iter2);
		}
	}

	return dis;

}

