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

// 3DSmartCityView.cpp : CMy3DSmartCityView ÀàµÄÊµÏÖ
//

#include "stdafx.h"
// SHARED_HANDLERS ¿ÉÒÔÔÚÊµÏÖÔ¤ÀÀ¡¢ËõÂÔÍ¼ºÍËÑË÷É¸Ñ¡Æ÷¾ä±úµÄ
// ATL ÏîÄ¿ÖĞ½øĞĞ¶¨Òå£¬²¢ÔÊĞíÓë¸ÃÏîÄ¿¹²ÏíÎÄµµ´úÂë¡£
#ifndef SHARED_HANDLERS
#include "3DSmartCity.h"
#endif


#include "3DSmartCityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DSmartCityView

IMPLEMENT_DYNCREATE(CMy3DSmartCityView, CView)

	BEGIN_MESSAGE_MAP(CMy3DSmartCityView, CView)
		// ±ê×¼´òÓ¡ÃüÁî
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DSmartCityView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_WM_ERASEBKGND()
		ON_WM_DESTROY()
		ON_COMMAND(ID_GUANXIANTONGJION, &CMy3DSmartCityView::OnGuanxiantongjion)
		ON_COMMAND(ID_CHANGJINGON, &CMy3DSmartCityView::OnPipeOn)
		ON_COMMAND(32791, &CMy3DSmartCityView::OnBuildingOn)
		ON_COMMAND(ID_BIAOHUION, &CMy3DSmartCityView::OnBiaohuion)
		ON_COMMAND(ID_HENGDUANFENXION, &CMy3DSmartCityView::OnHengduanfenxion)
		ON_COMMAND(ID_LIUXIANGFENXION, &CMy3DSmartCityView::OnLiuxiangfenxion)
		ON_COMMAND(ID_ZONGDUANFENXION, &CMy3DSmartCityView::OnZongduanfenxion)
		ON_WM_CLOSE()
<<<<<<< HEAD
		ON_COMMAND(ID_ZHUIZONGFENXION, &CMy3DSmartCityView::OnZhuizongfenxion)
		ON_COMMAND(ID_CHELIANG, &CMy3DSmartCityView::OnCheliang)
		ON_UPDATE_COMMAND_UI(ID_CHELIANG, &CMy3DSmartCityView::OnUpdateCheliang)
		ON_COMMAND(ID_CELIANGAREA, &CMy3DSmartCityView::OnCeliangarea)
		ON_UPDATE_COMMAND_UI(ID_CELIANGAREA, &CMy3DSmartCityView::OnUpdateCeliangarea)
=======
		ON_COMMAND(ID_LIANTONGFENXION, &CMy3DSmartCityView::OnLiantongfenxion)
		ON_COMMAND(ID_SHUIPINGJINGJUFENXION, &CMy3DSmartCityView::OnShuipingjingjufenxion)
>>>>>>> parent of 5503c20... Revert "è®¡ç®—æ°´å¹³å‡€è·..."
	END_MESSAGE_MAP()

	// CMy3DSmartCityView ¹¹Ôì/Îö¹¹

	CMy3DSmartCityView::CMy3DSmartCityView()
	{
		//³õÊ¼»¯
		mOSG=0;
		mThreadHandle=0;
		isPipe=false;
		isFirst=true;
		isTestju=false;
		isTestAera=false;

	}

	CMy3DSmartCityView::~CMy3DSmartCityView()
	{
	}

	BOOL CMy3DSmartCityView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: ÔÚ´Ë´¦Í¨¹ıĞŞ¸Ä
		//  CREATESTRUCT cs À´ĞŞ¸Ä´°¿ÚÀà»òÑùÊ½

		return CView::PreCreateWindow(cs);
	}

	// CMy3DSmartCityView »æÖÆ

	void CMy3DSmartCityView::OnDraw(CDC* /*pDC*/)
	{
		CMy3DSmartCityDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;


	}


	// CMy3DSmartCityView ´òÓ¡


	void CMy3DSmartCityView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMy3DSmartCityView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ä¬ÈÏ×¼±¸
		return DoPreparePrinting(pInfo);
	}

	void CMy3DSmartCityView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: Ìí¼Ó¶îÍâµÄ´òÓ¡Ç°½øĞĞµÄ³õÊ¼»¯¹ı³Ì
	}

	void CMy3DSmartCityView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: Ìí¼Ó´òÓ¡ºó½øĞĞµÄÇåÀí¹ı³Ì
	}

	void CMy3DSmartCityView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CMy3DSmartCityView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CMy3DSmartCityView Õï¶Ï

#ifdef _DEBUG
	void CMy3DSmartCityView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMy3DSmartCityView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const // ·Çµ÷ÊÔ°æ±¾ÊÇÄÚÁªµÄ
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSmartCityDoc)));
		return (CMy3DSmartCityDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMy3DSmartCityView ÏûÏ¢´¦Àí³ÌĞò

	int CMy3DSmartCityView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
		mOSG = new COSGObject(m_hWnd);
		return 0;
	}



	BOOL CMy3DSmartCityView::OnEraseBkgnd(CDC* pDC)
	{
		if(0==mOSG)
		{
			return CView::OnEraseBkgnd(pDC);
		}
		else
		{
			return FALSE;
		}


		return CView::OnEraseBkgnd(pDC);
	}



	void CMy3DSmartCityView::OnInitialUpdate()
	{
		CView::OnInitialUpdate();
		mOSG->InitOSG();
		mThreadHandle=(HANDLE)_beginthread(&COSGObject::Render,0,mOSG);
		// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

		CMainFrame*  pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		SmartCityTreeView* leftView = (SmartCityTreeView*)pFrame->GetActiveFrame();
		SmartCityTreeView* leftView001=(SmartCityTreeView*)pFrame->m_wndSplitter.GetPane(0,0);
		CMy3DSmartCityView* pRightView = (CMy3DSmartCityView*)pFrame->m_wndSplitter.GetPane(0,1);

		tree.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
			| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
			| TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS | TVS_EDITLABELS,
			CRect(0, 30, 250, 1000), leftView001, 1200);
		tree.ShowWindow(SW_SHOW);
		tree.ModifyStyle( TVS_CHECKBOXES, 0 );
		tree.ModifyStyle( 0, TVS_CHECKBOXES );
		HTREEITEM hRoot;	
		CString str="Í¼²ãÃû³Æ";
		hRoot=tree.InsertItem(str);
		tree.SetCheck(hRoot);
		HTREEITEM hChild ;
		for(vector<string>::iterator it=pRightView->mOSG->layernames.begin();it!=pRightView->mOSG->layernames.end();it++)
		{
			layerName = it->c_str();
			hChild=tree.InsertItem(layerName,hRoot);
			tree.SetCheck(hChild);
		}
	}

	void CMy3DSmartCityView::OnDestroy()
	{
		CView::OnDestroy();
		if(mOSG!=0) delete mOSG;
		WaitForSingleObject(mThreadHandle,1000);
		CloseHandle(mThreadHandle);
		//_endthreadex(mThreadHandle);

		// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌĞò´úÂë
	}


	void CMy3DSmartCityView::OnGuanxiantongjion()
	{
		// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
		mOSG->initStatisticDlg();
	}

	void CMy3DSmartCityView::OnLiuxiangfenxion()
	{
		mOSG->initFlowDirectionDlg();
	}

	void CMy3DSmartCityView::OnZhuizongfenxion()
	{
		mOSG->initTrackPipeDlg();
	}

	void CMy3DSmartCityView::OnPipeOn()
	{
		// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
		theApp.NeedModify=TRUE;
		while(!theApp.CanModify)Sleep(1);
		if (isFirst||!isPipe)
		{
			mOSG->pipeView();
			isPipe=true;
			isFirst=false;
		}
		theApp.NeedModify=FALSE;
	}


	void CMy3DSmartCityView::OnBuildingOn()
	{
		// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
		theApp.NeedModify=TRUE;
		while(!theApp.CanModify)Sleep(1);
		if (isFirst||isPipe)
		{
			mOSG->buildingView();
			isPipe=false;
			isFirst=false;
		}
		theApp.NeedModify=FALSE;
	}


	void CMy3DSmartCityView::OnBiaohuion()
	{
		mOSG->addFlag();
	}


	void CMy3DSmartCityView::OnHengduanfenxion()
	{
		if(IDYES==MessageBoxA(_T("ÊÇ·ñ»­ÏßÑ¡È¡¹ÜÏß?"),_T("¹ÜÏßÑ¡È¡"),MB_ICONQUESTION+MB_YESNO))  
		{  
			mOSG->isDrawLineStart=true;
		}  
		else
		{
			mOSG->isDrawLineStart=false;
		}

	}	

	void CMy3DSmartCityView::OnZongduanfenxion()
	{
		MessageBoxA(_T("ÇëË«»÷Ñ¡È¡¹ÜÏß"),_T("¹ÜÏßÑ¡È¡"));
		mOSG->isVsectionStart=true;
	}	


	void CMy3DSmartCityView::OnClose()
	{
		CView::OnClose();
	}


	void CMy3DSmartCityView::OnLiantongfenxion()
	{
		// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë

	}


<<<<<<< HEAD
void CMy3DSmartCityView::OnClose()
{
	

	CView::OnClose();
}


void CMy3DSmartCityView::OnCheliang()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
	isTestju=!isTestju;
	mOSG->isTestju(isTestju);
}


void CMy3DSmartCityView::OnUpdateCheliang(CCmdUI *pCmdUI)
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî¸üĞÂÓÃ»§½çÃæ´¦Àí³ÌĞò´úÂë
	pCmdUI->SetCheck(isTestju);

	if(isTestju==false&&isTestAera==false)
	{
		//pCmdUI->SetCheck(0);
		pCmdUI->Enable(true);
	}
	else if(isTestAera==false&&isTestju==true)
	{
		//pCmdUI->SetCheck(1);
		pCmdUI->Enable(true);
	}
	else if(isTestAera==true&&isTestju==false)
	{
		//pCmdUI->SetCheck(0);
		pCmdUI->Enable(false);
	}
}


void CMy3DSmartCityView::OnCeliangarea()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
	isTestAera=!isTestAera;
	mOSG->isTestAera(isTestAera);
}


void CMy3DSmartCityView::OnUpdateCeliangarea(CCmdUI *pCmdUI)
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî¸üĞÂÓÃ»§½çÃæ´¦Àí³ÌĞò´úÂë
	pCmdUI->SetCheck(isTestAera);
	if(isTestju==false&&isTestAera==false)
	{
		pCmdUI->Enable(true);
	}
	else if(isTestju==false&&isTestAera==true)
	{
		pCmdUI->Enable(true);
	}
	else if(isTestAera==false&&isTestju==true)
	{
		pCmdUI->Enable(false);
	}
}



=======
	void CMy3DSmartCityView::OnShuipingjingjufenxion()
	{
		// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌĞò´úÂë
		MessageBoxA(_T("Çëµ¥»÷Ñ¡È¡¹ÜÏß"),_T("¹ÜÏßÑ¡È¡"));
		mOSG->isHSpacingStart=true;
	}
>>>>>>> parent of 5503c20... Revert "è®¡ç®—æ°´å¹³å‡€è·..."
