//�Ӿ���
//ԭʼ����Ϊ��۾�
//�������Դ�������˽�һ�����������
//��������ĳ�����ʾ�Ĺ���

#include "VisionSimulation.h"
#include "3DS.H"

CLoad3DS *m_3ds;
GLuint  m_lilisit;

GameScene::GameScene(void)
{
	this->start = 0;
	this->Cars=NULL;
	this->rotx = -60;
	this->roty = 0;
	this->rotz = 40;
	this->deep = -15;
	this->scene = new CEnvironment;


	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; // ���������
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; // ��������

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); // ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); // ���������
}

GameScene::~GameScene(void)
{
}

bool GameScene::DrawGL(void)
{

		glLoadIdentity(); // ���õ�ǰ��ģ�͹۲����

		glEnable(GL_DEPTH_TEST); //
		glDisable(GL_BLEND); // �رջ��
		glEnable(GL_COLOR_MATERIAL); // ʹ����ɫ����-------------->

		/////////----------------
		/////-------------------------�ӽǴ���
		if (this->Cars->viewangle==0)//////////////-----------------�����ӽ�
		{
			///////------------------------------------
			glTranslatef(0.0f,0.0f,deep); // ������Ļ------
			glRotatef(rotx,1.0f,0.0f,0.0f);
			glRotatef(roty,0.0f,1.0f,0.0f);
			glRotatef(rotz,0.0f,0.0f,1.0f);
		}
		if (this->Cars->viewangle==3)//���ӽ�Ϊ3ʱ�������˳��ӽ�
		{			
			glTranslatef(0.0f,0.0f,deep); // ������Ļ------
			//////////---------------------------------------�ӽǱ仯
			glRotatef(- 70,  1.0f,0.0f,0.0f);
			glRotatef(  0,   0.0f,1.0f,0.0f);
			glRotatef(  0,   0.0f,0.0f,1.0f);
		}
		/////////-------��������
		{
			////////////////////--------------------------------------------------------------------����λ��
			glPushMatrix();
			if (this->Cars->viewangle==0)
			{
				//////////------------------------------------------------���ƹ�Դ
				///////----------------
				glPushMatrix();
					glTranslatef(5,5,10);// ��Դλ��
					GLfloat LightPosition[]= { 0, 0, 0, 1.0f }; 
					glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // ���ù�Դλ��
					glEnable(GL_LIGHTING); // ���ù�Դ
					glEnable(GL_LIGHT1); // ����һ�Ź�Դ
				glPopMatrix();
			}
			if (this->Cars->viewangle==3)//���ӽ�Ϊ�����˳��ӽ�ʱ������λ�÷�ת
			{
				glRotatef(  -this->Cars->rotx,   1.0f,0.0f,0.0f);
				glRotatef(  -this->Cars->roty,   0.0f,1.0f,0.0f);
				glRotatef(  -this->Cars->rotz,   0.0f,0.0f,1.0f);
				//////////------------------------------------------------���ƹ�Դ
				///////----------------
				glPushMatrix();
					glTranslatef(5,5,10);// ��Դλ��
					GLfloat LightPosition[]= { 0, 0, 0, 1.0f }; 
					glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // ���ù�Դλ��
					glEnable(GL_LIGHTING); // ���ù�Դ
					glEnable(GL_LIGHT1); // ����һ�Ź�Դ
				glPopMatrix();
				//////////-------------��Դд����������֮ǰ��̫��------��д��֮���ǵ���
				glTranslatef(- this->Cars->position.x,- this->Cars->position.y,- this->Cars->position.z);
			}
			///------------------------------------------////////////////----------------------------���Ƶ���
			{
				glPushMatrix();
				glTranslatef(0.0,0.0,-0.475);
				glTranslatef(-MAP,MAP,0.0);
				this->scene->DrawSand();
				glTranslatef(MAP,-MAP,0.0);

				glPopMatrix();
			}
			glPopMatrix();
		}
		if(this->Cars!=NULL)
		{
			this->Cars->DrawGL();
		}
	return false;
}
