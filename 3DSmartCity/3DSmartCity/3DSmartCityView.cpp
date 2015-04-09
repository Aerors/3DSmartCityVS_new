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

// 3DSmartCityView.cpp : CMy3DSmartCityView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
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
	END_MESSAGE_MAP()

	// CMy3DSmartCityView ����/����

	CMy3DSmartCityView::CMy3DSmartCityView()
	{
		//��ʼ��
		mOSG=0;
		mThreadHandle=0;
		isPipe=false;
		isFirst=true;

	}

	CMy3DSmartCityView::~CMy3DSmartCityView()
	{
	}

	BOOL CMy3DSmartCityView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CMy3DSmartCityView ����

	void CMy3DSmartCityView::OnDraw(CDC* /*pDC*/)
	{
		CMy3DSmartCityDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;


	}


	// CMy3DSmartCityView ��ӡ


	void CMy3DSmartCityView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMy3DSmartCityView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CMy3DSmartCityView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CMy3DSmartCityView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CMy3DSmartCityView ���

#ifdef _DEBUG
	void CMy3DSmartCityView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMy3DSmartCityView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSmartCityDoc)));
		return (CMy3DSmartCityDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMy3DSmartCityView ��Ϣ�������

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
		// TODO: �ڴ����ר�ô����/����û���

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
		CString str="ͼ������";
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

		// TODO: �ڴ˴������Ϣ����������
	}


	void CMy3DSmartCityView::OnGuanxiantongjion()
	{
		// TODO: �ڴ���������������
		mOSG->initStatisticDlg();
	}

	void CMy3DSmartCityView::OnLiuxiangfenxion()
	{
		mOSG->initFlowDirectionDlg();
	}

	void CMy3DSmartCityView::OnPipeOn()
	{
		// TODO: �ڴ���������������
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
		// TODO: �ڴ���������������
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
	if(IDYES==MessageBoxA(_T("�Ƿ���ѡȡ����?"),_T("����ѡȡ"),MB_ICONQUESTION+MB_YESNO))  
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
		MessageBoxA(_T("��˫��ѡȡ����"),_T("����ѡȡ"));
		mOSG->isVsectionStart=true;
	}	







void CMy3DSmartCityView::OnClose()
{
	

	CView::OnClose();
}
