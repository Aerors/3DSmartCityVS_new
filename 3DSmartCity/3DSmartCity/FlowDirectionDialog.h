#pragma once
#include "afxcmn.h"
#include "resource.h"
// FlowDirectionDialog �Ի���

class FlowDirectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FlowDirectionDialog)

public:
	FlowDirectionDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FlowDirectionDialog();

// �Ի�������
	enum { IDD = IDD_LIUXIANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
};
