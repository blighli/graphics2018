//
//  main.cpp
//  Project01
//
//  Created by 钱立清 on 2018/12/18.
//  Copyright © 2018 钱立清. All rights reserved.
//

#include <iostream>

#include <GLUT/glut.h>
#include <math.h>

static int width = 800, height = 600;
static float cameraX = 5.0f, cameraY = 0.0f;
static float pro = acos(-1.0) / 180.0;
static int angle = 90;
static int prevX = -1, prevY = -1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX * cos(pro * angle), cameraY, cameraX * sin(pro * angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1.0f, 1.0f, 1.0f);
    glutWireTeapot(1.0f);
    glutSwapBuffers();
}

// 重绘函数
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, (float)w / h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

// 鼠标响应函数
void mouse (int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        prevX = x, prevY = y;
    }
}

// 键盘响应函数 UP->E DOWN->G LEFT->F RIGHT->D
void keyboard (unsigned char key, int x, int y){
    switch(key) {
        case GLUT_KEY_UP :
            cameraY ++; break;
        case GLUT_KEY_DOWN :
            cameraY --; break;
        case GLUT_KEY_LEFT :
            angle += 10; break;
        case GLUT_KEY_RIGHT :
            angle -= 10; break;
        case 27:
            exit(0);
    }
}

void motion(int x, int y) {
    angle += x - prevX;
    cameraY += 0.05 * (y - prevY);
    prevX = x, prevY = y;
}

int main(int argc, char* argv[]) {
    // 窗口初始化
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
    
    glutCreateWindow("teapot");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    
    // 响应函数
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}


