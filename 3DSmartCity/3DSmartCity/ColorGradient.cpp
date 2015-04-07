#include "StdAfx.h"
#include "ColorGradient.h"

ColorGradient::ColorGradient(osg::Vec4f color,int rank)
{
	float off = (1.0-0.1)/(rank-1);
	colors = new osg::Vec4f[rank];
	for(int i=0;i<rank;i++)
	{
		float f = 1-off*i;
		osg::Vec4f tm(color.r()*f,color.g()*f,color.b()*f,f);
		colors[i] = tm;
	}
}
ColorGradient::ColorGradient(osg::Vec4f colorBegin,osg::Vec4f colorEnd,int rank)
{
	/*int i,j;
	float off = 1.0/(rank-1);
	colors = new osg::Vec4f[rank];
	for(i=rank-1,j=0;i>=0;i--,j++)
	{
		osg::Vec4f tm(colorBegin.r()*i*off+colorEnd.r()*j*off, colorBegin.g()*i*off+colorEnd.g()*j*off, colorBegin.b()*i*off+colorEnd.b()*j*off, 0.3); 
		colors[i] = tm;
	}*/
	colors = new osg::Vec4f[2];
	colors[0] = colorBegin;
	colors[1] = colorEnd;
}
ColorGradient::~ColorGradient(void)
{
	delete [] colors;
}


osg::Vec4f* ColorGradient::getColorArray()
{
	return colors;
}