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
#include "DisDlg.h"
#include "AddFlagDlg.h"
#include <osg/Timer>
#include <osg/io_utils>
#include <osg/observer_ptr>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/PolytopeIntersector>
#include <osgUtil/LineSegmentIntersector>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgFX/Scribe>
#include <iostream>
#include <osg/MatrixTransform>
class CEventRect :
	public osgGA::GUIEventHandler
{
public:
	CEventRect(osg::ref_ptr<osgEarth::MapNode> mapNode1,CDisDlg ** addlg);
	~CEventRect(void);
	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
	void isStartTestArea(bool isTest);
	bool isStartTest1;
	osg::ref_ptr<osgEarth::MapNode> mapNode1;
	osg::ref_ptr<osg::Geode> polygon;
	osg::ref_ptr<osg::Geode> xiaoqiu;
	osg::ref_ptr<osg::Vec3Array> vertexrect;
	osg::Vec3d beginpoint;
	osg::Vec3d midpoint;
	osg::Vec3d endpoint;
	int firstdbc;
	osg::ref_ptr<osg::Group> LineRoot;
	osg::ref_ptr<osg::Geometry> geom;
	osg::ref_ptr<osg::StateSet> state;
	osg::ref_ptr<osg::Geode> RectLine;
	osg::Vec3Array::iterator iter;
	float GetAera(osg::ref_ptr<osg::Vec3Array> vetex);//计算不规则多边形面积
	float LineInter(osg::Vec3d point1,osg::Vec3d point2);
	int jilu;
	CDisDlg * *DisDlgShow;
	osg::ref_ptr<osg::Group> mLabels3;
	osg::ref_ptr<osgEarth::MapNode> mapNode3;
public:
	float beginx,beginy;
	float endx,endy;

};

