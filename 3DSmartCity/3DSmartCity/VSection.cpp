#include "StdAfx.h"
#include "VSection.h"


VSection::VSection(MapNode* mapNode,osgViewer::Viewer* viewer,bool * isStart)
{	
	this->mapNode=mapNode;
	this->viewer=viewer;
	this->isStart=isStart;
	this->sectionDlg=new VSectionDlg;
	sectionDlg->Create(IDD_VSECTION);
	highLight=new CHighLight;
	DBclass=new DBConnection();
	DBclass->ConnectToDB(conn,"localhost","5432","HRBPipe","postgres","123456");
}


VSection::~VSection(void)
{
}


bool VSection::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	osg::Vec4 color=osg::Vec4(1.0,1.0,0.0,0.8);
	if(*isStart)
	{	
		if(ea.getEventType()==osgGA::GUIEventAdapter::DOUBLECLICK)
		{
			osgUtil::LineSegmentIntersector::Intersections intersection;
			highLight->setHighLight(findPipe(ea.getX(),ea.getY(),intersection),color);
			*isStart=false;
			return true;
		}
	}	
	return false;
}

osg::NodeList VSection::findPipe(double x, double y,osgUtil::LineSegmentIntersector::Intersections intersection)
{
	osg::NodeList nodes;
	int *row_num=new int(0);
	//osgUtil::LineSegmentIntersector::Intersections intersection;
	osg::Geode* tmp;

	char *strTmp; 
	char *startDepth, *endDepth, *startElevation,*endElevation;
	double sdepth,edepth,sele,eele;
	double sgele,egele;//start depth, line elevation, ground elevation;

	//���listcontrol;
	sectionDlg->m_List.DeleteAllItems();
	sectionDlg->m_List.SetRedraw(false);
	//���charCtrl;
	sectionDlg->m_ChartCtrl.RemoveAllSeries();
	sectionDlg->m_ChartCtrl.EnableRefresh(false);

	//����һ������ ����һ������
	//����
	CChartLineSerie *pGroundSeriel=sectionDlg->m_ChartCtrl.CreateLineSerie();
	pGroundSeriel->SetSeriesOrdering(poNoOrdering);//����Ϊ����
	pGroundSeriel->SetName("ground");

	//����
	CChartLineSerie *pLineSeriel=sectionDlg->m_ChartCtrl.CreateLineSerie();
	pLineSeriel->SetSeriesOrdering(poNoOrdering);//����Ϊ����
	pLineSeriel->SetName("line");
	//���ߵ�
	CChartPointsSerie *pPointSeriel=sectionDlg->m_ChartCtrl.CreatePointsSerie();
	pPointSeriel->SetSeriesOrdering(poNoOrdering);//����Ϊ����	
	pPointSeriel->SetName("pipe");

	string line="ysgline_new";
	int len=line.length();
	string bzm;

	//delete
	int inti=0,intj=0,intk=0;
	bool breakFlag=false;
	//x , y ����ֵ��intersection����뷨���ཻ�Ľڵ��Լ��ཻ�Ľڵ�·���������Ϣ���б�
	if (viewer->computeIntersections(x,y,intersection))//ʹ��computeIntersections���㵱ǰ�����е���������Щģ�ͣ��������ڽ������
	{

		//ʹ�õ�����ȡ����Щģ�ͣ�ȡ���Ľ����һ��NodePath����󣬱�����NodePath��������ҵ��Ƿ񵥻�����Ŀ��ڵ�
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter=intersection.begin();hiter!=intersection.end();++hiter)
		{
			if (breakFlag) break;
			inti++;
			if (!hiter->nodePath.empty())
			{
				const osg::NodePath& np = hiter->nodePath;
				for (int i = np.size()-1, intk=0;i>=0;--i)
				{
					if (breakFlag) break;
					intj++;
					intk++;
					
					osg::Node* nd = dynamic_cast<osg::Node*>(np[i]);
					if (nd)
					{
						if (nd->getName().find(line) == 0)
						{
							//MessageBox(NULL,_T(nd->getName().c_str()),"test",0);
							tmp = dynamic_cast<osg::Geode*>(nd);
							if (tmp)
							{	
								breakFlag=true;
								nodes.push_back(nd);								
								bzm=nd->getName().substr(len);
								string sql = "select line.��ʶ��,line.�ܾ�,line.����,line.�������,line.�յ�����, \
											 point1.����߳� as ���߳�,point2.����߳� as �յ�߳�,line.�������,line.̽������ \
											 from ysgpoint_new as point1,ysgpoint_new as point2,(\
											 select * from ysgline_new where ��ʶ��='"
											 +trim(bzm)+
											 "' ) as line	where line.�����=point1.��̽��� and line.�յ���=point2.��̽���";
								res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),row_num);

								int field_num=PQnfields(res);

								for(int j=0;j<*row_num;++j)
								{
									strTmp = PQgetvalue(res,j,0);
									sectionDlg->m_List.InsertItem(j, strTmp);//������

									for(int k=1;k<field_num;++k)
									{
										char* strTmp = PQgetvalue(res,j,k);
										if (j>2 && j<7)
										{
											strTmp[8]='\0';
										}
										sectionDlg->m_List.SetItemText(j,k,strTmp);

										startDepth	=		PQgetvalue(res,j,3);
										endDepth	=		PQgetvalue(res,j,4);
										startElevation	=	PQgetvalue(res,j,5);
										endElevation	=	PQgetvalue(res,j,6);

										sdepth=atof(startDepth);
										edepth=atof(endDepth);
										sele=atof(startElevation);
										eele=atof(endElevation);

										sgele=sdepth+sele;
										egele=edepth+eele;

										pGroundSeriel->AddPoint(0,sgele);
										pGroundSeriel->AddPoint(1,egele);
										pLineSeriel->AddPoint(0,sele);
										pLineSeriel->AddPoint(1,eele);									
										pPointSeriel->AddPoint(0,sele);
										pPointSeriel->AddPoint(1,eele);

									}

								}

							break;	
							}
						}
					}
				}
			}
		}
	}

	sectionDlg->m_ChartCtrl.GetLegend()->SetVisible(true);
	sectionDlg->m_ChartCtrl.EnableRefresh(true);
	sectionDlg->m_List.SetRedraw(true);
	sectionDlg->ShowWindow(SW_NORMAL);

	return nodes;

}