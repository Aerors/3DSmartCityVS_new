#pragma once
#include "HeadFiles.h"
#include "DBConnection.h"
#include <string>
#include "CSectionDlg.h"
#include "HighLightVisitor.h"

class CCSection:public osgGA::GUIEventHandler
{
public:
	//CCSection(MapNode* mapNode,osgViewer::Viewer* viewer,osg::Group * linesGroup,bool * isDrawLineOver,CCSectionDlg ** sectionDlg);	
	CCSection(MapNode* mapNode,osgViewer::Viewer* viewer,osg::Group * linesGroup,bool * isDrawLineOver);	
	~CCSection(void);
	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
	void findPipes(GeoPoint startPoint,GeoPoint endPoint);

public:
	bool * isDrawLineStart;
	bool clickTime;
	MapNode * mapNode;
	osgViewer::Viewer * mViewer;
	GeoPoint startPoint;
	GeoPoint endPoint;
	osg::ref_ptr<osg::Group> linesGroup;
	
	DBConnection *DBclass;
	PGconn *conn;
	PGresult *res;
	std::vector<std::string> bzms;//保存上次查询到的标识码
	//CCSectionDlg **sectionDlg;
	CCSectionDlg *sectionDlg;

};

