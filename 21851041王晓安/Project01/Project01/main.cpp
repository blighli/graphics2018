//
//  main.cpp
//  Project01
//
//  Created by wxaaaa on 2018/12/17.
//  Copyright © 2018 wxaaaa. All rights reserved.
//

#include <iostream>

#include <GLUT/glut.h>
#include <math.h>

const double PI = acos(-1.0);
static int width = 800, height = 600;
static float cameraPos = 3.0f, cameraY = 0.0f;
static float c = PI / 180.0;
static int angle = 270;
static int prevX = -1, prevY = -1;
static float newSize = 1.0f, zoomStep = 0.05f;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //单位矩阵
    glLoadIdentity();
    // 相机
    gluLookAt(cameraPos*cos(c*angle), cameraY, cameraPos*sin(c*angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // 紫色
    glColor3f(1.0, 0.0, 1.0);
    // 缩放
    glScalef(newSize, newSize, newSize);
//    glutSolidTeapot(0.75f);
    glutWireTeapot(0.75f);
    // 交换缓冲
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        prevX = x, prevY = y;
    }
}

void keyboard (unsigned char key, int x, int y){
    if (key == 27){
        exit(0);
    }
}
void onMouseMove(int x, int y) {
    angle += x - prevX;
    cameraY += 0.05 * (y - prevY);
    prevX = x, prevY = y;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, (float)w / h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
    glutInitWindowSize(width, height);
    glutCreateWindow("teapot");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(onMouseMove);
    glutMainLoop();
    return 0;
}
