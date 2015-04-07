#include "StdAfx.h"
#include "HighLightVisitor.h"
#include <osg/Geometry>

HighLightVisitor::HighLightVisitor(std::string str,bool makeithighlight,osg::Vec4f color)
	:osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
{
	m_bzm = str;
	highlightFlag = makeithighlight;
	this->color = color;
	this->hasEndFlag = false;
}

HighLightVisitor::HighLightVisitor(std::string str,bool makeithighlight,osg::Vec4f colorBegin,osg::Vec4f colorEnd)
	:osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
{
	m_bzm = str;
	highlightFlag = makeithighlight;
	this->color = colorBegin;
	this->colorEnd = colorEnd;
	this->hasEndFlag = true;
}

HighLightVisitor::~HighLightVisitor(void)
{
}

//void HighLightVisitor::apply(osg::Node& node)
//{
//	std::string s = node.getName();
//}

void HighLightVisitor::apply(osg::Geode& node)
{
	if(node.getName() == m_bzm)
	{
		osg::Geometry* tmpGeom = dynamic_cast<osg::Geometry*>(node.getDrawable(0));
		if(highlightFlag)
		{
			if(tmpGeom)
			{
				osg::Vec4Array* tmpColorArray = dynamic_cast<osg::Vec4Array*>(tmpGeom->getColorArray());
				if(!this->hasEndFlag)
				{
					if(tmpColorArray)
					{
						osg::Vec4Array::iterator iter = tmpColorArray->begin();
						for(iter; iter!=tmpColorArray->end(); iter++)
						{
							iter->set(color.r(),color.g(),color.b(),color.a());
						}
					}
				}else
				{
					if(tmpColorArray)
					{
						/*osg::Vec4Array::iterator iter = tmpColorArray->begin();
						for(iter; iter!=tmpColorArray->end(); iter++)
						{
							iter->set(color.r(),color.g(),color.b(),color.a());
						}*/
						tmpColorArray->erase(tmpColorArray->begin(),tmpColorArray->end());
						tmpColorArray->push_back(color);
						tmpColorArray->push_back(colorEnd);
					}
				}
				
				
			}
		}else
		{
			if(tmpGeom)
			{
				osg::Vec4Array* tmpColorArray = dynamic_cast<osg::Vec4Array*>(tmpGeom->getColorArray());
				if(tmpColorArray)
				{
					osg::Vec4Array::iterator iter = tmpColorArray->begin();
					for(iter; iter!=tmpColorArray->end(); iter++)
					{
						iter->set(0.0,0.0,1.0,0.8);
					}
				}
			}
		}
		
		tmpGeom->dirtyDisplayList();
		return;
	}
}

//void HighLightVisitor::apply(osg::Group& node)
//{
//	std::string s = node.getName();
//	int num = node.getNumChildren();
//	for(int i=0;i<num;i++)
//	{
//
//	}
//}