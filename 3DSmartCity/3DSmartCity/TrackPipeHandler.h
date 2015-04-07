#pragma once
#include <osg/Group>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include "TrackPipeDialog.h"
#include <osgEarth/MapNode>
#include <osgViewer/Viewer>
class TrackPipeHandler :
	public osgGA::GUIEventHandler
{

public:
	TrackPipeHandler(void);
	~TrackPipeHandler(void);
	TrackPipeHandler(CTrackPipeDialog** ppFlowDlg,osgViewer::Viewer* mViewer);
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

private:
	CTrackPipeDialog** ppTrackDlg;
	osgViewer::Viewer* mViewer;
	std::vector<std::string> oldBzms;

	void Pick(float x,float y );
};

