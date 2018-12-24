//
//  main.cpp
//  Project 1
//
//  Created by 祈越 on 2018/12/17.
//  Copyright © 2018 QiyueX. All rights reserved.
//
//

#include <iostream>
#include <cmath>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#define PI 3.1415926535

static int windowWidth = 600;
static int windowHeight = 600;

static int angelWithX = 90;
static int originX = -1;
static int originY = -1;
static float viewPointDistance = 2.0;
static float viewPointHeight = 0.0;
static float angelToRadius = PI / 180.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    // 问题：在macOS Mojave、Xcode10环境下必须调用glutReshapeWindow，并且参数必须与glutInitWindowSize不同，否则会出现黑屏什么都不显示的问题
    // 参见：https://stackoverflow.com/questions/52509427/mac-mojave-opengl
    glutReshapeWindow(windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX), viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireTeapot(0.5);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        originX = x;
        originY = y;
    }
}

void mouseMove(int x, int y) {
    angelWithX += x - originX;
    viewPointHeight += 0.03 * (y - originY);
    if (viewPointHeight > 1.0) {
        viewPointHeight = 1.0;
    }
    else if (viewPointHeight < -1.0) {
        viewPointHeight = -1.0;
    }
    originX = x;
    originY = y;
}

void specialKey(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        if (viewPointDistance > 1.5) {
            viewPointDistance -= 0.1;
        }
    }
    if (key == GLUT_KEY_DOWN) {
        if (viewPointDistance < 3.0) {
            viewPointDistance += 0.1;
        }
    }
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(100, 100);
    glutCreateWindow("Project 1");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutSpecialFunc(specialKey);
    glutMainLoop();
    return 0;
}
