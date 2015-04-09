// Õâ¶Î MFC Ê¾ÀıÔ´´úÂëÑİÊ¾ÈçºÎÊ¹ÓÃ MFC Microsoft Office Fluent ÓÃ»§½çÃæ 
// (¡°Fluent UI¡±)¡£¸ÃÊ¾Àı½ö¹©²Î¿¼£¬
// ÓÃÒÔ²¹³ä¡¶Microsoft »ù´¡Àà²Î¿¼¡·ºÍ 
// MFC C++ ¿âÈí¼şËæ¸½µÄÏà¹Øµç×ÓÎÄµµ¡£
// ¸´ÖÆ¡¢Ê¹ÓÃ»ò·Ö·¢ Fluent UI µÄĞí¿ÉÌõ¿îÊÇµ¥¶ÀÌá¹©µÄ¡£
// ÈôÒªÁË½âÓĞ¹Ø Fluent UI Ğí¿É¼Æ»®µÄÏêÏ¸ĞÅÏ¢£¬Çë·ÃÎÊ  
// http://msdn.microsoft.com/officeui¡£
//
// °æÈ¨ËùÓĞ(C) Microsoft Corporation
// ±£ÁôËùÓĞÈ¨Àû¡£

// 3DSmartCityView.h : CMy3DSmartCityView ÀàµÄ½Ó¿Ú
//

#pragma once
#include "3DSmartCityDoc.h"
#include "MainFrm.h"
#include "OSGObject.h"
#include "SmartCityTreeCtrl.h"
#include "SmartCityTreeView.h"
#include "3DSmartCity.h"
#define  WM_UPDATEDATA_DIS WM_USER+112
class CMy3DSmartCityView : public CView
{
protected: // ½ö´ÓĞòÁĞ»¯´´½¨
	CMy3DSmartCityView();
	DECLARE_DYNCREATE(CMy3DSmartCityView)
	CString layerName;
	SmartCityTreeCtrl tree;

// ÌØĞÔ
public:
	CMy3DSmartCityDoc* GetDocument() const;

// ²Ù×÷µØÍ¼
public:
	COSGObject* mOSG;
	HANDLE mThreadHandle;
//wangsongwei  ³¡¾°¿ØÖÆ±êÊ¶·û
public:
	bool isPipe;
	bool isFirst;
	bool isTestju;
	bool isTestAera;
	double m_dis;

// ÖØĞ´
public:
	virtual void OnDraw(CDC* pDC);  // ÖØĞ´ÒÔ»æÖÆ¸ÃÊÓÍ¼
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ÊµÏÖ
public:
	virtual ~CMy3DSmartCityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Éú³ÉµÄÏûÏ¢Ó³Éäº¯Êı
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
<<<<<<< HEAD
	afx_msg void OnZhuizongfenxion();
	afx_msg void OnCheliang();
	afx_msg void OnUpdateCheliang(CCmdUI *pCmdUI);
	afx_msg void OnCeliangarea();
	afx_msg void OnUpdateCeliangarea(CCmdUI *pCmdUI);
=======
	afx_msg void OnLiantongfenxion();
	afx_msg void OnShuipingjingjufenxion();
>>>>>>> parent of 5503c20... Revert "è®¡ç®—æ°´å¹³å‡€è·..."
};

#ifndef _DEBUG  // 3DSmartCityView.cpp ÖĞµÄµ÷ÊÔ°æ±¾
inline CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const
   { return reinterpret_cast<CMy3DSmartCityDoc*>(m_pDocument); }
#endif

