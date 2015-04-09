#pragma once

#include "resource.h"
#include "afxcmn.h"

#define  WM_UPDATEHSPACEDLG WM_USER+112

// HSpacingDlg �Ի���

class HSpacingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HSpacingDlg)

public:
	HSpacingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HSpacingDlg();

// �Ի�������
	enum { IDD = IDD_HSPACINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
