#pragma once
#include "resource.h"

// CTrackPipeDialog �Ի���

class CTrackPipeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTrackPipeDialog)

public:
	CTrackPipeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTrackPipeDialog();

// �Ի�������
	enum { IDD = IDD_ZHUIZONG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CEdit mEdit;
	CMFCColorButton mColorPicker;
};
