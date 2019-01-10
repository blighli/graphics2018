/* Copyright (c) 2009, �����׻������Ƽ����޹�˾
* All Rights reserved.
* �ļ����ƣ�StdAfx.h
* ժҪ�����Ĳ���
* ���ߣ��������������ʼ���
*/

#pragma once

#include "StdAfx.h"
#include "Vertex.h"
#include "3DS.h"

class AutoPart {
public:
	AutoPart(char *filename,int n=0){
		char appdir[666];
		GetCurrentDirectory(666,appdir);
		SetCurrentDirectory("Data");
		m_3ds=new CLoad3DS();
		m_3ds->Init(filename,n);
		SetCurrentDirectory(appdir);
	}
	virtual ~AutoPart(){
		delete m_3ds;
	}
	virtual BOOL DrawGL()=0;
protected:
	CLoad3DS *m_3ds;
	GLuint m_autoPartList;
private:
	;
};


class AutoPartBody:public AutoPart {
public:
	AutoPartBody(char *filename,int n=0);
	~AutoPartBody(){};
	BOOL DrawGL();
protected:
	;
private:
	;
};

class AutoPartWheel:public AutoPart {
public:
	AutoPartWheel(char *filename="wheel.3ds",int n=1);
	~AutoPartWheel(){};
	BOOL Set(CVertex newpos);////////////////�൱��MOVE TO
	BOOL Rotxyz(double x, double y, double z);
	BOOL DrawGL();
public:
	GLdouble rotx,roty,rotz;
	GLdouble distance;
	GLdouble speed;
	CVertex pos;//λ�ã�ԭ��
	CVertex rot_fa;///����������ת��
	int rotable;
	int blend;
	int blendf;
private:
	;
};




