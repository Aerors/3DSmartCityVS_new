#include "StdAfx.h"
#include "TravelManipulator.h"

//构造函数
	CTravelManipulator::CTravelManipulator(void):m_movespeed(1.0f),
	m_leftdowm(false),
	m_pushX(0),
	m_angle(2.5),
	m_pengzhuang(true),
	m_pushY(0)
{
	m_position=osg::Vec3(-22.0f, -274.0f, 100.0f);
	m_rotation=osg::Vec3(osg::PI_2, 0.0f, 0.0f);
	ismanyou=false;
}


CTravelManipulator::~CTravelManipulator(void)
{

}

CTravelManipulator *CTravelManipulator::TravelToScene(osg::ref_ptr<osgViewer::Viewer> view)
{

	osg::ref_ptr<CTravelManipulator> camera=new CTravelManipulator;
	view->setCameraManipulator(camera);
	camera->m_view=view;
	return camera;
}
//设置矩阵
void CTravelManipulator::setByMatrix(const osg::Matrix& matrix)
{

}
//设置逆矩阵
void CTravelManipulator::setByInverseMatrix(const osg::Matrix& matrix)
{


}
//得到矩阵
osg::Matrix CTravelManipulator::getMatrix(void)const
{
	osg::Matrixd mat;
	mat.makeRotate(m_rotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),  
		m_rotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),  
		m_rotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));  
	return mat * osg::Matrixd::translate(m_rotation);

}
//得到逆矩阵
osg::Matrix CTravelManipulator::getInverseMatrix(void)const
{
	osg::Matrixd mat;  

	mat.makeRotate(m_rotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),  
		m_rotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),  
		m_rotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));  
	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_rotation));  

}
//事件处理函数
bool CTravelManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
{
	// 获取鼠标位置  
	float mouseX = ea.getX();  
	float mouseY = ea.getY();  
	if(ismanyou)
	{	
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):  
		{  
			// 空格键  
			if(ea.getKey() == 0x20)  
			{  
				us.requestRedraw();  
				us.requestContinuousUpdate(false);  
				return true;  
			}  
			// 上移键  
			if (ea.getKey() == 0xFF50)  
			{  
				ChangePosition(osg::Vec3(0, 0, m_movespeed));  

				return true;  
			}  
			// 下移键  
			if (ea.getKey() == 0xFF57)  
			{  
				ChangePosition(osg::Vec3(0, 0,-m_movespeed));  
				return true;  
			}  

			// 加速  
			if (ea.getKey() == 0x2B)  
			{  
				m_movespeed += 1.0f;  
				return true;  
			}  

			// 减少速度  
			if (ea.getKey() == 0x2D)  
			{  
				m_movespeed -= 0.1f;  
				if(m_movespeed < 1.0f)  
				{  
					m_movespeed = 1.0f;  
				}  
				return true;  
			}  

			// 前进  
			if (ea.getKey() == 0xFF52 || ea.getKey() == 0x57 || ea.getKey() == 0x77)  
			{  
				ChangePosition(osg::Vec3(0, m_movespeed * sinf(osg::PI_2 + m_rotation._v[2]), 0));  
				ChangePosition(osg::Vec3(m_movespeed * cosf(osg::PI_2 + m_rotation._v[2]),0,0));  
				return true;  
			}  

			// 后退  
			if (ea.getKey() == 0xFF54 || ea.getKey() == 0x53 || ea.getKey() == 0x73)  
			{  
				ChangePosition(osg::Vec3(0, -m_movespeed * sinf(osg::PI_2 + m_rotation._v[2]), 0));  
				ChangePosition(osg::Vec3(-m_movespeed * cosf(osg::PI_2 + m_rotation._v[2]),0,0));  
				return true;  
			}  

			// 向左  
			if (ea.getKey() == 0x41 || ea.getKey() == 0x61)  
			{  
				ChangePosition(osg::Vec3(0, m_movespeed * cosf(osg::PI_2 + m_rotation._v[2]),0));  
				ChangePosition(osg::Vec3(-m_movespeed * sinf(osg::PI_2 + m_rotation._v[2]),0,0));  
				return true;  
			}  

			// 向右  
			if (ea.getKey() == 0x44 || ea.getKey() == 0x64)  
			{  
				ChangePosition(osg::Vec3(0, -m_movespeed * cosf(osg::PI_2 + m_rotation._v[2]),0));  
				ChangePosition(osg::Vec3(m_movespeed * sinf(osg::PI_2 + m_rotation._v[2]),0,0));  
				return true;  
			}  

			// 向右转  
			if (ea.getKey() == 0xFF53)  
			{  
				m_rotation._v[2] -= osg::DegreesToRadians(m_angle);  
			}  

			// 向左转  
			if (ea.getKey() == 0xFF51)  
			{  
				m_rotation._v[2] += osg::DegreesToRadians(m_angle);  
			}  

			// 改变屏幕角度F键  
			if (ea.getKey() == 0x46 || ea.getKey() == 0x66)  
			{  
				m_angle -= 0.2;  
				return true;  
			}  

			//G键  
			if (ea.getKey() == 0x47 || ea.getKey() == 0x66)  
			{  
				m_angle += 0.2;  
				return true;  
			}  
			return true;  
		} 
		case(osgGA::GUIEventAdapter::PUSH):  

			if (ea.getButton() == 1)  
			{  
				m_pushX = mouseX;  
				m_pushY = mouseY;  

				m_leftdowm = true;  
			}  

			return true; 
			// 拖动  
		case(osgGA::GUIEventAdapter::DRAG):  

			if (m_leftdowm)  
			{  
				m_rotation._v[2] -= osg::DegreesToRadians(m_angle * (mouseX - m_pushX)) / 200;  
				m_rotation._v[0] += osg::DegreesToRadians(1.1 * (mouseY - m_pushY)) / 200;  

				if (m_rotation._v[0] >= 3.14)  
				{  
					m_rotation._v[0] = 3.14;  
				}  

				if (m_rotation._v[0] <= 0)  
				{  
					m_rotation._v[0] = 0;  
				}  
			}  
			return false;  
			// 鼠标释放  
		case(osgGA::GUIEventAdapter::RELEASE):  

			if (ea.getButton() == 1)  
			{  
				m_leftdowm = false;  
			}  

			return false;  

		default:  
			return false;  

	}
	}
return false;
}


//位置变换函数
void CTravelManipulator::ChangePosition(osg::Vec3& delta)
{
	if(m_pengzhuang)
	{
		//得到新的位置
		osg::Vec3 newposi1=m_position+delta;
		osgUtil::IntersectVisitor ivXY;
		//根据新的位置得到两条线段检测
		osg::ref_ptr<osg::LineSegment> lineXY=new osg::LineSegment(newposi1,m_position);
		osg::ref_ptr<osg::LineSegment> lineZ=new  osg::LineSegment(newposi1 + osg::Vec3(0.0f, 0.0f, 10.0f), newposi1 - osg::Vec3(0.0f, 0.0f, -10.0f));
		ivXY.addLineSegment(lineZ.get());
		ivXY.addLineSegment(lineXY.get());
		//结构交集检测
		m_view->getSceneData()->accept(ivXY);
		//如果没有碰撞检测
		if(!ivXY.hits())
		{
			m_position=m_rotation+delta;
		}
	}
	else
	{
		m_position=m_position+delta;
	}
}
//设置速度
float CTravelManipulator::getSpeed()
{
    return m_movespeed;
}
void  CTravelManipulator::setSpeed(float &sp)
{
	m_movespeed=sp;
}
//设置起始位置
osg::Vec3 CTravelManipulator::getPositon()
{
	return m_position;
}
void  CTravelManipulator::setPosition(osg::Vec3 &position)
{
	m_position=position;
}

void CTravelManipulator::isManyou(bool ismanyou1)
{
	ismanyou=ismanyou1;
}



