#pragma once
#include "HeadFiles.h"
#include "PickHandlerHighLight.h"
#include "HighLightVisitor.h"
#include "afxcmn.h"
#include "PipePoint.h"

using namespace osg;
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;
// CBaoguanDlg �Ի���

class CBaoguanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaoguanDlg)

public:
	CBaoguanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaoguanDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BAOGUAN };

	//add
	MapNode* mapNode;
	EarthManipulator **manip;
	osgViewer::Viewer* viewer;
	osg::Group *root;
	Analyze *bgAnalyze;

	PickHandlerHighLight *_pick;

public:
	void initDlgToGetOSGParam(MapNode* mapNode,EarthManipulator ** em,osgViewer::Viewer* viewer,osg::Group *root);



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPickPipe();
	afx_msg void OnBnClickedButtonClearPipe();
	afx_msg void OnBnClickedButtonCancel();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListBaoguan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
