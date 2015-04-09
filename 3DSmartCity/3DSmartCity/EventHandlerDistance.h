#pragma once
#include <osgUtil/LineSegmentIntersector>
#include <osgEarth/MapNode>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/Map>
#include <osg/LineWidth>
#include <osg/ShapeDrawable>
#include <osgEarth/GeoData>
#include <osgEarth//MapNode>
#include <osgText/Font>
#include <osgText/Text>
#include "DisDlg.h"
#include "AddFlagDlg.h"

using namespace  std;

class CEventHandlerDistance :
	public osgGA::GUIEventHandler
{
public:
	
	BOOL isPickWorld;//是否点击世界地图
	
	void isStartTest(bool isTest);

public:
	CEventHandlerDistance(osg::ref_ptr<osgEarth::MapNode> mapNode1,CDisDlg ** addlg,bool *isWindowClose);
	~CEventHandlerDistance(void);
	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

	osg::Vec3d IntersectPoint(osg::Vec3d XPosition,osg::Vec3d YPosition,osg::ref_ptr<osg::Node> Node);
	bool isTestJu;
	double GetDis(osg::Vec3d form,osg::Vec3d to);
	double GetDis1(osg::ref_ptr<osg::Vec3Array> vec);
	//状态机
	//0用户没用双击
	//1设置了起点
	//2设置了终点
	int jieduan;	
	CEventHandlerDistance *mDIS;
	CDisDlg * *DisDlgShow;
	bool * isWindowClose1;
	osg::ref_ptr<osg::Group> mLabels3;
	osg::ref_ptr<osgEarth::MapNode> mapNode3;
	osg::ref_ptr<osg::Group> myRoot;
	osg::ref_ptr<osg::Group> myRoot1;
	osg::ref_ptr<osg::Geode> lineStrip;//线
	osg::ref_ptr<osg::Geode> lineStrip1;//线

	osg::ref_ptr<osg::Group> StartandEnd;
	osg::ref_ptr<osgEarth::MapNode> mapNode1;
	osg::Vec3d startPoint;//开始点
	osg::Vec3d midPoint;//中间点
	osg::Vec3d endPoint;//结束点
	osg::ref_ptr<osg::Vec3Array> vertex;//顶点

	int Jilu;
	osg::ref_ptr<osg::CoordinateSystemNode> csn;
	//GeoPoint ConvertPoint;

	//文本
	osg::ref_ptr<osg::Geode> wenben;

};

