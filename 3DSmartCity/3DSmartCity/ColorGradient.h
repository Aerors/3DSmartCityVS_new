#pragma once
#include <osg/Vec4f>
#include <osg/Array>
class ColorGradient
{
public:
	ColorGradient(osg::Vec4f color,int rank);
	ColorGradient(osg::Vec4f colorbegin,osg::Vec4f colorend,int rank);
	~ColorGradient(void);
	osg::Vec4f* getColorArray();

private:
	osg::Vec4f* colors;
};

