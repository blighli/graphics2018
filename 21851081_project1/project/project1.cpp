// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>  
#include <GL/glut.h>  
#include<iostream>
#pragma comment(lib, "glut32.lib")  
using namespace std;


void init(void)
{
	glClearColor(0.2, 0.2, 0.2, 1.0); //背景颜色，随便编了一个  
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); 
	glLoadIdentity();    
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glutWireTeapot(2); //变量是size;
	
	
	glutSwapBuffers();
}

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


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutIdleFunc(display);
	glutMainLoop();

	system("pause");
	return 0;
}


