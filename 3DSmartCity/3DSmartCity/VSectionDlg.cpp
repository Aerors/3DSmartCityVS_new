// VSectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "VSectionDlg.h"
#include "afxdialogex.h"


// VSectionDlg �Ի���

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


// VSectionDlg ��Ϣ�������


BOOL VSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.DeleteAllItems();//���  
	m_List.InsertColumn(0,"��ʶ��",LVCFMT_LEFT,95);//�����  
	m_List.InsertColumn(1,"�ܾ�",LVCFMT_LEFT,95);  
	m_List.InsertColumn(2,"����",LVCFMT_LEFT,95);  
	m_List.InsertColumn(3,"�������",LVCFMT_LEFT,95);  
	m_List.InsertColumn(4,"�յ�����",LVCFMT_LEFT,95);  
	m_List.InsertColumn(5,"���߳�",LVCFMT_LEFT,95);  
	m_List.InsertColumn(6,"�յ�߳�",LVCFMT_LEFT,95);  
	m_List.InsertColumn(7,"�������",LVCFMT_LEFT,95);  
	m_List.InsertColumn(8,"̽������",LVCFMT_LEFT,95);  

	CChartAxis *pAxis= NULL; 
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	m_ChartCtrl.GetTitle()->AddString("�ݶ������");
	pAxis->GetLabel()->SetText("����߳�(m)");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
