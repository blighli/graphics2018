//
//  main.cpp
//  project03
//
//  Created by weipingw on 2019/1/12.
//  Copyright © 2019 weipingw. All rights reserved.
//

#include <iostream>

#include <math.h>
#include "model_loader.hpp"

using namespace std;

#define  GLUT_WHEEL_UP        3
#define  GLUT_WHEEL_DOWN    4
const int winWeight = 600, winHeight = 600;
string filePath = "./nanosuit/nanosuit.obj";
ObjLoader objModel = ObjLoader(filePath);
GLfloat defaultMatrix[16];
GLfloat currentMatrix[16];
GLfloat distance_z;
bool mouseLefeDown = false, mouseRightDown = false;
int bufX = 0, bufY = 0;

void setLightRes() {
    
    GLfloat mat_specular[] = { 1.0, 0.5, 0.0, 1.0 };  //镜面反射参数
    GLfloat mat_shininess[] = { 10.0 };               //高光指数
    //材质属性
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    const GLfloat glfLight0Ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    const GLfloat glfLight1Ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    const GLfloat glfLight0Diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    const GLfloat glfLight1Diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    const GLfloat glfLight0Specular[] = { 1.0, 0.0, 0.0, 1.0 };
    const GLfloat glfLight1Specular[] = { 0.0, 0.0, 1.0, 1.0 };
    const GLfloat glPosition0[] = { 0,20,-1,1 };
    const GLfloat glPosition1[] = { 0,20,1,1 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, glfLight0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glfLight0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, glfLight0Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, glPosition0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, glfLight1Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, glfLight1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, glfLight1Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, glPosition1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);//两面照亮
    glEnable(GL_LIGHTING);//启用光照
    glEnable(GL_LIGHT0);//打开光源
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);//启用颜色追踪
    glFrontFace(GL_CCW);// 指定逆时针绕法表示多边形正面
}
/*初始化
 */
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 30.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(100.0, 100.0, 100.0, .0, 0.0, 0.0, .0, 1.0, 0.0);
    gluLookAt(100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    distance_z = 100.0f * sqrt(3.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, defaultMatrix);
    memcpy(currentMatrix, defaultMatrix, sizeof(defaultMatrix));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

/* 显示
 */
void display()
{
    static int z = 0;
    GLfloat earth_moon_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };//地球月亮环境光照
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(currentMatrix);
    setLightRes();
    //glutSolidTeapot(8);
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_moon_ambient);
    objModel.Draw();
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, h - winWeight, winWeight, winHeight);
}

/* 在绝对坐标系下进行平移、旋转变换
 */
void addTranslate(GLfloat x, GLfloat y, GLfloat z)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();                                                                        // 加载单位矩阵
    glTranslatef(x, y, z);                                                                    // 平移
    glMultMatrixf(currentMatrix);                                                             // 变换矩阵左乘当前矩阵
    glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
    glPopMatrix();
}
void addRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();                                                                        // 加载单位矩阵
    glTranslatef(.0, .0, -distance_z);                                                        // z轴平移复原
    glRotatef(angle, x, y, z);                                                                // 旋转
    glTranslatef(.0, .0, distance_z);                                                        // z轴平移重做
    glMultMatrixf(currentMatrix);                                                            // 变换矩阵左乘当前矩阵
    glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
    glPopMatrix();
}

void mouse(int button, int state, int x, int y)
{
    y = winHeight - y;
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLefeDown = true;
            bufX = x; bufY = y;
        }
        else {
            mouseLefeDown = false;
            bufX = bufY = 0;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseRightDown = true;
            bufX = x; bufY = y;
        }
        else {
            mouseRightDown = false;
            bufX = bufY = 0;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a')
    {
        //cout << "scale up" << endl;
        glScalef(.9f, .9f, .9f);
        glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
        glutPostRedisplay();
    }
    if (key == 's')
    {
        //cout << "scale down" << endl;
        glScalef(1.1f, 1.1f, 1.1f);
        glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    y = winHeight - y;
    if (bufX >= 0 && bufY >= 0 && (bufX != x || bufY != y)) {
        GLfloat deltax = GLfloat(x - bufX);
        GLfloat deltay = GLfloat(y - bufY);
        if (mouseRightDown) {
            addTranslate(deltax * .2f, deltay * .2f, .0f);
            glutPostRedisplay();
        }
        else if (mouseLefeDown) {
            GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
            addRotate(dis*.5f, -deltay / dis, deltax / dis, .0);
            glutPostRedisplay();
        }
    }
    bufX = x;
    bufY = y;
}

/*操作提示
 */
void printInstrument() {
    printf("操作提示！\n·旋转物体：按下鼠标【左键】拖拽\n·移动物体：按下鼠标【右键】拖拽\n·缩小物体：a \n 放大物体：s");
}

/*主函数
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);                                                                        //初始化GLUT
    glutInitWindowSize(winWeight, winHeight);                                                    //初始窗口大小
    glutInitWindowPosition(300, 0);                                                                //初始窗口位置
    glutCreateWindow("project03");                                                  //创建窗口，指定窗口名称
    printInstrument();                                                                            //终端显示操作提示
    init();                                                                                        //调用初始化函数
    glutReshapeFunc(reshape);                                                                    //指定重绘函数
    glutDisplayFunc(display);                                                                    //指定显示内容函数
    glutMouseFunc(mouse);                                                                        //指定鼠标函数
    glutMotionFunc(motion);                                                                        //指定鼠标动作函数
    glutKeyboardFunc(keyboard);
    glutMainLoop();                                                                                //进入主循环并处理事件
    
    return 0;
}
