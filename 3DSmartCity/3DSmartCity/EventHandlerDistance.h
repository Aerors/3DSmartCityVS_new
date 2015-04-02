#pragma once
#include <osgUtil/LineSegmentIntersector>
#include <osgEarth/MapNode>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/Map>

class CEventHandlerDistance :
	public osgGA::GUIEventHandler
{
public:
	
	BOOL isPickWorld;//�Ƿ��������ͼ
	
	void isStartTest(bool isTest);

public:
	CEventHandlerDistance(void);
	~CEventHandlerDistance(void);
	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
	bool isTestJu;
	//״̬��
	//0�û�û��˫��
	//1���������
	//2�������յ�
	int jieduan;

	osg::ref_ptr<osg::Geode> lineStrip;//��

	osg::Vec3 startPoint;
	osg::Vec3 endPoint;
	osg::ref_ptr<osg::Vec3Array> vertex;//����
};

