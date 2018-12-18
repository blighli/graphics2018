//
//  main.cpp
//  OpenGL第一次作业
//
//  Created by 宇宙无敌美少女 on 2018/12/18.
//  Copyright © 2018年 OPENGL2. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdio.h>
//圆周率宏
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH=0;
GLint SCREEN_HEIGHT=0;
//设置程序的窗口大小
GLint windowWidth=400;
GLint windowHeight=300;
//绕x轴旋转角度
GLfloat xRotAngle=0.0f;
//绕y轴旋转角度
GLfloat yRotAngle=0.0f;
//受支持的点大小范围
GLfloat sizes[2];
//受支持的点大小增量
GLfloat step;

enum MODELS{
    SPHERE=0,
    CONE,
    CUBE,
    TORUS,
    DODECAHEDRON,
    TEAPOT,
    OCTAHEDRON,
    TETRAHEDRON,
    ICOSAHEDRON
};
GLint iModel=SPHERE;
GLboolean bWire=GL_TRUE;
//菜单回调函数
void processMenu(int value){
    switch(value){
        case 1:
            iModel=SPHERE;
            break;
        case 2:
            iModel=CONE;
            break;
        case 3:
            iModel=CUBE;
            break;
        case 4:
            iModel=TORUS;
            break;
        case 5:
            iModel=DODECAHEDRON;
            break;
        case 6:
            iModel=TEAPOT;
            break;
        case 7:
            iModel=OCTAHEDRON;
            break;
        case 8:
            iModel=TETRAHEDRON;
            break;
        case 9:
            iModel=ICOSAHEDRON;
            break;
        case 10:
            bWire=GL_TRUE;
            break;
        case 11:
            bWire=GL_FALSE;
            break;
        default:
            break;
    }
    //重新绘制
    glutPostRedisplay();
}
//显示回调函数
void renderScreen(void){
    //将窗口颜色清理为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //将模板缓冲区值全部清理为1
    glClearStencil(1);
    //使能模板缓冲区
    glEnable(GL_STENCIL_TEST);
    //把整个窗口清理为当前清理颜色：黑色。清除深度缓冲区、模板缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //将当前Matrix状态入栈
    glPushMatrix();
    //坐标系绕x轴旋转xRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //坐标系绕y轴旋转yRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
    //进行平滑处理
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH,GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH,GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH,GL_NICEST);
    
    //白色绘制坐标系
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
    glVertex3f(-9.0f,0.0f,0.0f);
    glVertex3f(9.0f,0.0f,0.0f);
    glVertex3f(0.0f,-9.0f,0.0f);
    glVertex3f(0.0f,9.0f,0.0f);
    glVertex3f(0.0f,0.0f,-9.0f);
    glVertex3f(0.0f,0.0f,9.0f);
    glEnd();
    
    glPushMatrix();
    glTranslatef(9.0f,0.0f,0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,9.0f,0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,0.0f,9.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
    
    //设置绘画颜色为金色蓝色
    glColor3f(0.0, 0.0, 1.0);
    switch(iModel){
            //球
        case SPHERE:
            if(bWire){
                glutWireSphere(8.0f,20,20);
            }
            else{
                glutSolidSphere(8.0f,20,20);
            }
            break;
            //锥体
        case CONE:
            if(bWire){
                glutWireCone(4.0f,8.0f,20,20);
            }
            else{
                glutSolidCone(4.0f,8.0f,20,20);
            }
            break;
            //立体
        case CUBE:
            if(bWire){
                glutWireCube(8.0f);
            }
            else{
                glutSolidCube(8.0f);
            }
            break;
            //甜圈
        case TORUS:
            if(bWire){
                glutWireTorus(3.0f,6.0f,20,20);
            }
            else{
                glutSolidTorus(3.0f,6.0f,20,20);
            }
            break;
            //十六面体，默认半径1.0
        case DODECAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z轴均放大6倍
            if(bWire){
                glutWireDodecahedron();
            }
            else{
                glutSolidDodecahedron();
            }
            break;
            //茶壶
        case TEAPOT:
            if(bWire){
                glutWireTeapot(8.0f);
            }
            else{
                glutSolidTeapot(8.0f);
            }
            break;
            //八面体，默认半径1.0
        case OCTAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z轴均放大6倍
            if(bWire){
                glutWireOctahedron();
            }
            else{
                glutSolidOctahedron();
            }
            break;
            //四面体，默认半径1.0
        case TETRAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z轴均放大6倍
            if(bWire){
                glutWireTetrahedron();
            }
            else{
                glutSolidTetrahedron();
            }
            break;
            //二十面体，默认半径1.0
        case ICOSAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z轴均放大6倍
            if(bWire){
                glutWireIcosahedron();
            }
            else{
                glutSolidIcosahedron();
            }
            break;
        default:
            break;
    }
    
    //恢复压入栈的Matrix
    glPopMatrix();
    //交换两个缓冲区的指针
    glutSwapBuffers();
}
//设置Redering State
void setupRederingState(void){
    //设置清理颜色为黑色
    glClearColor(0.0f,0.0,0.0,1.0f);
    //设置绘画颜色为绿色
    glColor3f(0.0, 1.0, 0.0);
    //使能深度测试
    glEnable(GL_DEPTH_TEST);
    //获取受支持的点大小范围
    glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
    //获取受支持的点大小增量
    glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
    printf("point size range:%f-%f\n",sizes[0],sizes[1]);
    printf("point step:%f\n",step);
}
//窗口大小变化回调函数
void changSize(GLint w,GLint h){
    //横宽比率
    GLfloat ratio;
    //设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
    GLfloat coordinatesize=10.0f;
    //窗口宽高为零直接返回
    if((w==0)||(h==0))
        return;
    //设置视口和窗口大小一致
    glViewport(0,0,w,h);
    //对投影矩阵应用随后的矩阵操作
    glMatrixMode(GL_PROJECTION);
    //重置当前指定的矩阵为单位矩阵
    glLoadIdentity();
    ratio=(GLfloat)w/(GLfloat)h;
    //正交投影
    if(w<h)
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
    else
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
    //对模型视图矩阵堆栈应用随后的矩阵操作
    glMatrixMode(GL_MODELVIEW);
    //重置当前指定的矩阵为单位矩阵
    glLoadIdentity();
}

//按键输入处理回调函数
void specialKey(int key,int x,int y){
    
    if(key==GLUT_KEY_UP){
        xRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_DOWN){
        xRotAngle+=5.0f;
    }
    else if(key==GLUT_KEY_LEFT){
        yRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_RIGHT){
        yRotAngle+=5.0f;
    }
    //重新绘制
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    int nModelMenu;
    int nWireMenu;
    int nMainMenu;
    //初始化glut
    glutInit(&argc,argv);
    //使用双缓冲区、深度缓冲区、模板缓冲区
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //获取系统的宽像素
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //获取系统的高像素
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
    //创建窗口，窗口名字为OpenGL Glut Demo
    glutCreateWindow("OpenGL Glut Demo");
    //设置窗口大小
    glutReshapeWindow(windowWidth,windowHeight);
    //窗口居中显示
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
    //创建二级菜单
    nModelMenu=glutCreateMenu(processMenu);
    glutAddMenuEntry("Sphere",1);
    glutAddMenuEntry("Cone",2);
    glutAddMenuEntry("Cube",3);
    glutAddMenuEntry("Torus",4);
    glutAddMenuEntry("Dodecahedron",5);
    glutAddMenuEntry("Teapot",6);
    glutAddMenuEntry("Octahedron",7);
    glutAddMenuEntry("Tetrahedron",8);
    glutAddMenuEntry("Icosahedron",9);
    nWireMenu=glutCreateMenu(processMenu);
    glutAddMenuEntry("Wire",10);
    glutAddMenuEntry("Solid",11);
    nMainMenu=glutCreateMenu(processMenu);
    glutAddSubMenu("Model",nModelMenu);
    glutAddSubMenu("WireOrSolid",nWireMenu);
    //将菜单榜定到鼠标右键上
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //窗口大小变化时的处理函数
    glutReshapeFunc(changSize);
    //设置显示回调函数
    glutDisplayFunc(renderScreen);
    //设置按键输入处理回调函数
    glutSpecialFunc(specialKey);
    //设置全局渲染参数
    setupRederingState();
    glutMainLoop();
    return 0;
}
