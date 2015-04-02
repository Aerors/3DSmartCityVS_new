// CSectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSectionDlg.h"
#include "afxdialogex.h"


// CCSectionDlg �Ի���

IMPLEMENT_DYNAMIC(CCSectionDlg, CDialogEx)

CCSectionDlg::CCSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSectionDlg::IDD, pParent)
{

}

CCSectionDlg::~CCSectionDlg()
{
}

void CCSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, listPro);
	DDX_Control(pDX, IDC_CHARTCTRL, mChartCtrl);
}


void CCSectionDlg::clearData()
{

}

BEGIN_MESSAGE_MAP(CCSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSectionDlg ��Ϣ�������


BOOL CCSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	listPro.DeleteAllItems();//���  
	listPro.InsertColumn(0,"��ʶ��",LVCFMT_LEFT,95);//�����  
	listPro.InsertColumn(1,"�ܾ�",LVCFMT_LEFT,95);  
	listPro.InsertColumn(2,"����",LVCFMT_LEFT,95);  
	listPro.InsertColumn(3,"�������",LVCFMT_LEFT,95);  
	listPro.InsertColumn(4,"�յ�����",LVCFMT_LEFT,95);  
	listPro.InsertColumn(5,"���߳�",LVCFMT_LEFT,95);  
	listPro.InsertColumn(6,"�յ�߳�",LVCFMT_LEFT,95);  
	listPro.InsertColumn(7,"�������",LVCFMT_LEFT,95);  
	listPro.InsertColumn(8,"̽������",LVCFMT_LEFT,95);  

	CChartAxis *pAxis= NULL; 
	pAxis = mChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = mChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	mChartCtrl.GetTitle()->AddString("��������");
	pAxis->GetLabel()->SetText("����߳�(m)");

	return TRUE; 
}

