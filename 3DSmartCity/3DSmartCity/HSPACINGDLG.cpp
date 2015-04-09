// HSpacingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "HSpacingDlg.h"
#include "afxdialogex.h"


// HSpacingDlg �Ի���

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


// HSpacingDlg ��Ϣ�������


BOOL HSpacingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mList.DeleteAllItems();//���  
	mList.InsertColumn(0,"��ʶ��",LVCFMT_LEFT,95);//�����  
	mList.InsertColumn(1,"�ܾ�",LVCFMT_LEFT,95);  
	mList.InsertColumn(2,"����",LVCFMT_LEFT,95);  
	mList.InsertColumn(3,"�������",LVCFMT_LEFT,95);  
	mList.InsertColumn(4,"�յ�����",LVCFMT_LEFT,95);  
	mList.InsertColumn(5,"���߳�",LVCFMT_LEFT,95);  
	mList.InsertColumn(6,"�յ�߳�",LVCFMT_LEFT,95);  
	mList.InsertColumn(7,"�������",LVCFMT_LEFT,95);  
	mList.InsertColumn(8,"̽������",LVCFMT_LEFT,95);  


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



afx_msg LRESULT HSpacingDlg::OnUpdatehspacedlg(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}
