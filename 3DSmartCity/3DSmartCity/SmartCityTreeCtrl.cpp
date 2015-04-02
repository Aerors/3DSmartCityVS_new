// SmartCityTreeCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "SmartCityTreeCtrl.h"
#include "3DSmartCityView.h"
#include "SmartCityTreeView.h"
#include "MainFrm.h"

// SmartCityTreeCtrl

IMPLEMENT_DYNAMIC(SmartCityTreeCtrl, CTreeCtrl)
SmartCityTreeCtrl::SmartCityTreeCtrl(HWND hWnd)
{
   m_hWnd=hWnd;
}
SmartCityTreeCtrl::SmartCityTreeCtrl()
{

}

SmartCityTreeCtrl::~SmartCityTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(SmartCityTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &SmartCityTreeCtrl::OnNMClick)
END_MESSAGE_MAP()



// SmartCityTreeCtrl ��Ϣ�������




void SmartCityTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame*  pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	SmartCityTreeView* leftView = (SmartCityTreeView*)pFrame->GetActiveFrame();
	SmartCityTreeView* leftView001=(SmartCityTreeView*)pFrame->m_wndSplitter.GetPane(0,0);
	CMy3DSmartCityView* pRightView = (CMy3DSmartCityView*)pFrame->m_wndSplitter.GetPane(0,1);
	CPoint pt = GetCurrentMessage()->pt;   //��ȡ��ǰ�������Ϣ�������
	this->ScreenToClient(&pt);
	UINT uFlags = 0;

	mainFrame = (CMainFrame*)GetActiveWindow();//��������Ļ���꣬ת�������οؼ��Ŀͻ�������

	HTREEITEM hItem = this->HitTest(pt, &uFlags);//Ȼ�����������


	if ((hItem != NULL) && (TVHT_ONITEMSTATEICON & uFlags))//��������λ�����ڽڵ�λ������
	{
		osgEarth::Map* map = dynamic_cast<osgEarth::Map*>(pRightView->mOSG->mapNode->getMap());


		BOOL checked =this->GetCheck(hItem);
		CString nData001 = this->GetItemText(hItem);
		string layerName001 = (CT2A)nData001.GetBuffer(0);

	/*	theApp.NeedModify = TRUE;
		while(!theApp.CanModify)
		Sleep(1);*/
		osg::ref_ptr<osgEarth::ImageLayer> layer;
		for(osgEarth::ImageLayerVector::iterator it = pRightView->mOSG->imageLayerVec.begin();it!=pRightView->mOSG->imageLayerVec.end();it++)
		{
			string s = (*it)->getName();
			if(0 ==s.compare(layerName001))
			{
				layer = *it;
				if(checked)
				{//��ʱ��ѡ�е�δѡ��
					//map->removeImageLayer(layer);
					//------wangsongwei ����Ϊ���ɼ�
					layer->setVisible(false);
				}else
				{//��ʱ��δѡ�е�ѡ��
					//map->addImageLayer(layer);
					//------wangsongwei
					layer->setVisible(true);
				}
				//theApp.NeedModify = FALSE;
			}
		}

		

		//-----wangsongwei  ģ�Ͳ�
		osg::ref_ptr<osgEarth::ModelLayer> mlayer;
		for(osgEarth::ModelLayerVector::iterator it = pRightView->mOSG->modelLayerVec.begin();it!=pRightView->mOSG->modelLayerVec.end();it++)
		{
			string s = (*it)->getName();
			if(0 ==s.compare(layerName001))
			{
				mlayer = *it;
				if(checked)
				{//��ʱ��ѡ�е�δѡ��
					//map->removeImageLayer(layer);
					//------wangsongwei ����Ϊ���ɼ�
					mlayer->setVisible(false);
				}else
				{//��ʱ��δѡ�е�ѡ��
					//map->addImageLayer(layer);
					//------wangsongwei
					mlayer->setVisible(true);
				}
				//theApp.NeedModify = FALSE;
			}
		}
		
	}
	*pResult = 0;
}
