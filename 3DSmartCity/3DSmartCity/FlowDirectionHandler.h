#pragma once
#include <osg/Group>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include "FlowDirectionDialog.h"
#include <osgEarth/MapNode>
#include <osgViewer/Viewer>
class FlowDirectionHandler :
	public osgGA::GUIEventHandler
{
public:
	FlowDirectionHandler(void);
	~FlowDirectionHandler(void);
	FlowDirectionHandler(FlowDirectionDialog** ppFlowDlg,osgViewer::Viewer* mViewer);

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

private:
	FlowDirectionDialog** ppFlowDlg;
	osgViewer::Viewer* mViewer;
	std::vector<std::string> oldBzms;

	void Pick(float x,float y );
};

