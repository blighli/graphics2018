//
//  main.cpp
//  Project01
//
//  Created by 黄小洁 on 2018/12/17.
//  Copyright © 2018 黄小洁. All rights reserved.
//
#include <GLUT/GLUT.h>

GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//当左键按下时记录鼠标坐标
GLfloat oldy;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0); //画笔黄色
    glLoadIdentity();  //加载单位矩阵
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(anglex,1.0,0.0,0.0);
    glRotatef(angley,0.0,1.0,0.0);
    glRotatef(anglez,0.0,0.0,1.0);
    glutWireTeapot(1.0);
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

void motion(int x, int y)
{
    GLint deltax = oldx - x;
    GLint deltay = oldy - y;
    anglex  += 360 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度
    angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
    anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
    oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
    oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutIdleFunc(display);
    glutMainLoop();
    return 0; 
}
