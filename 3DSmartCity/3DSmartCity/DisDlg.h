#pragma once
#include "stdafx.h"
#include "resource.h"
#include "HeadFiles.h"

// CDisDlg �Ի���
#define  WM_UPDATEDATA_DIS WM_USER+112

using namespace osg;
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;
class CDisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDisDlg)

public:
	CDisDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDisDlg();
	void initDlg(osg::ref_ptr<osg::Group> mLabels,	osg::ref_ptr<osgEarth::MapNode> mapNode);
	CString m_dis;
	CString m_name;
// �Ի�������
	enum { IDD = IDD_DisDlg };
	osg::ref_ptr<osg::Group> mLabels2;
	osg::ref_ptr<osgEarth::MapNode> mapNode2;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeDis();
};
