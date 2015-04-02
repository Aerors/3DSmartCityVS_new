#pragma once
#include "MainFrm.h"
#include "OSGObject.h"

using namespace std;
using namespace osgEarth;


// SmartCityTreeView ��ͼ

class SmartCityTreeView : public CView
{
	DECLARE_DYNCREATE(SmartCityTreeView)

protected:
	SmartCityTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~SmartCityTreeView();
	CMainFrame* mainFrame;
public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	CButton m_button;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


