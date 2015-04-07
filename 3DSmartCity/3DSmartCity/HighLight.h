#pragma once
#include <vector>
#include "HeadFiles.h"
using namespace osg;
class CHighLight
{
public:
	CHighLight(void);
	~CHighLight(void);

	//高亮操作
	void setHighLight(NodeList nodes,osg::Vec4f newcolor);

public:
	//用来临时存储本次高亮的节点和之前的颜色,以便恢复颜色
	NodeList oldNodes;
	osg::Vec4f oldColor;

};

