// TrackPipeDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "TrackPipeDialog.h"
#include "afxdialogex.h"


// CTrackPipeDialog �Ի���

IMPLEMENT_DYNAMIC(CTrackPipeDialog, CDialogEx)

CTrackPipeDialog::CTrackPipeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrackPipeDialog::IDD, pParent)
{

}

CTrackPipeDialog::~CTrackPipeDialog()
{
}

void CTrackPipeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZZLIST, m_List);
	DDX_Control(pDX, IDC_ZZEDIT, mEdit);
	DDX_Control(pDX, IDC_ZZCOLORBUTTON, mColorPicker);
}


BEGIN_MESSAGE_MAP(CTrackPipeDialog, CDialogEx)
END_MESSAGE_MAP()


// CTrackPipeDialog ��Ϣ�������
