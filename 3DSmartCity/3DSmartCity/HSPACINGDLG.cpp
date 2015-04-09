// HSpacingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "HSpacingDlg.h"
#include "afxdialogex.h"


// HSpacingDlg 对话框

IMPLEMENT_DYNAMIC(HSpacingDlg, CDialogEx)

HSpacingDlg::HSpacingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HSpacingDlg::IDD, pParent)	
{
	m_HSpaceValue = 0.0;
}

HSpacingDlg::~HSpacingDlg()
{
}

void HSpacingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HSPACING_LIST, mList);
	//  DDX_Text(pDX, IDC_HSPACING, mHSpaceValue);
	DDX_Text(pDX, IDC_HSPACING, m_HSpaceValue);
	DDV_MinMaxDouble(pDX, m_HSpaceValue, 0.0, 10000.0);
}


BEGIN_MESSAGE_MAP(HSpacingDlg, CDialogEx)
//	ON_WM_UPDATEUISTATE()
	ON_MESSAGE(WM_UPDATEHSPACEDLG, &HSpacingDlg::OnUpdatehspacedlg)
END_MESSAGE_MAP()


// HSpacingDlg 消息处理程序


BOOL HSpacingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mList.DeleteAllItems();//清空  
	mList.InsertColumn(0,"标识码",LVCFMT_LEFT,95);//添加列  
	mList.InsertColumn(1,"管径",LVCFMT_LEFT,95);  
	mList.InsertColumn(2,"材质",LVCFMT_LEFT,95);  
	mList.InsertColumn(3,"起点埋深",LVCFMT_LEFT,95);  
	mList.InsertColumn(4,"终点埋深",LVCFMT_LEFT,95);  
	mList.InsertColumn(5,"起点高程",LVCFMT_LEFT,95);  
	mList.InsertColumn(6,"终点高程",LVCFMT_LEFT,95);  
	mList.InsertColumn(7,"建设年代",LVCFMT_LEFT,95);  
	mList.InsertColumn(8,"探测日期",LVCFMT_LEFT,95);  


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



afx_msg LRESULT HSpacingDlg::OnUpdatehspacedlg(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}
