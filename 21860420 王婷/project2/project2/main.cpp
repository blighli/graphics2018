//
//  main.cpp
//  project2
//
//  Created by 宇宙无敌美少女 on 2019/1/2.
//  Copyright © 2019年 OPENGL2. All rights reserved.
//

#define PI 3.1415926

#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>


GLuint sun,earth,moon;

GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID = 0, texture_ID = 0;
    
    // 打开文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if (pFile == 0){
        cout<<file_name<<" open failed"<<endl;
        return 0;
    }
    // 读取宽度、高度、计算大小
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, 54, SEEK_SET);
    
    GLint line_bytes = width * 3;
    while (line_bytes % 4 != 0)
        ++line_bytes;
    total_bytes = line_bytes * height;
    pixels = (GLubyte*)malloc(total_bytes);
    
    fread(pixels, total_bytes, 1, pFile);
    
    // 分配一个新的纹理编号
    glGenTextures(1, &texture_ID);
    
    // 绑定新的纹理，载入纹理并设置纹理参数
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    GLint lastTextureID = last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
    free(pixels);
    cout<<"success";
    return texture_ID;
}

//画球
void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(PI) / (GLfloat)iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(PI) / (GLfloat)iSlices;
    GLfloat ds = 1.0f / (GLfloat)iSlices;
    GLfloat dt = 1.0f / (GLfloat)iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;
    
    for (i = 0; i < iStacks; i++)
    {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));
        
        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for (j = 0; j <= iSlices; j++)
        {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));
            
            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            
            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();
        
        t -= dt;
    }
}

void drawCircle(GLfloat r)
{
    int j = 0;
    glBegin(GL_POINTS);
    for (j = 0; j < 100; j++)
    {
        GLfloat theta = j * 2 * PI / 100;
        glVertex3f(r*cos(theta), 0.0f, r*sin(theta));
    }
    glEnd();
}

void Initial()
{
    //light0
    /*
     GLfloat light0_diffuse[] = { 1.0f,0.5f,0.0f,1.0f };
     GLfloat light0_position[] = { 10.0f,20.0f,-150.0f,1.0f };
     GLfloat light0_direction[] = { 0.0f,0.0f,-1.0f };
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
     glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
     */
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glFrontFace(GL_CCW);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    
}

void ChangeSize(int w, int h)
{
    if (h == 0)h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, (float)w / (float)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display(void)
{
    
    static float angle1 = 0.0f, angle2 = 0.0f;//angle1地球绕太阳旋转的角度，angle2月亮绕地球旋转的角度
    
    //漫反射光照
    GLfloat sun_emission[] = { 0.6f,0.0f,0.0f,1.0f };
    GLfloat earth_emission[] = { 0.4f,0.4f,0.8f,50.0f };
    GLfloat moon_emission[] = { 0.98f,0.625f,0.12f,1.0f };
    
    //环境光照
    GLfloat sun_ambient[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat earth_moon_ambient[] = { .0f, .0f, .0f, 1.0f };
    
    //光源light1
    //漫反射光分量
    GLfloat light1_diffuse[] = { 30.5f,30.8f,30.0f,1.0f };
    //坐标位置
    GLfloat light1_position[] = { 50.0f,100.0f,100.0f,1.0f };
    //聚光灯方向角
    GLfloat light1_direction[] = { 0.0f,0.0f,-1.0f };
    
    //清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //指定当前操作模型视图矩阵堆栈
    glMatrixMode(GL_MODELVIEW);
    //重置模型视图矩阵
    glLoadIdentity();
    
    //--------------
    //太阳
    glTranslatef(0.0f, 0.0f, -150.0f);
    glRotatef(angle1, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, sun);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
    gltDrawSphere(12.0f, 30, 30);
    glDisable(GL_LIGHT1);
    glPushMatrix();
    
    //--------------
    //地球
    glBindTexture(GL_TEXTURE_2D, earth);
    glRotatef(angle1, 0.0f, 10.0f, 1.0f);
    glTranslatef(40.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_moon_ambient);
    gltDrawSphere(6.0f, 20, 20);
    
    //--------------
    //月亮
    glBindTexture(GL_TEXTURE_2D, moon);
    glRotatef(angle2, 0.0f, 1.0f, 0.0f);
    glTranslatef(15.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, moon_emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_moon_ambient);
    gltDrawSphere(3.0f, 20, 20);
    
    glPopMatrix();
    
    //旋转步长
    angle1 += 4.0f;
    if (angle1 == 360.0f)
        angle1 = 0.0f;
    
    angle2 += 40.0f;
    if (angle2 == 360.0f)
        angle2 = 0.0f;
    
    glutSwapBuffers();
}

void TimerFunc(int x)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
    
}

//因为mac需手动设置相对路径,这里测试一下
void fTest(){
    FILE* pFile = fopen("moon1.bmp", "rb");
    FILE* pFile2 = fopen("./sun2.bmp", "w");
    if (pFile == 0){
        cout<<"test1"<<" open failed"<<endl;
    }
    if (pFile2 == 0){
        cout<<"test2"<<" open failed"<<endl;
    }
}
int main(int argc, char* argv[])
{
    //fTest();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("WangTing-project02");
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(Display);
    
    glutTimerFunc(500, TimerFunc, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);    // 启用纹理
    sun = load_texture("sun1.bmp");  //加载纹理
    earth = load_texture("earth1.bmp");
    moon = load_texture("moon1.bmp");
    
    Initial();
    
    glutMainLoop();
    
    return 0;
    
}
