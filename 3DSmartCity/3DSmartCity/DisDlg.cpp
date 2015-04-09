// DisDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "DisDlg.h"
#include "afxdialogex.h"
#include <string>

// CDisDlg 对话框

IMPLEMENT_DYNAMIC(CDisDlg, CDialogEx)

CDisDlg::CDisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisDlg::IDD, pParent)
{
	m_dis="";
	m_name="";
}
void CDisDlg::initDlg(osg::ref_ptr<osg::Group> mLabels,	osg::ref_ptr<osgEarth::MapNode> mapNode)
{
	this->mLabels2=mLabels;
	this->mapNode2=mapNode;
}
CDisDlg::~CDisDlg()
{
}

void CDisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Dis,m_dis);
	DDX_Text(pDX, IDC_NAME,m_name);
	

}


BEGIN_MESSAGE_MAP(CDisDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDisDlg::OnBnClickedOk)
	ON_MESSAGE(WM_UPDATEDATA_DIS, &CDisDlg::OnUpdatedata)
END_MESSAGE_MAP()

void CDisDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CDialogEx::OnOK();
}

afx_msg LRESULT CDisDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}