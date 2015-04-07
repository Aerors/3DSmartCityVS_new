#pragma once
#include "resource.h"

// CTrackPipeDialog 对话框

class CTrackPipeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTrackPipeDialog)

public:
	CTrackPipeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTrackPipeDialog();

// 对话框数据
	enum { IDD = IDD_ZHUIZONG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CEdit mEdit;
	CMFCColorButton mColorPicker;
};
