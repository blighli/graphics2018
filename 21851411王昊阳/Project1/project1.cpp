//
//  main.cpp
//  OpenGLTest
//
//  Created by 王昊阳 on 2018/12/13.
//  Copyright © 2018 王昊阳. All rights reserved.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glut/glut.h>
/* 初始摄像机位置 */
static GLdouble axix = 0.0,axiy = 0.0,z = 4.0;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();
    /* 设置照相机 */
    gluLookAt (axix, axiy, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 2.0, 1.0);
    /* 画茶壶 */
    glutWireTeapot(1.0);
    glFlush ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0,(GLfloat) w/(GLfloat) h,1.5,20.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd':
            axix += 1.0;
            glutPostRedisplay();
            break;
        case 'a':
            axix -= 1.0;
            glutPostRedisplay();
            break;
        case 'w':
            z -= 1.0;
            glutPostRedisplay();
            break;
        case 's':
            z += 1.0;
            glutPostRedisplay();
            break;
            // 正视图视角
        case '1':
            axix = 0.0;
            axiy = 0.0;
            z = 4.0;
            glutPostRedisplay();
            break;
            // 侧视图视角
        case '2':
            axix = 4.0;
            axiy = 0.0;
            z = 0.0;
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
