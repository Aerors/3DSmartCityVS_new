#include "StdAfx.h"
#include "HSpacing.h"


HSpacing::HSpacing(MapNode* _mapNode,osgViewer::Viewer* _viewer,bool *_isStart)
{
	mapNode=_mapNode;
	viewer=_viewer;
	isStart=_isStart;
	isFirstTime=true;

	mHSpacingDlg=new HSpacingDlg;
	mHSpacingDlg->Create(IDD_HSPACINGDLG);
	highLight=new CHighLight;
	DBclass=new DBConnection();
	DBclass->ConnectToDB(conn,"localhost","5432","HRBPipe","postgres","123456");

}


HSpacing::~HSpacing(void)
{
}

bool HSpacing::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	if (*isStart)
	{
		if (ea.getEventType()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			if (isFirstTime)
			{
				mHSpacingDlg->mList.DeleteAllItems();
				node1=pick(ea.getX(),ea.getY());
				bzm1=setValue(node1);
				if (bzm1!="-1") 
				{	
					isFirstTime=false;
					nodes.clear();
					nodes.push_back(node1);
					highLight->setHighLight(nodes,osg::Vec4(1.0,0.0,0.0,0.8));
				}
			} 
			else
			{	
				node2=pick(ea.getX(),ea.getY());
				bzm2=setValue(node2);
				if (bzm2!="-1")
				{
					nodes.push_back(node2);
					highLight->setHighLight(nodes,osg::Vec4(1.0,0.0,0.0,0.8));

					isFirstTime=true;
					computeHSpace(bzm1,bzm2);
					*isStart=false;					
					mHSpacingDlg->ShowWindow(SW_NORMAL);
				}
			}
			return true;
		}
	}
	return false;
}


Node *HSpacing::pick(double x,double y)
{
	bool breakFlag=false;
	osg::Geode *tmp;
	string line="ysgline_new";
	if (viewer->computeIntersections(x,y,intersection))//使用computeIntersections计算当前场景中单击到了那些模型，结果存放在结果集内
	{

		//使用迭代器取出这些模型，取出的结果是一个NodePath类对象，遍历该NodePath对象可以找到是否单击到了目标节点
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter=intersection.begin();hiter!=intersection.end();++hiter)
		{
			if (breakFlag) break;
			if (!hiter->nodePath.empty())
			{
				const osg::NodePath& np = hiter->nodePath;
				for (int i = np.size()-1, intk=0;i>=0;--i)
				{
					if (breakFlag) break;
					osg::Node* nd = dynamic_cast<osg::Node*>(np[i]);
					if (nd)
					{
						if (nd->getName().find(line) == 0)
						{
							tmp = dynamic_cast<osg::Geode*>(nd);
							if (tmp)
							{	
								breakFlag=true;
								return nd;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}


string HSpacing::setValue(Node *node)
{
	string bzm;
	char *strTmp;
	int *row_num=new int(0);
	string line="ysgline_new";
	if (!node) return "-1";
	bzm=trim(node->getName().substr(line.length()));

	string sql = "select line.标识码,line.管径,line.材质,line.起点埋深,line.终点埋深,\
				 point1.地面高程 as 起点高程,point2.地面高程 as 终点高程,line.建设年代,line.探测日期\
				 from ysgpoint_new as point1,ysgpoint_new as point2,\
				 ysgline_new as line where line.标识码='"+bzm+
				 "' and line.起点点号=point1.物探点号 and line.终点点号=point2.物探点号";
	res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),row_num);

	int field_num=PQnfields(res);

	for(int j=0;j<*row_num;++j)
	{
		strTmp = PQgetvalue(res,j,0);
		mHSpacingDlg->mList.InsertItem(j, strTmp);//插入行

		for(int k=1;k<field_num;++k)
		{
			strTmp = PQgetvalue(res,j,k);
			if (k>2 && k<7)
			{
				strTmp[8]='\0';
			}
			mHSpacingDlg->mList.SetItemText(j,k,strTmp);
		}
	}
	return bzm;
}


void HSpacing::computeHSpace(string bzm1,string bzm2)
{
	string sql="select st_length(st_shortestline(line1.geom, line2.geom))\
				from ysgline_new as line1, ysgline_new as line2\
				where line1.标识码='"+bzm1
				+"' and line2.标识码='"+bzm2+"'";
	int *rows=new int(0);
	res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),rows);
	ASSERT(*rows==1);
	char *len=PQgetvalue(res,0,0);
	len[8]='\0';
	mHSpacingDlg->m_HSpaceValue=atof(len)*111120;
	mHSpacingDlg->SendMessage(WM_UPDATEHSPACEDLG, false);
}