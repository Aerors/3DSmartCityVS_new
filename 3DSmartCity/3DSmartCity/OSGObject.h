#pragma once

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer\api\Win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgEarth/MapNode>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarth/ImageLayer>
#include "3DSmartCity.h"
#include "PipeStatisticHandler.h"
#include "HeadFiles.h"
#include "AddPipe.h"
#include "AddFlagDlg.h"
#include "AddClick.h"
#include "CSection.h"
#include "FlowDirectionDialog.h"
#include "TrackPipeDialog.h"
#include "VSection.h"
<<<<<<< HEAD
#include "EventHandlerDistance.h"
#include "DisDlg.h"
#include "EventRect.h"
=======
#include "HSpacing.h"

>>>>>>> parent of 5503c20... Revert "ËÆ°ÁÆóÊ∞¥Âπ≥ÂáÄË∑ù..."
using namespace osgEarth;
class COSGObject
{
public:
	COSGObject(HWND hWnd);
	~COSGObject(void);
	void InitOSG();
	void InitSceneGraph();
	void InitCameraConfig();//≥ı ºªØœ‡ª˙
	void PreFrameUpdate();//«∞¥¶¿Ì
	void PostFrameUpdate();//∫Û¥¶¿Ì
	static void Render(void * ptr);//πÊ±‹œﬂ≥Ãª•≥‚∑Ω∑®
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	vector<string> layernames;
	osgEarth::ImageLayerVector imageLayerVec;

	osgViewer::Viewer *getViewer();
	void InitOsgEarth();
	void setChinaBoundariesOpacity(double opt);
	double getChinaBoundariesOpacity();
	void rmvChinaBounds();
	void addChinaBounds();

	void addPipe(string pipeName,string pointName);


	//biaohui--mark
	CAddFlagDlg *addlg;
	bool closeWindows;
	void addFlag();	
	osg::ref_ptr<osg::Group> mLabels;

	//ª≠œﬂ∆Ù”√±Í÷æ ∫·∂œ√Ê∑÷Œˆ;--songweiwang
	bool isDrawLineStart;
	osg::ref_ptr<osg::Group> mCSLine;
	//---end hengduanfenxi

	//ÀÆ∆Ωæªæ‡;songweiwang
	bool isHSpacingStart;
	//end---ÀÆ∆Ωæªæ‡;songweiwang

	//◊›∂œ√Ê∑÷Œˆ---songweiwang;	
	bool isVsectionStart;	

	//---end zongduanfenxi

	
public:
	//dc--π‹œﬂÕ≥º∆-----------------------------------------------------------------
	bool ifDoStatistic;
	StatisticDialog* pStatisticDlg;
	void initStatisticDlg();
	osg::Group* pRectNodeGroup;

	//dc--¡˜œÚ∑÷Œˆ------------------------------------------------------------------
	FlowDirectionDialog* pFlowDirectionDlg;
	void initFlowDirectionDlg();
	
	//dc--◊∑◊Ÿ∑÷Œˆ------------------------------------------------------------------
	CTrackPipeDialog* pTrackPipeDlg;
	void initTrackPipeDlg();
	//dc----------------------------------------------------------------------------

	//------wangsongwei  º”…œƒ£–Õ≤„øÿ÷∆
	ModelLayerVector modelLayerVec;
	osg::ref_ptr<osg::Group> mPipeGroup;


private:
	HWND n_hWnd;//¥¥Ω®“ª∏ˆæ‰±˙
	osgViewer::Viewer * mViewer;
	osg::ref_ptr<osg::Group> mRoot;

	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
	osg::ref_ptr<osgEarth::ImageLayer> china_boundaries;
	//π‹œﬂ π‹µ„
private:
	map<string ,string> *pipes;
public:
	void pipeView(void);
	void buildingView(void);

	//¡øÀ„
	CDisDlg *disdlg;
	void adddis();
public:
	osg::ref_ptr<CEventHandlerDistance> eh;
	osg::ref_ptr<CEventRect> er;
	void isTestju(bool isTestju);
	void isTestAera(bool isTestAera);


};


