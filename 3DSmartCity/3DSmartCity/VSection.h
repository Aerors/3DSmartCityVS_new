#include "HeadFiles.h"
#include "VSectionDlg.h"
#include "HighLight.h"
#include "DBConnection.h"
#include "VSectionDlg.h"

#pragma once

class VSection:public osgGA::GUIEventHandler
{
public:
	VSection(MapNode* mapNode,osgViewer::Viewer* viewer,bool * isStart);
	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
	~VSection(void);

	osg::NodeList VSection::findPipe(double x, double y,osgUtil::LineSegmentIntersector::Intersections intersection);


public:
	MapNode *mapNode;
	osgViewer::Viewer *viewer;
	bool *isStart;
	VSectionDlg *sectionDlg;
	CHighLight *highLight;

	DBConnection *DBclass;
	PGconn *conn;
	PGresult *res;
};

