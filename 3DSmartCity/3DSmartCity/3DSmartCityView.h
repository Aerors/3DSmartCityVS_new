// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// 3DSmartCityView.h : CMy3DSmartCityView ��Ľӿ�
//

#pragma once
#include "3DSmartCityDoc.h"
#include "MainFrm.h"
#include "OSGObject.h"
#include "SmartCityTreeCtrl.h"
#include "SmartCityTreeView.h"
#include "3DSmartCity.h"

class CMy3DSmartCityView : public CView
{
protected: // �������л�����
	CMy3DSmartCityView();
	DECLARE_DYNCREATE(CMy3DSmartCityView)
	CString layerName;
	SmartCityTreeCtrl tree;

// ����
public:
	CMy3DSmartCityDoc* GetDocument() const;

// ������ͼ
public:
	COSGObject* mOSG;
	HANDLE mThreadHandle;
//wangsongwei  �������Ʊ�ʶ��
public:
	bool isPipe;
	bool isFirst;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy3DSmartCityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnGuanxiantongjion();
	afx_msg void OnPipeOn();
	afx_msg void OnBuildingOn();
	afx_msg void OnBiaohuion();
	afx_msg void OnHengduanfenxion();
	afx_msg void OnLiuxiangfenxion();
	afx_msg void OnZongduanfenxion();
	afx_msg void OnClose();
	afx_msg void OnZhuizongfenxion();
};

#ifndef _DEBUG  // 3DSmartCityView.cpp �еĵ��԰汾
inline CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const
   { return reinterpret_cast<CMy3DSmartCityDoc*>(m_pDocument); }
#endif

