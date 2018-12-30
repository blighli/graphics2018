#include "pch.h"

#include <stdlib.h>  
#include <GL/glut.h>  
#include <Windows.h>
#include <math.h>
#include<iostream>
#pragma comment(lib, "glut32.lib")  
using namespace std;

const int n = 20;
const GLdouble R = 0.5f;
const GLdouble R = 0.5f;
const GLdouble Pi = 3.1415926536f;
const GLdouble factor = 0.1f;

static int day = 0; // day的变化：从0到359

//显示
void display(void)
{
	glClearColor(0.8, 0.8, 0.8, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 400000000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -400000000, 400000000, 0, 0, 0, 0, 0, 1);
	
	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

	}
	//绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);


		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidSphere(69600000, 20, 20);
	}

	//绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 50.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		//地球半径
		GLdouble earth_radio = 15945000.0f;
		//日地距离
		GLdouble earth_sun_radio = 150000000.0f;
		//日地角度
		GLdouble earth_angle = day / 360.0 * 2 * Pi;

		glColor3f(0.0f, 0.0f, 1.0f);
		glRotatef(earth_angle / 2.0 / Pi * 360.0, 0.0f, 0.0f, -1.0f);
		glTranslatef(earth_sun_radio, 0.0f, 0.0f);
		glutSolidSphere(earth_radio, 20, 20);
	}

	//绘制月球
	{
		GLfloat earth_mat_ambient[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 100.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		//月球半径
		GLdouble month_radio = 4345000.0f;
		//地月距离
		GLdouble month_earth_radio = 38000000.0f;
		//地月角度
		GLdouble month_earth_angle = (day % 30) / 30.0 * 2 * Pi;

		glColor3f(1.0f, 1.0f, 0.0f);
		glRotatef(month_earth_angle / 2.0 / Pi * 360.0, 0.0f, 0.0f, -1.0f);
		glTranslatef(month_earth_radio, 0.0f, 0.0f);
		glutSolidSphere(month_radio, 20, 20);
	}

	glFlush();

	glutSwapBuffers();
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

void idle(void) {
	++day;
	if (day >= 360) {
		day = 0;
	}
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SolarSystem");
	glutDisplayFunc(display);

	glutIdleFunc(idle);

	SetupLights();

	glutMainLoop();
	return 0;
}