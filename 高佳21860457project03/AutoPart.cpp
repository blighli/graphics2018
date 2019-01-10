//ԭʼ���ߣ�������
//AutoWheel��ο�����۾�������̥�˶��Ĳ���˼·
//�Լ�������д����̥�˶�����

#include "AutoPart.h"
#include "3DS.H"

AutoPartBody::AutoPartBody(char *filename,int n/* =0 */):AutoPart(filename,0){
	m_autoPartList = glGenLists(1);
	glNewList(m_autoPartList,GL_COMPILE);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glRotatef(180.0f,0.0f,1.0f,0.0f);
	m_3ds->show3ds(0,0.0,0.9,-0.25,0.3);
	glRotatef(-180.0f,0.0f,1.0f,0.0f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glEndList();
}

BOOL AutoPartBody::DrawGL(){
	glCallList(m_autoPartList);
	return TRUE;
}

AutoPartWheel::AutoPartWheel(char *filename,int n/* =0 */):AutoPart(filename,1){

	m_autoPartList = glGenLists(1);
	glNewList(m_autoPartList,GL_COMPILE);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glRotatef(180.0f,0.0f,1.0f,0.0f);
	m_3ds->show3ds(1,0.0,-0.1,0.0,0.3);
	glRotatef(-180.0f,0.0f,1.0f,0.0f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glEndList();

	this->rotx=0;
	this->roty=0;
	this->rotz=0;
	
	this->blend = 0;
	this->blendf= 1;
	
	this->distance=0;
	this->rotable=0;
	this->speed=0;
}


BOOL AutoPartWheel::Set(CVertex newpos)//������ԭ��λ��//�ƶ���ĳ����
{
	this->pos=newpos;
	return true;
}

BOOL AutoPartWheel::Rotxyz(double x, double y, double z)
{
	if (rotable==1)
	{
		this->rotx+=x;
		this->roty+=y;
		this->rotz+=z;
	}
	return true;
}

BOOL AutoPartWheel::DrawGL(void)
{
	glPushMatrix();

	glTranslatef(this->pos.x,this->pos.y,this->pos.z);
	if (this->rotable==1)
	{
			glRotatef(0,1.0f,0.0f,0.0f); // ��X����ת
			glRotatef(0,0.0f,1.0f,0.0f); // ��Y����ת
			glRotatef(rotz-rot_fa.z,0.0f,0.0f,1.0f); // ��Z����ת
	}
	{

		while (distance>360) distance-=360;
		while (distance<-360) distance+=360;
		glRotatef(distance,1.0f,0.0f,0.0f); // ��X����ת
		glRotatef(0,0.0f,1.0f,0.0f); // ��Y����ת
		glRotatef(0,0.0f,0.0f,1.0f); // ��Z����ת
	}
	glTranslatef(0.0f,-0.0f,0.1f);
	glCallList(m_autoPartList);
	glTranslatef(0.0f,0.0f,0.0f);    
	glPopMatrix();
	return false;
}
