#pragma once
#include <vector>
#include "HeadFiles.h"
using namespace osg;
class CHighLight
{
public:
	CHighLight(void);
	~CHighLight(void);

	//��������
	void setHighLight(NodeList nodes,osg::Vec4f newcolor);

public:
	//������ʱ�洢���θ����Ľڵ��֮ǰ����ɫ,�Ա�ָ���ɫ
	NodeList oldNodes;
	osg::Vec4f oldColor;

};

