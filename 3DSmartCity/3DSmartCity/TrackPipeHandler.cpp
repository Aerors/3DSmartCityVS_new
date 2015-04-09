#include "StdAfx.h"
#include "TrackPipeHandler.h"
#include "DBConnection.h"
#include "HighLightVisitor.h"
#include "makeSql.h"
#include "HighLightVisitor.h"
#include "ColorGradient.h"

TrackPipeHandler::TrackPipeHandler(void)
{
}


TrackPipeHandler::~TrackPipeHandler(void)
{
}



TrackPipeHandler::TrackPipeHandler(CTrackPipeDialog** ppTrackDlg,osgViewer::Viewer* mViewer)
{
	this->ppTrackDlg = ppTrackDlg;
	this->mViewer = mViewer;
}


bool TrackPipeHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	if((*ppTrackDlg)->IsWindowVisible())
	{
		switch(ea.getEventType())
		{
		case (osgGA::GUIEventAdapter::DOUBLECLICK):
			{
				osg::Vec3d m_TempPoint1;
				//const osgEarth::SpatialReference* m_pGeoSRS = mapNode->getTerrain()->getSRS();

				Pick(ea.getX(),ea.getY());
			}
		}
		return true;
	}
	return false;
}


void TrackPipeHandler::Pick(float x,float y )
{
	osgUtil::LineSegmentIntersector::Intersections intersection;
	//x , y 坐标值，intersection存放与法线相交的节点以及相交的节点路径等相关信息的列表
	if (mViewer->computeIntersections(x,y,intersection))//使用computeIntersections计算当前场景中单击到了那些模型，结果存放在结果集内
	{
		
		//使用迭代器取出这些模型，取出的结果是一个NodePath类对象，遍历该NodePath对象可以找到是否单击到了目标节点
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter=intersection.begin();hiter!=intersection.end();++hiter)
		{
			std::cout<<"scan  the  computeIntersections"<<std::endl;
			std::cout<<intersection.size();
			if (!hiter->nodePath.empty())
			{
				const osg::NodePath& np = hiter->nodePath;
				for (int i = np.size()-1;i>=0;--i)
				{
					osg::Node* nd = dynamic_cast<osg::Node*>(np[i]);
					if (nd)
					{
						if (nd->getName().find("ysgline_new") == 0)
						{
							osg::Geode* tmp = dynamic_cast<osg::Geode*>(nd);
							if(tmp)
							{
								osg::Vec4f color,colorEnd;
								osg::Geometry* tmpGeom = dynamic_cast<osg::Geometry*>(tmp->getDrawable(0));
								if(tmpGeom)
								{
									osg::Vec4Array* tmpColorArray = dynamic_cast<osg::Vec4Array*>(tmpGeom->getColorArray());
									if(tmpColorArray)
									{
										COLORREF cref = (*ppTrackDlg)->mColorPicker.GetColor();
										BYTE r = GetRValue(cref);
										BYTE g = GetGValue(cref);
										BYTE b = GetBValue(cref);
										color.set(r/255,g/255,b/255,1);

										osg::Vec4Array::iterator iter = tmpColorArray->begin();
										for(iter; iter!=tmpColorArray->end(); iter++)
										{
											iter->set(r/255,g/255,b/255,0.5);
											
										}
									}
								}

								DBConnection reader;
								makeSql ms;
								reader.ConnectToDB("localhost","5432","HRBPipe","postgres","123456");
								string sql = ms.flowDirectionSql(nd->getName());
								PGresult* res = reader.ExecSQL(const_cast<char*>(sql.c_str()));
								
								int field_num=PQnfields(res);
								int tuple_num=PQntuples(res);
								float* fbzms = new float[tuple_num];
								
								//
								{
									CString cs;
									cs.Format("共%d条管线！",tuple_num);
									(*ppTrackDlg)->mEdit.SetWindowTextA(cs);
								}

								//初始化list
								{
									(*ppTrackDlg)->m_List.DeleteAllItems();
									for(int j=0;j<field_num;++j)
									{
										(*ppTrackDlg)->m_List.InsertColumn(j,PQfname(res,j), LVCFMT_LEFT, 80);
									}

									for(int j=0;j<tuple_num;++j)
									{
										char* s = PQgetvalue(res,j,0);
										int nRow = (*ppTrackDlg)->m_List.InsertItem(j, s);//插入行

										for(int k=1;k<field_num;++k)
										{
											char* t = PQgetvalue(res,j,k);
											(*ppTrackDlg)->m_List.SetItemText(j, k, t);//设置数据

											if(1==k)
											{
												char* s = PQfname(res,k);
												//ASSERT(PQfname(res,k) == "标识码");
												fbzms[j] = atof(t);//查询到的标识码
											}

										}
									}
								}


								//绘制整条流向管线
								{
									for(std::vector<std::string>::iterator it=oldBzms.begin();it!=oldBzms.end();it++)
									{
										HighLightVisitor hl(*it,false);
										mViewer->getSceneData()->accept(hl);
									}
									oldBzms.erase(oldBzms.begin(),oldBzms.end());
									ASSERT(oldBzms.empty());

									/*ColorGradient g(color,colorEnd,tuple_num);*/
									ColorGradient g(color,tuple_num);
									osg::Vec4f* colors = g.getColorArray();
									for(int i=0;i<tuple_num;i++)
									{
										string s;
										ostringstream buf;
										buf<<"ysgline_new "<<fbzms[i];
										s = buf.str();
										HighLightVisitor hl(s,true,colors[i]);
										mViewer->getSceneData()->accept(hl);

										oldBzms.push_back(s);
									}
								}
								tmpGeom->dirtyDisplayList();
								
							}
							return;
						}
					}
				}
			}
		}
	}
}