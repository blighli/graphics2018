#include <iostream>
using namespace std;

#include <cmath>
#include <ctime>
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

static int cnt=0;

void myTimerFunc(int val);
void drawSun();//太阳
void drawMercury();//水星
void drawVenus();//金星
void drawEarth();//地球
void drawMoon();//月亮
void drawMars();//火星
void drawJupiter();//木星
void drawSaturn();//土星
void drawUranus();//天王星
void drawNeptune();//海王星
void drawOrbit(unsigned int para);//轨道
void myDisplay();

void myTimerFunc(int val){
    cnt++;
    if(cnt>=500)
        cnt=0;
    myDisplay();
    glutTimerFunc(10,myTimerFunc,0);
}

void drawSun(){
    glPushMatrix();
    glColor4f(1.0,0.0,0.0,0.1);//红色
    glRotatef(cnt,0.0,0.0,-1.0);
    glutSolidSphere(18000000,30,30);
    glPopMatrix();
}

void drawMercury(){
    glPushMatrix();
    glColor4f(0.0,1.0,1.0,0.8);//青色
    glRotatef(3.0*cnt,-0.0,0.0,-1.0);
    glTranslatef(40000000.0,0.0,0.0);
    glutSolidSphere(9000000,30,30);
    glPopMatrix();
    drawOrbit(44500000);
}

void drawVenus(){
    glPushMatrix();
    glColor4f(1.00,0.89,0.0,1.0);//金黄
    glRotatef(2.5*cnt,0.0,0.0,-1.0);
    glTranslatef(65000000,0.0,0.0);
    glutSolidSphere(11000000,30,30);
    glPopMatrix();
    drawOrbit(65000000);
}

void drawEarth(){
    glPushMatrix();
    glColor4f(0.0,0.0,1.0,0.8);//蓝色
    glRotatef(2.0*cnt,0.0,0.0,-1.0);
    glTranslatef(90000000,0.0,0.0);
    glutSolidSphere(10000000,30,30);
    glPopMatrix();
    drawOrbit(90000000);
}

void drawMoon(){
    glPushMatrix();
    glColor4f(1.0,1.0,1.0,1.0);//白色
    glRotatef(2.0*cnt,0.0,0.0,-1.0);
    glTranslatef(110000000,0.0,0.0);
    glutSolidSphere(4000000,30,30);
    glPopMatrix();
}

void drawMars(){
    glPushMatrix();
    glColor4f(1.00,0.89,0.4,1.0);
    glRotatef(1.4*cnt,0.0,0.0,-1.0);
    glTranslatef(100000000,0.0,0.0);
    glutSolidSphere(6000000,30,30);
    glPopMatrix();
    drawOrbit(100000000);
}

void drawJupiter(){
    glPushMatrix();
    glColor4f(1.00,0.89,0.4,1.0);
    glRotatef(1.2*cnt,0.0,0.0,-1.0);
    glTranslatef(110000000,0.0,0.0);
    glutSolidSphere(9000000,20,20);
    glPopMatrix();
    drawOrbit(110000000);
}

void drawSaturn(){
    glPushMatrix();
    glColor4f(1.0,1.0,0.0,1.0);//黄色
    glRotatef(1.1*cnt,0.0,0.0,-1.0);
    glTranslatef(120000000,0.0,0.0);
    glutSolidSphere(7000000,20,20);
    glutSolidTorus(1000000,11000000,30,30);
    glPopMatrix();
    drawOrbit(120000000);
    
}

void drawUranus(){
    glPushMatrix();
    glColor4f(0.0,0.3,1.0,0.5);
    glRotatef(cnt,0.0,0.0,-1.0);
    glTranslatef(130000000,0.0,0.0);
    glutSolidSphere(8000000,20,20);
    glPopMatrix();
    drawOrbit(130000000);
}

void drawNeptune(){
    glPushMatrix();
    glColor4f(0.0,0.82,1.0,0.5);
    glRotatef(0.7*cnt,0.0,0.0,-1.0);
    glTranslatef(140000000,0.0,0.0);
    glutSolidSphere(8000000,20,20);
    glPopMatrix();
    drawOrbit(140000000);
}

void drawOrbit(unsigned int para){
    glPushMatrix();
    glColor4f(1.0,1.0,1.0,0.5);
    glutSolidTorus(100000,para,30,30);
    glPopMatrix();
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//加载单位阵
    gluPerspective(62.0,1.0,1,100000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,-200000000,200000000,0,0,0,0,0,1);
    //调用画星球的函数
    drawSun();
    drawMercury();
    drawVenus();
    drawEarth();
    drawMoon();
    drawMars();
    drawJupiter();
    drawSaturn();
    drawUranus();
    drawNeptune();
    glutSwapBuffers();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("???");
    glutDisplayFunc(&myDisplay);
    glutTimerFunc(10,myTimerFunc,0);
    glutMainLoop();
    return 0;
}
