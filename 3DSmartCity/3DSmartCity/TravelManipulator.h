#pragma once
#include <osgViewer/Viewer>
#include <osg/LineSegment>
#include <osg/Point>
#include <osg/Geometry>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <vector>

class CTravelManipulator :
	public osgGA::CameraManipulator
{
public:
	CTravelManipulator(void);//构造函数
	~CTravelManipulator(void);//析构函数
	//把漫游加入到场景之中
	static CTravelManipulator *TravelToScene(osg::ref_ptr<osgViewer::Viewer> view);
private:
	osg::ref_ptr<osgViewer::View> m_view;
	//移动速度
	float m_movespeed;
	osg::Vec3 m_position;
	osg::Vec3 m_rotation;
	bool ismanyou;
public:
	//鼠标左键是否按下
	float m_leftdowm;
	//鼠标X,Y
	float m_pushX;
	float m_pushY;
	//设置矩阵
	virtual void setByMatrix(const osg::Matrix& matrix);
	//设置逆矩阵
	virtual void setByInverseMatrix(const osg::Matrix& matrix);
	//得到矩阵
	virtual osg::Matrix getMatrix(void)const;	
	//得到逆矩阵
	virtual osg::Matrix getInverseMatrix(void)const;
	//事件处理函数
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);
	//屏幕角度
	float m_angle;
	//位置变换函数
	void ChangePosition(osg::Vec3& delta);
	//碰撞检测是否开启
	bool m_pengzhuang;
	//设置速度
	float getSpeed();
	void  setSpeed(float &sp);
	//设置起始位置
	osg::Vec3 getPositon();
	void  setPosition(osg::Vec3 &position);
    void isManyou(bool ismanyou1);

};

