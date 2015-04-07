#include "StdAfx.h"
#include "HighLight.h"


CHighLight::CHighLight(void)
{
	oldColor=Vec4f(0.0,0.0,1.0,0.8);
}


CHighLight::~CHighLight(void)
{
}
void CHighLight::setHighLight(NodeList nodes,osg::Vec4f newcolor)
{
	osg::ref_ptr<osg::Geometry> tmpGeom1,tmpGeom2;
	osg::ref_ptr<osg::Geode> tmpGeonode;
	osg::ref_ptr<osg::Vec4Array> tmpColorArray;
	//恢复之前点的颜色
	if (0!=oldNodes.size())
	{
		for (std::vector<osg::ref_ptr<osg::Node>>::iterator it = oldNodes.begin(); it != oldNodes.end(); ++it)
		{
			tmpGeonode=dynamic_cast<osg::Geode*>(it->get());
			tmpGeom1 = dynamic_cast<osg::Geometry*>(tmpGeonode->getDrawable(0));
			if(tmpGeom1)
			{
				tmpColorArray=dynamic_cast<osg::Vec4Array*>(tmpGeom1->getColorArray());
				tmpColorArray[0].clear();
				tmpColorArray[0].push_back(oldColor);
				tmpGeom1->dirtyDisplayList();	
			}
		}
	}
	
	oldNodes.clear();
	for (std::vector<osg::ref_ptr<osg::Node>>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		oldNodes.push_back(it->get());
		tmpGeonode=dynamic_cast<osg::Geode*>(it->get());
		tmpGeom2 = dynamic_cast<osg::Geometry*>(tmpGeonode->getDrawable(0));
		if(tmpGeom2)
		{
			tmpColorArray=dynamic_cast<osg::Vec4Array*>(tmpGeom2->getColorArray());
			oldColor=tmpColorArray[0][0];
			tmpColorArray[0].clear();
			tmpColorArray[0].push_back(newcolor);
			tmpGeom2->dirtyDisplayList();
		}
	}

}