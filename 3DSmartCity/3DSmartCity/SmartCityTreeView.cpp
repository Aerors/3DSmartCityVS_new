// SmartCityTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "SmartCityTreeView.h"


// SmartCityTreeView

IMPLEMENT_DYNCREATE(SmartCityTreeView, CView)

SmartCityTreeView::SmartCityTreeView()
{

}

SmartCityTreeView::~SmartCityTreeView()
{
}

BEGIN_MESSAGE_MAP(SmartCityTreeView, CView)
	
END_MESSAGE_MAP()


// SmartCityTreeView ��ͼ

void SmartCityTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// SmartCityTreeView ���

#ifdef _DEBUG
void SmartCityTreeView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void SmartCityTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// SmartCityTreeView ��Ϣ�������


void SmartCityTreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rect(0,0,250,30);
	m_button.Create(_T("ͼ�����"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,rect,this,1689);
	m_button.ShowWindow(SW_SHOW);
}