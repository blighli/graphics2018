//
//  main.cpp
//  Project01
//
//  Created by 黄小洁 on 2018/12/17.
//  Copyright © 2018 黄小洁. All rights reserved.
//

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <GLUT/GLUT.h>

static GLdouble axix = 0.0 ,axiy =0.0,axiz = 5.0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 0.0);
    glLoadIdentity ();
    /* 设置照相机 */
    gluLookAt (axix, axiy, axiz, 0.0 , 0.0, 0.0, 0.0, 1.0, 0.0);
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
        case 'a':
            axix -= 1.0;
            glutPostRedisplay();
            break;
        case 'd':
            axix += 1.0;
            glutPostRedisplay();
            break;
        case 'w':
            axiz += 1.0;
            glutPostRedisplay();
            break;
        case 's':
            axiz -= 1.0;
            glutPostRedisplay();
            break;
            // 复位
        case 'r':
            axix = 0.0;
            axiy = 0.0;
            axiz = 5.0;
            glutPostRedisplay();
            break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (300, 300);
    glutInitWindowPosition (300, 300);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
