//
//  main.cpp
//  project01
//
//  Created by weipingw on 2018/12/18.
//  Copyright © 2018年 weipingw. All rights reserved.
//

#include <GLUT/glut.h>
#include<iostream>
using namespace std;

GLfloat base_distance = 8.0;
GLfloat distance_radio = 1.0; // distance = base_distance * distance_radio
GLfloat roate = 0.0;// set rate of roate
GLfloat rote = 0.0;// set the angle of roate
GLfloat anglex = 0.0;// X aris
GLfloat angley = 0.0;//Y aris
GLfloat anglez = 0.0;//Z aris
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx; //old coordinates
GLfloat oldy;
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); //set black background
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, base_distance*distance_radio, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rote, 0.0f, 1.0f, 0.0f);
    glRotatef(anglex,1.0,0.0,0.0);
    glRotatef(angley,0.0,1.0,0.0);
    glRotatef(anglez,0.0,0.0,1.0);
    glutWireTeapot(2);
    rote += roate;
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
    gluLookAt(0.0, 0.0, base_distance*distance_radio, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            roate = 0;
            rote = 0;
            oldx = x;
            oldy = y;
            cout << "left" << endl;
        }
        
    }
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            roate += 1.0f;
            cout << "right" << endl;
        }
        
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a')
    {
        //roate += 1.0f;
        distance_radio -= 0.1;
        cout << "scale up" << endl;
    }
    if (key == 's')
    {
        //roate += 1.0f;
        distance_radio += 0.1;
        cout << "scale down" << endl;
    }
}

void motion(int x, int y)
{
    GLint deltax = oldx - x;
    GLint deltay = oldy - y;
    anglex  += 360 * (GLfloat)deltax / (GLfloat)WinW;
    angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
    anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
    oldx = x;
    oldy = y;
    glutPostRedisplay();
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
