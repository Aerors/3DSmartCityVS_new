#include "StdAfx.h"
#include "OSGObject.h"
#include "HighLightVisitor.h"

#include "FlowDirectionHandler.h"
#include "TrackPipeHandler.h"
COSGObject::COSGObject(HWND hWnd)
{
	n_hWnd = hWnd;

	isDrawLineStart=false;
	closeWindows=false;
	isVsectionStart=false;
	pStatisticDlg =  new StatisticDialog();
	pFlowDirectionDlg = new FlowDirectionDialog();
	pTrackPipeDlg = new CTrackPipeDialog();
	pipes=new map<string ,string>;
	pipes->insert(pair<string,string>("ysgline_new","ysgpoint_new"));
}


COSGObject::~COSGObject(void)
{
	mViewer->setDone(true);
	Sleep(1000);
	mViewer->stopThreading();
	delete mViewer;
}

void COSGObject::InitOSG()
{
	InitSceneGraph();
	InitCameraConfig();
	InitOsgEarth();
}
void COSGObject::InitSceneGraph()
{
	//��ʼ������ͼ
	mRoot=new osg::Group;
	mPipeGroup = new osg::Group;
	mLabels=new osg::Group;
	osg::ref_ptr<osg::Node> mp=osgDB::readNodeFile("E:/HRB/china-simple2.earth");
	mRoot->addChild(mp);
	mRoot->addChild(mLabels);
	mapNode=dynamic_cast<osgEarth::MapNode*>(mp.get());

	//osg::StateSet* stateset = mapNode->getOrCreateStateSet();
	osg::StateSet* stateset = mRoot->getOrCreateStateSet();
	//stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
}
void COSGObject::InitCameraConfig()//��ʼ�����
{
	CRect rect;
	//RECT rect;	
	mViewer = new osgViewer::Viewer;
	::GetWindowRect(n_hWnd,&rect);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits=new osg::GraphicsContext::Traits;
	osg::ref_ptr<osg::Referenced> vindata=new osgViewer::GraphicsWindowWin32::WindowData(n_hWnd);
	rect.OffsetRect(1000,1000);
	traits->x=0;
	traits->y=0;
	traits->width=rect.right-rect.left;
	traits->height=rect.bottom-rect.top;
	traits->windowDecoration=false;
	traits->doubleBuffer=true;
	traits->sharedContext=0;
	traits->setInheritedWindowPixelFormat=true;
	traits->inheritedWindowData=vindata;
	osg::GraphicsContext *gc=osg::GraphicsContext::createGraphicsContext(traits);


	osg::ref_ptr<osg::Camera> camera=new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(traits->x,traits->y,traits->width,traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f,static_cast<double> (traits->width)/static_cast<double>(traits->height),1.0,1000.0);

	//begin   dialog of mark
	addlg=new CAddFlagDlg();
	addlg->Create(IDD_ADD_DIALOG);
	addlg->initDlg(mLabels,mapNode);
	mViewer->addEventHandler(new CAddClick(mapNode,mViewer,&addlg,&closeWindows));
	//end     dialog of mark

	//begin ��������
	mCSLine=new osg::Group();
	mRoot->addChild(mCSLine);
	mViewer->addEventHandler(new CCSection(mapNode, mViewer,mCSLine,& isDrawLineStart));
	//end	��������

	//begin �ݶ������  songweiwang;
	mViewer->addEventHandler(new VSection(mapNode, mViewer,&isVsectionStart));
	//end	�ݶ������  songweiwang;

	//dc begin	����ͳ��---------------------------------------
	pStatisticDlg->Create(IDD_TONGJI);
	pRectNodeGroup = new osg::Group;
	mRoot->addChild(pRectNodeGroup);
	mViewer->addEventHandler(new PipeStatisticHandler(mViewer,mapNode.get(),&pStatisticDlg,&pRectNodeGroup));
	//dc end	����ͳ��---------------------------------------

	//dc begin	�������---------------------------------------
	pFlowDirectionDlg->Create(IDD_LIUXIANG);
	mViewer->addEventHandler(new FlowDirectionHandler(&pFlowDirectionDlg,mViewer));
	//dc end	�������---------------------------------------
	
	//dc begin	�������---------------------------------------
	pTrackPipeDlg->Create(IDD_ZHUIZONG);
	mViewer->addEventHandler(new TrackPipeHandler(&pTrackPipeDlg,mViewer));
	//dc end	�������---------------------------------------

	mViewer->setCamera(camera);
	//mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	mViewer->setSceneData(mRoot);
	mViewer->realize();
	mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_USING_PRIMITIVES);
	mViewer->getCamera()->setNearFarRatio(0.000003f);

	mViewer->addEventHandler(new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()));
	//����,����

	disdlg=new CDisDlg();
	disdlg->Create(IDD_DisDlg);
	disdlg->initDlg(mLabels,mapNode);
	eh=new CEventHandlerDistance(mapNode,&disdlg,&closeWindows);
	mViewer->addEventHandler(eh);
	//���
	er=new CEventRect(mapNode,&disdlg);
	mViewer->addEventHandler(er);
}
void COSGObject::PreFrameUpdate()
{
	while(theApp.NeedModify) Sleep(1);
	theApp.CanModify=FALSE;
}
void COSGObject::PostFrameUpdate()
{
	if (theApp.NeedModify)theApp.CanModify=true;
}
void COSGObject::Render(void * ptr)//����̻߳��ⷽ��,��Ⱦ�߳�
{

	COSGObject *osg =(COSGObject *)ptr;
	osgViewer::Viewer *viewer = osg->getViewer();
	while(!viewer->done())
	{

		osg->PreFrameUpdate();
		viewer->frame();
		osg->PostFrameUpdate();
	}
	_endthread();
}

osgViewer::Viewer *COSGObject::getViewer()
{
	return mViewer;
}

void COSGObject::InitOsgEarth()
{
	//��ʼ��������
	em=new osgEarth::Util::EarthManipulator;

	if(mapNode.valid())
	{
		em->setNode(mapNode);
	}
	em->getSettings()->setArcViewpointTransitions(true);
	mViewer->setCameraManipulator(em);
	em->setViewpoint( osgEarth::Viewpoint(
		126.660, 45.75, 20,   // longitude, latitude, altitude
		24.261, -29.6, 3450.0), // heading, pitch, range
		5.0 );

	//��ʼ�����
	osgEarth::Config skyConf;
	osgEarth::Util::SkyOptions options(skyConf);
	double hours=skyConf.value("hours",12.0);
	osgEarth::Util::SkyNode *skyNode = osgEarth::Util::SkyNode::create(options, mapNode);
	skyNode->setDateTime(osgEarth::DateTime(2015,02,13,hours));
	skyNode->attach(mViewer,3);
	mRoot->addChild(skyNode);

	//�����ˮ��ͼ��
	map<string, string>::iterator pipes_iter;
	for (pipes_iter=pipes->begin();pipes_iter!=pipes->end();pipes_iter++)
	{
		addPipe(pipes_iter->first,pipes_iter->second);
	}

	//��ȡͼ��
	mapNode->getMap()->getImageLayers(imageLayerVec);
	for (osgEarth::ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		layernames.push_back(it->get()->getName());
	}
	mapNode->getMap()->getModelLayers(modelLayerVec);
	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		layernames.push_back(it->get()->getName());
	}

	//china_boundaries=mapNode->getMap()->getImageLayerByName("world_boundaries");

}
//void COSGObject::setChinaBoundariesOpacity(double opt)
//{
//	if(china_boundaries)
//	{
//		china_boundaries->setOpacity(opt);
//	}
//}
//double COSGObject::getChinaBoundariesOpacity()
//{
//	if(china_boundaries)
//	{
//		return china_boundaries->getOpacity();
//	}
//	else
//	{
//		return -1;
//	}
//}
//void COSGObject::rmvChinaBounds()
//{
//
//	if(china_boundaries)
//	{
//		mapNode->getMap()->removeImageLayer(china_boundaries);
//
//	}
//}
//void COSGObject::addChinaBounds()
//{
//	if(china_boundaries)
//	{
//		mapNode->getMap()->addImageLayer(china_boundaries);
//	}
//}

void COSGObject::addPipe(string pipeName,string pointName)
{
	AddPipe * addpipes=new AddPipe();
	addpipes->InitAddPipe(pipeName,pointName);
	//addpipes->Addpipes(mapNode);
	mPipeGroup = addpipes->Addpipes(mapNode,mRoot);

	delete addpipes;
}


void COSGObject::initStatisticDlg()
{
	pStatisticDlg->ShowWindow(SW_NORMAL);
}

void COSGObject::initFlowDirectionDlg()
{
	pFlowDirectionDlg->ShowWindow(SW_NORMAL);
}

void COSGObject::initTrackPipeDlg()
{
	pTrackPipeDlg->ShowWindow(SW_NORMAL);
}

void COSGObject::pipeView(void)
{

	for (ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		//mapNode->getMap()->removeImageLayer(it->get());
		it->get()->setVisible(false);
	}

	int num = mRoot->getNumChildren();
	osg::Node* child;
	for(int i=0;i<num;i++)
	{
		child = mRoot->getChild(i);
		if(child->getName().compare("pipes") == 0)
		{
			child->setNodeMask(0xffffffff);
		}
	}

	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		//mapNode->getMap()->removeModelLayer(it->get());
		if (pipes->find(it->get()->getName())==pipes->end())
		{
			it->get()->setVisible(false);
		}
		else
		{
			it->get()->setVisible(true);
		}
	}
}



void COSGObject::buildingView(void)
{
	for (ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		//mapNode->getMap()->addImageLayer(it->get());
		it->get()->setVisible(true);
	}

	int num = mRoot->getNumChildren();
	osg::Node* child;
	for(int i=0;i<num;i++)
	{
		child = mRoot->getChild(i);
		if(child->getName().compare("pipes") == 0)
		{
			child->setNodeMask(0x00);

		}
	}

	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		//mapNode->getMap()->addModelLayer(it->get());
		//it->get()->setVisible(true);
		if (pipes->find(it->get()->getName())==pipes->end())
		{
			it->get()->setVisible(true);
		}
		else
		{
			it->get()->setVisible(false);
		}
	}
}


//mark flag  ... HuiGe  �㶮��
void COSGObject::addFlag()
{
	if (!addlg->IsWindowVisible())
	{
		if (addlg==NULL)
		{
			addlg=new CAddFlagDlg();
			addlg->Create(IDD_ADD_DIALOG);
			addlg->initDlg(mLabels,mapNode);
		}		
		addlg->ShowWindow(SW_NORMAL);
	}	
}
//�������
void COSGObject::isTestju(bool isTestju)
{
	theApp.NeedModify=TRUE;
	while(!theApp.CanModify)Sleep(1);

	eh->isStartTest(isTestju);
	theApp.NeedModify=FALSE;

}
//�������
void COSGObject::isTestAera(bool isTestAera)
{
	theApp.NeedModify=TRUE;
	while(!theApp.CanModify)Sleep(1);
	er->isStartTestArea(isTestAera);
	theApp.NeedModify=FALSE;

}
//������㵯���Ի���
void COSGObject::adddis()
{
	if (!disdlg->IsWindowVisible())
	{
		if (disdlg==NULL)
		{
			disdlg=new CDisDlg();
			disdlg->Create(IDD_DisDlg);
			disdlg->initDlg(mLabels,mapNode);			
		}		
		disdlg->ShowWindow(SW_NORMAL);
	}	
}
