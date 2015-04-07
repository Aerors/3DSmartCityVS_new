#pragma once
#include <osg/NodeVisitor>
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
class HighLightVisitor :
	public osg::NodeVisitor
{
public:
	HighLightVisitor(std::string str,bool makeithighlight,osg::Vec4f color=osg::Vec4f(1.0,1.0,0.0,0.5));
	HighLightVisitor(std::string str,bool makeithighlight,osg::Vec4f colorBegin,osg::Vec4f colorEnd);//ֻΪ�������Դ--�յ���ɫ
	~HighLightVisitor(void);

	virtual void apply(osg::Geode& node);

private:
	std::string m_bzm;//����+��ʶ��
	bool		highlightFlag;
	osg::Vec4f	color;
	osg::Vec4f	colorEnd;//ֻΪ�������Դ--�յ���ɫ
	bool		hasEndFlag;
};

