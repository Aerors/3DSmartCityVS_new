// BaoguanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "BaoguanDlg.h"
#include "afxdialogex.h"


// CBaoguanDlg 对话框

IMPLEMENT_DYNAMIC(CBaoguanDlg, CDialogEx)

CBaoguanDlg::CBaoguanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaoguanDlg::IDD, pParent)
{
	bgAnalyze = new Analyze();
}

CBaoguanDlg::~CBaoguanDlg()
{
	if(bgAnalyze->bgMarkerLayer->getVisible())
	{
		bgAnalyze->bgMarkerLayer->setVisible(false);
	}

	bgAnalyze->objectIDOfPiecked = "";
	//bgAnalyze->objectIDsVector.erase(bgAnalyze->objectIDsVector.begin(),bgAnalyze->objectIDsVector.end());
	set <std::string>().swap(bgAnalyze->objectIDsVector);
	bgAnalyze->objectIDOfPiecked = "";
	m_list.DeleteAllItems();

	delete bgAnalyze;
	bgAnalyze = NULL;
}

void CBaoguanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BAOGUAN, m_list);
}


BEGIN_MESSAGE_MAP(CBaoguanDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PICK_PIPE, &CBaoguanDlg::OnBnClickedButtonPickPipe)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_PIPE, &CBaoguanDlg::OnBnClickedButtonClearPipe)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CBaoguanDlg::OnBnClickedButtonCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BAOGUAN, &CBaoguanDlg::OnNMDblclkListBaoguan)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CBaoguanDlg::initDlgToGetOSGParam(MapNode* mapNode,EarthManipulator ** em,osgViewer::Viewer* viewer,osg::Group *root)
{
	this->mapNode = mapNode;
	manip = em;
	this->viewer = viewer;
	this->root = root;
}



BOOL CBaoguanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD styles=m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(styles|LVS_EX_FULLROWSELECT);//选中全行

	m_list.InsertColumn( 0, "编号", LVCFMT_LEFT, 40 );//插入列
	m_list.InsertColumn( 1, "标识码", LVCFMT_CENTER, 60 );
	m_list.InsertColumn( 2, "阀门位置", LVCFMT_CENTER, 280 );
	return TRUE;  // return TRUE unless you set the focus to a control

}

// CBaoguanDlg 消息处理程序


void CBaoguanDlg::OnBnClickedButtonPickPipe()
{
	AfxMessageBox(_T("开始拾取管线，请双击管线！"));
	 //新建一个pickhandler
	_pick = new PickHandlerHighLight(this->mapNode,*manip,this->viewer,this->root,bgAnalyze);
	//设置为DYNAMIC DYNAMIC确实不会影响到事件处理器
	_pick->setDataVariance(osg::Object::DataVariance::DYNAMIC);
	//为事件设置名字 方便删除该事件
	_pick->setName("bgPicked");
	// 加入到viewer中
	this->viewer->addEventHandler(_pick);
}

//开始分析 按钮名字有问题！
void CBaoguanDlg::OnBnClickedButtonClearPipe()
{
	bgAnalyze->addMarkers(this->mapNode,this->root,"ysgline_new","ysgpoint_new",bgAnalyze->objectIDOfPiecked);
	int row = 1;
	CString rowStr = "";
	CString pointStr = "";
	//显示列表  序号  标识码
	//for(std::set<std::string>::iterator it=bgAnalyze->objectIDsVector.begin();it!=bgAnalyze->objectIDsVector.end();it++)
	//{
	//	/*std::string bzm("ysgline_new "+ *(it));
	//	osg::Node* root= this->viewer->getSceneData();
	//	HighLightVisitor hlv(bzm);
	//	root->accept(hlv);*/
	//	rowStr.Format("%d",row);
	//	int nRow = m_list.InsertItem(0, rowStr);//插入行
	//	m_list.SetItemText(nRow, 1, (*it).c_str());//设置数据
	//	row++;
	//}


	//显示列表 序号 标识码 geometry
	map<std::string,std::string>::iterator it2;
	for (it2=bgAnalyze->Id_Geom.begin();it2!=bgAnalyze->Id_Geom.end();++it2)
	{
		rowStr.Format("%d",row);//编号
		int nRow = m_list.InsertItem(0,rowStr);
		m_list.SetItemText(nRow,1,it2->first.c_str());

		//pointStr.Format("POINT(%d,%d,%d)",it2->second->getLon(),it2->second->getLat(),it2->second->getEle());
		//MessageBox(pointStr);
		m_list.SetItemText(nRow,2,it2->second.c_str());

		row++;
	}
}

//清除
void CBaoguanDlg::OnBnClickedButtonCancel()
{
	//设置marker图层 不可见
	if(bgAnalyze->bgMarkerLayer->getVisible())
	{
		bgAnalyze->bgMarkerLayer->setVisible(false);
	}
	//设置选中的管线标识码为空
	bgAnalyze->objectIDOfPiecked = "";
	
	//清空分析后存储的管点信息
	//bgAnalyze->objectIDsVector.erase(bgAnalyze->objectIDsVector.begin(),bgAnalyze->objectIDsVector.end());
	set <std::string>().swap(bgAnalyze->objectIDsVector);
	//清空list列表
	m_list.DeleteAllItems();
	//清空分析后存储的管点信息:标识码和geom
	bgAnalyze->Id_Geom.erase(bgAnalyze->Id_Geom.begin(),bgAnalyze->Id_Geom.end());
	
	//删除自定义事件
	for (osgViewer::View::EventHandlers::iterator iter = viewer->getEventHandlers().begin();iter != viewer->getEventHandlers().end();)
	{
		if(*iter == _pick)
		{
			iter = viewer->getEventHandlers().erase(iter);
		}
		else
		{
			++iter;
		}
	}

	CDialogEx::OnOK();//退出
}




//void CBaoguanDlg::OnHdnItemdblclickListBaoguan(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	*pResult = 0;
//}

//双击List某行 飞行定位
void CBaoguanDlg::OnNMDblclkListBaoguan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//TODO:双击定位
	double _lon = 0.0;
	double _lat = 0.0;
	double _elev = 0.0;
	//设置marker图层 不可见
	if(bgAnalyze->bgMarkerLayer->getVisible())
	{
		bgAnalyze->bgMarkerLayer->setVisible(false);
	}
	//获取选中行的几何信息
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if(pos!=NULL)  //这样就算选择多个也只取第一个
	{
		int nItem = m_list.GetNextSelectedItem( pos );
		CString st = m_list.GetItemText(nItem,2);
		MessageBox(st);

		string pointStr=string(st);
		int m,n,l,i,j,k;
		string str1,str2,str3,str4;
		n = pointStr.find('(');
		m = pointStr.find(')');
		string lon_lat_ele = pointStr.substr(n+1,m-1);

		i = lon_lat_ele.find(',');
		l = lon_lat_ele.length();
		str1 = lon_lat_ele.substr(0,i-1);//string:  lon
		str2 = lon_lat_ele.substr(i+1,l-1);//string:  lat,ele

		j = str2.find(',');
		k = str2.length();
		str3 = str2.substr(0,j-1); //string lat
		str4 = str2.substr(j+1,k-1);//string  ele

		_lon = atof(str1.c_str());//double lon
		_lat = atof(str3.c_str());
		_elev = atof(str4.c_str());



	/*	l = pointStr.find(' ');
		str1 = pointStr.substr(n+1,l-n-1);
		str2 = pointStr.substr(l+1,m-l-1);
		_lon=atof(str1.c_str());
		_lat=atof(str2.c_str());*/

	}
	//添加视野定位
	(*manip)->setViewpoint( osgEarth::Viewpoint(
		_lon, _lat, _elev,   // longitude, latitude, altitude
		24.261, -29.6, 350.0), // heading, pitch, range
		5.0 );
	//重新添加marker
	Style pin;		
	std::string noteName="";
	GeoPoint geoPoint;
	pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	this->viewer->getSceneData()->asGroup()->addChild(new PlaceNode(mapNode, GeoPoint(geoSRS, _lon,_lat,_elev),"here", pin));
	*pResult = 0;
}




void CBaoguanDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(bgAnalyze->bgMarkerLayer->getVisible())
	{
		bgAnalyze->bgMarkerLayer->setVisible(false);
	}

	bgAnalyze->objectIDOfPiecked = "";
	//bgAnalyze->objectIDsVector.erase(bgAnalyze->objectIDsVector.begin(),bgAnalyze->objectIDsVector.end());
	set <std::string>().swap(bgAnalyze->objectIDsVector);
	bgAnalyze->objectIDOfPiecked = "";
	m_list.DeleteAllItems();

	delete bgAnalyze;
	bgAnalyze = NULL;
}


void CBaoguanDlg::OnClose()
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	if(bgAnalyze->bgMarkerLayer->getVisible())
	{
  		bgAnalyze->bgMarkerLayer->setVisible(false);
	}

	bgAnalyze->objectIDOfPiecked = "";
	//bgAnalyze->objectIDsVector.erase(bgAnalyze->objectIDsVector.begin(),bgAnalyze->objectIDsVector.end());
	set <std::string>().swap(bgAnalyze->objectIDsVector);
	bgAnalyze->objectIDOfPiecked = "";
	m_list.DeleteAllItems();

	delete bgAnalyze;
	bgAnalyze = NULL;

	CDialogEx::OnClose();
}
