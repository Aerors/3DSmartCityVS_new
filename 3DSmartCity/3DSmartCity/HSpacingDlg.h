#pragma once

#include "resource.h"
#include "afxcmn.h"

#define  WM_UPDATEHSPACEDLG WM_USER+112

// HSpacingDlg 对话框

class HSpacingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HSpacingDlg)

public:
	HSpacingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HSpacingDlg();

// 对话框数据
	enum { IDD = IDD_HSPACINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mList;
//	CString mHSpaceValue;
	double m_HSpaceValue;
	virtual BOOL OnInitDialog();
//	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
protected:
	afx_msg LRESULT OnUpdatehspacedlg(WPARAM wParam, LPARAM lParam);
};
