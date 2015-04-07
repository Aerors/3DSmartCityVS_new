// FlowDirectionDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "FlowDirectionDialog.h"
#include "afxdialogex.h"


// FlowDirectionDialog 对话框

IMPLEMENT_DYNAMIC(FlowDirectionDialog, CDialogEx)

FlowDirectionDialog::FlowDirectionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(FlowDirectionDialog::IDD, pParent)
{

}

FlowDirectionDialog::~FlowDirectionDialog()
{
}

void FlowDirectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FLOWDIRLIST, m_list);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, mColorPicker);
}


BEGIN_MESSAGE_MAP(FlowDirectionDialog, CDialogEx)
END_MESSAGE_MAP()


// FlowDirectionDialog 消息处理程序
