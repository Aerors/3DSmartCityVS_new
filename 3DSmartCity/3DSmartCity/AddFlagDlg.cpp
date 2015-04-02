// AddFlagDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "AddFlagDlg.h"
#include "afxdialogex.h"
#include <string>


using namespace osgEarth::Symbology;
using namespace osgEarth::Annotation;
// CAddFlagDlg �Ի���

IMPLEMENT_DYNAMIC(CAddFlagDlg, CDialogEx)

CAddFlagDlg::CAddFlagDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddFlagDlg::IDD, pParent)
{

	m_Lat = 0.0;
	m_Lon = 0.0;
	m_Note = _T("");
}

CAddFlagDlg::~CAddFlagDlg()
{
}

void CAddFlagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_LON, strLon);
	//  DDX_Text(pDX, IDC_EDIT_LAT, strLat);
	//  DDX_Text(pDX, IDC_EDIT_NOTE, strNote);
	DDX_Text(pDX, IDC_EDIT_LAT, m_Lat);
	DDX_Text(pDX, IDC_EDIT_LON, m_Lon);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_Note);
	DDV_MaxChars(pDX, m_Note, 255);
}


BEGIN_MESSAGE_MAP(CAddFlagDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddFlagDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddFlagDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_UPDATEDATA_ADDMARKER, &CAddFlagDlg::OnUpdatedata)
//ON_REGISTERED_MESSAGE(WM_UPDATEDATA, &CAddFlagDlg::OnUpdatedata)
END_MESSAGE_MAP()


// CAddFlagDlg ��Ϣ�������


void CAddFlagDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Lon==0.0)
	{
		MessageBox("����ѡȡ����","ERROR");
	} 
	else if (m_Note=="")
	{
		MessageBox("���������ƣ������������ģ�","ERROR");
	} 
	else
	{
		Style pin;		
		std::string noteName;
		noteName=m_Note.GetBuffer(0);
		pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
		mLabels->addChild( new PlaceNode(mapNode, geoPoint,noteName, pin));
		m_Lat = 0.0;
		m_Lon = 0.0;
		m_Note = _T("");		
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}	
	
}


void CAddFlagDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Lat = 0.0;
	m_Lon = 0.0;
	m_Note = _T("");
	UpdateData(FALSE);
	CDialogEx::OnCancel();
}


void CAddFlagDlg::initDlg(osg::ref_ptr<osg::Group> mLabels,	osg::ref_ptr<osgEarth::MapNode> mapNode)
{
	this->mLabels=mLabels;
	this->mapNode=mapNode;
}

afx_msg LRESULT CAddFlagDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}


//afx_msg LRESULT CAddFlagDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
//{
//	UpdateData(wParam);
//	return 0;
//}
