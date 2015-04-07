// VSectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "VSectionDlg.h"
#include "afxdialogex.h"


// VSectionDlg 对话框

IMPLEMENT_DYNAMIC(VSectionDlg, CDialogEx)

VSectionDlg::VSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(VSectionDlg::IDD, pParent)
{

}

VSectionDlg::~VSectionDlg()
{
}

void VSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_V, m_List);
	DDX_Control(pDX, IDC_CHARTCTRL_V, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(VSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// VSectionDlg 消息处理程序


BOOL VSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.DeleteAllItems();//清空  
	m_List.InsertColumn(0,"标识码",LVCFMT_LEFT,95);//添加列  
	m_List.InsertColumn(1,"管径",LVCFMT_LEFT,95);  
	m_List.InsertColumn(2,"材质",LVCFMT_LEFT,95);  
	m_List.InsertColumn(3,"起点埋深",LVCFMT_LEFT,95);  
	m_List.InsertColumn(4,"终点埋深",LVCFMT_LEFT,95);  
	m_List.InsertColumn(5,"起点高程",LVCFMT_LEFT,95);  
	m_List.InsertColumn(6,"终点高程",LVCFMT_LEFT,95);  
	m_List.InsertColumn(7,"建设年代",LVCFMT_LEFT,95);  
	m_List.InsertColumn(8,"探测日期",LVCFMT_LEFT,95);  

	CChartAxis *pAxis= NULL; 
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	m_ChartCtrl.GetTitle()->AddString("纵断面分析");
	pAxis->GetLabel()->SetText("地面高程(m)");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
