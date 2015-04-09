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
	
	BOOL isPickWorld;//�Ƿ��������ͼ
	
	void isStartTest(bool isTest);

public:
	CEventHandlerDistance(osg::ref_ptr<osgEarth::MapNode> mapNode1,CDisDlg ** addlg,bool *isWindowClose);
	~CEventHandlerDistance(void);
	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

	osg::Vec3d IntersectPoint(osg::Vec3d XPosition,osg::Vec3d YPosition,osg::ref_ptr<osg::Node> Node);
	bool isTestJu;
	double GetDis(osg::Vec3d form,osg::Vec3d to);
	double GetDis1(osg::ref_ptr<osg::Vec3Array> vec);
	//״̬��
	//0�û�û��˫��
	//1���������
	//2�������յ�
	int jieduan;	
	CEventHandlerDistance *mDIS;
	CDisDlg * *DisDlgShow;
	bool * isWindowClose1;
	osg::ref_ptr<osg::Group> mLabels3;
	osg::ref_ptr<osgEarth::MapNode> mapNode3;
	osg::ref_ptr<osg::Group> myRoot;
	osg::ref_ptr<osg::Group> myRoot1;
	osg::ref_ptr<osg::Geode> lineStrip;//��
	osg::ref_ptr<osg::Geode> lineStrip1;//��

	osg::ref_ptr<osg::Group> StartandEnd;
	osg::ref_ptr<osgEarth::MapNode> mapNode1;
	osg::Vec3d startPoint;//��ʼ��
	osg::Vec3d midPoint;//�м��
	osg::Vec3d endPoint;//������
	osg::ref_ptr<osg::Vec3Array> vertex;//����

	int Jilu;
	osg::ref_ptr<osg::CoordinateSystemNode> csn;
	//GeoPoint ConvertPoint;

	//�ı�
	osg::ref_ptr<osg::Geode> wenben;

};

