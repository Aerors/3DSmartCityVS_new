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
	CTravelManipulator(void);//���캯��
	~CTravelManipulator(void);//��������
	//�����μ��뵽����֮��
	static CTravelManipulator *TravelToScene(osg::ref_ptr<osgViewer::Viewer> view);
private:
	osg::ref_ptr<osgViewer::View> m_view;
	//�ƶ��ٶ�
	float m_movespeed;
	osg::Vec3 m_position;
	osg::Vec3 m_rotation;
	bool ismanyou;
public:
	//�������Ƿ���
	float m_leftdowm;
	//���X,Y
	float m_pushX;
	float m_pushY;
	//���þ���
	virtual void setByMatrix(const osg::Matrix& matrix);
	//���������
	virtual void setByInverseMatrix(const osg::Matrix& matrix);
	//�õ�����
	virtual osg::Matrix getMatrix(void)const;	
	//�õ������
	virtual osg::Matrix getInverseMatrix(void)const;
	//�¼�������
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);
	//��Ļ�Ƕ�
	float m_angle;
	//λ�ñ任����
	void ChangePosition(osg::Vec3& delta);
	//��ײ����Ƿ���
	bool m_pengzhuang;
	//�����ٶ�
	float getSpeed();
	void  setSpeed(float &sp);
	//������ʼλ��
	osg::Vec3 getPositon();
	void  setPosition(osg::Vec3 &position);
    void isManyou(bool ismanyou1);

};

