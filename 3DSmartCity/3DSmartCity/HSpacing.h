#include "HeadFiles.h"
#include "HSpacingDlg.h"
#include "HighLight.h"
#include "DBConnection.h"

#pragma once
class HSpacing:
	public osgGA::GUIEventHandler
{
public:
	HSpacing(MapNode* mapNode,osgViewer::Viewer* viewer,bool * isStart);
	~HSpacing(void);

	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
	Node *pick(double x,double y);
	string setValue(Node *node);
	void computeHSpace(string bzm1,string bzm2);

public:

	Node *node1,*node2;
	NodeList nodes;
	string bzm1,bzm2;
	bool isFirstTime;
	bool *isStart;
	osgUtil::LineSegmentIntersector::Intersections intersection;

	MapNode *mapNode;
	osgViewer::Viewer *viewer;
	HSpacingDlg *mHSpacingDlg;
	CHighLight *highLight;

	DBConnection *DBclass;
	PGconn *conn;
	PGresult *res;
};

