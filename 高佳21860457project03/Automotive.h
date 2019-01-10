/* Copyright (c) 2009, �����׻������Ƽ����޹�˾
* All Rights reserved.
* �ļ����ƣ�StdAfx.h
* ժҪ������ʵ����
* ���ߣ��������������ʼ���
*/

#pragma once

#include "StdAfx.h"
#include "Vertex.h"
#include "AutoPart.h"


class myCar {
public:
	myCar(void);
	~myCar(void);
	
	double ready;//�趨���
	CVertex position;//λ��
	CVertex normal3f;//ԭʼ����//������//
	double rotx,roty,rotz;//��ת��
	
	int wheel_num;//��������
	AutoPartWheel * wheel;//���Ӳ���
	int viewangle;
	
	bool CreateDemoCar(void);
	bool CreateWheel(int n);
	bool Setpos(CVertex p);      //��������///����������ϵ�е�����
	bool SetOri(CVertex ori);    //����ԭ����
	bool Rotxyz(double x, double y, double z);//ת������
	bool ResetRot(void);          //��λ����
	bool CreateDemo4Wheel(double dx, double dy);
	bool DrawGL(void);
	
	bool MoveVector(CVertex v);
	bool WheelAllRot(double wrs, double wori);
	
	AutoPartBody * m_carbody;				//��ʾ�б�
	
	void MovingCalc(double * wrs, double * wori, myCar * car);//////�����ɹ�ʽ�ṩ������ݣ�ֱ���ƶ�,������Ϊ��������
};



class Automotive {
public:
	Automotive();
	~Automotive();
protected:
	;
private:
	;
};

