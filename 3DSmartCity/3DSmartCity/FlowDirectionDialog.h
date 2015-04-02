#pragma once
#include "afxcmn.h"
#include "resource.h"
// FlowDirectionDialog 对话框

class FlowDirectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FlowDirectionDialog)

public:
	FlowDirectionDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FlowDirectionDialog();

// 对话框数据
	enum { IDD = IDD_LIUXIANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
};
