#include <stdlib.h>  
#include <GL/glut.h>  
#include <Windows.h>
#include <math.h>
#include<iostream>
#pragma comment(lib, "glut32.lib")  
using namespace std;
GLfloat roate = 0.0;// set rote of roate ying yu bu hao  bu zhuang le 设置旋转速率
GLfloat rote = 0.0;//shezhi旋转角度
GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//当左键按下时记录鼠标坐标  
GLfloat oldy;

//初始化
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色  
}

//显示
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); //使能深度检测

	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0); //画笔红色
	glEnable(GL_NORMALIZE);  //归一化法向量

	glLoadIdentity();  //加载单位矩阵  
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(rote, 0.0f, 1.0f, 0.0f);
	glRotatef(anglex, 1.0, 0.0, 0.0);
	glRotatef(angley, 0.0, 1.0, 0.0);
	glRotatef(anglez, 0.0, 0.0, 1.0);
	glutSolidTeapot(2.0);
	rote += roate;

	glPopMatrix();
	glutSwapBuffers();
}

//
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
//设置光照
void SetupLights()
{
	GLfloat ambientLight[] = { 0.2f,  0.2f,  0.2f,  1.0f };//环境光
	GLfloat diffuseLight[] = { 0.9f,  0.9f,  0.9f,  1.0f };//漫反射
	GLfloat specularLight[] = { 1.0f,  1.0f,  1.0f,  1.0f };//镜面光
	GLfloat lightPos[] = { 50.0f, 80.0f, 60.0f, 1.0f };//光源位置

	glEnable(GL_LIGHTING);								//启用光照
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);		//设置环境光源
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);		//设置漫反射光源
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);	//设置镜面光源
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);		//设置灯光位置
	glEnable(GL_LIGHT0);								//打开第一个灯光

	glEnable(GL_COLOR_MATERIAL);						//启用材质的颜色跟踪
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//指定材料着色的面
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //指定材料对镜面光的反应
	glMateriali(GL_FRONT, GL_SHININESS, 100);           //指定反射系数
}

//鼠标控制
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			roate = 0;
			rote = 0;
			oldx = x;//当左键按下时记录鼠标坐标  
			oldy = y;
		}

	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			roate = 1.0f;
		}
	}

}

//运动
void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	angley += 108 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	anglex += 108 * (GLfloat)deltay / (GLfloat)WinH;
	//anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标  
	oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控  
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);

	SetupLights();

	glutMainLoop();
	return 0;
}
