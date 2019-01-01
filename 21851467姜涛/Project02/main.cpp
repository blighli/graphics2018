#include "pch.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "image.h"

using namespace std;

GLfloat rot0 = 30.0;
GLfloat rot1 = 0.0;
GLfloat rot2 = 0.0;
GLfloat rot3 = 0.0;
GLfloat rot4 = 0.0;
GLfloat rot5 = 0.0;
GLfloat rot6 = 0.0;
GLfloat rot7 = 0.0;
GLfloat rot8 = 0.0;


//卫星
GLfloat rot9 = 0.0;
GLfloat rot10 = 0.0;
GLfloat rot11 = 0.0;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}
GLuint sunTexture, merTexture, venTexture, earTexture, marTexture, jupTexture, satTexture, uraTexture, nepTexture, pluTexture, staTexture, logTexture;
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClearDepth(1.0);
	glShadeModel(GL_FLOAT);
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	GLfloat qaAmbientLight[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat qaSpecularLight[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	// Set the light position as center of the sun
	GLfloat qaLightPosition[] = { 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	GLfloat mat_ambient[] = { 0.5,0.5,0.5,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mat_ambient);

	//GLfloat sun_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的环境光颜色，为0
	//GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色，为0
	//GLfloat sun_mat_specular[] = { 1.0f, 1.0f,1.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
	////GLfloat sun_mat_emission[] = { 0.8f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射广颜色，为偏红色
	//GLfloat sun_mat_shininess = 90.0f;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	////glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	
	Image* sun = loadBMP("Bitmaps/sun.bmp");		sunTexture = loadTexture(sun);		delete sun;
	Image* mer = loadBMP("Bitmaps/mercury.bmp");	merTexture = loadTexture(mer);		delete mer;
	Image* ven = loadBMP("Bitmaps/venus.bmp");		venTexture = loadTexture(ven);		delete ven;
	Image* ear = loadBMP("Bitmaps/earth.bmp");		earTexture = loadTexture(ear);		delete ear;
	Image* mar = loadBMP("Bitmaps/mars.bmp");		marTexture = loadTexture(mar);		delete mar;
	Image* jup = loadBMP("Bitmaps/jupiter.bmp");	jupTexture = loadTexture(jup);		delete jup;
	Image* sat = loadBMP("Bitmaps/saturn.bmp");		satTexture = loadTexture(sat);		delete sat;
	Image* ura = loadBMP("Bitmaps/uranus.bmp");		uraTexture = loadTexture(ura);		delete ura;
	Image* nep = loadBMP("Bitmaps/neptune.bmp");	nepTexture = loadTexture(nep);		delete nep;
	

}
GLUquadric *quadric=gluNewQuadric();
void drawSun() {  //绘制太阳
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, 5.0, 20.0, 20.0);
	//glutSolidSphere(5.0, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawMercury() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, merTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(90, 1.0, 0.0, 0.0); //绘制辅助轨道
	glutSolidTorus(0.02, 7, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot1, 0.0, 1.0, 0.0);//设置水星公转速度
	glTranslatef(7, 0.0, 0.0); //设置水星公转半径
	glRotatef(rot0, 0.0, 1.0, 0.0);//设置水星自转
	gluSphere(quadric, 1.0, 20.0, 20.0);
	//glutSolidSphere(1.0, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawVenus() {      //绘制金星
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, venTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 11.0, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot2, 0.0, 3.0, 0.0);//设置金星公转速度
	glTranslatef(11.0, 0.0, 0.0);//设置金星公转半径
	glRotatef(rot0, 0.0, 1.0, 0.0);//设置金星自转
	gluSphere(quadric, 1.5, 20.0, 20.0);
	//glutSolidSphere(1.5, 20, 20);//绘制金星
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawEarth_Moon() { //绘制地球以及月亮
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 16.0, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot3, 0.0, 1.0, 0.0);//设置地球公转速度
	glTranslatef(16.0, 0.0, 0.0);//设置地球半径
	glRotatef(rot0, 0.0, 1.0, 0.0);//设置地球自转速度
	gluSphere(quadric, 2.0, 20.0, 20.0);
	//glutSolidSphere(2.0, 32, 32);

	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot9, 0.0, 1.0, 0.0);//设置月亮公转速度
	glTranslatef(3, 0.0, 0.0);//设置月亮公转半径
	glutSolidSphere(0.4, 10, 8);//绘制月亮
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawMars() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, marTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 21.0, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
    glRotatef(rot4, 0.0, 4.0, 0.0);//设置火星公转速度
	glTranslatef(21.0, 0.0, 0.0);//设置火星公转半径
	glRotatef(rot0, 0.0, 2.0, 0.0);//设置火星自转
	gluSphere(quadric, 1.2, 20.0, 20.0);
	//glutSolidSphere(1.2, 32, 32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawJupiter() { //绘制木星
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 28.0, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);//设置木星公转速度
	glRotatef(rot5, 0.0, 0.4, 0.0);
	glTranslatef(28.0, 0.0, 0.0);//设置木星公转半径
	glRotatef(rot0, 0.0, 0.3, 0.0);//设置木星自转
	gluSphere(quadric, 3.5, 20.0, 20.0);
	//lutSolidSphere(3.5, 20, 20);//绘制木星

	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot10, 0.0, 1.0, 0.0);//设置木卫1公转速度
	glTranslatef(4.0, 0.0, 0.0);//设置木卫1公转半径
	glutSolidSphere(0.3, 10, 8);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawSaturn() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, satTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 37.0, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot6, 0.0, 0.4, 0.0);//设置土星公转速度
	glTranslatef(37.0, 0.0, 0.0);//设置土星公转半径
	glRotatef(rot0, 0.0, 0.3, 0.0);//设置土星自转
	gluSphere(quadric, 3.0, 20.0, 20.0);
	//glutSolidSphere(3.0, 32, 32);
	//绘制土星光环
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidTorus(0.2, 6.0, 30, 30);
	glutSolidTorus(0.4, 5.0, 30, 30);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawUranus() { //绘制天王星
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, uraTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 45.5, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot7, 0.0, 0.4, 0.0);//设置天王星公转速度
	glTranslatef(45.5, 0.0, 0.0);//设置天王星公转半径
	glRotatef(rot0, 0.0, 0.03, 0.0);//设置天王星自转
	gluSphere(quadric, 2.5, 20.0, 20.0);
	//glutSolidSphere(2.5, 32, 32);//绘制天王星
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawNeptune() { //绘制海王星
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, nepTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(90, 1.0, 0.0, 0.0);//绘制辅助轨道
	glutSolidTorus(0.02, 53.6, 100, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(rot8, 0.0, 0.4, 0.0);//设置海王星公转速度
	glTranslatef(53.6, 0.0, 0.0);//设置海王星公转半径
	glRotatef(rot0, 0.0, 0.3, 0.0);//设置海王星自转
	gluSphere(quadric, 2.3, 20.0, 20.0);
	//glutSolidSphere(2.3, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -60.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	drawSun();
	drawMercury();
	drawVenus();
	drawEarth_Moon();
	drawMars();
	drawJupiter();
	drawSaturn();
	drawUranus();
	drawNeptune();
	glutSwapBuffers();
	glFlush();

}


void idle()
{


	rot0 += 0.5;
	if (rot0 >= 360.0)
		rot0 -= 360.0;

	rot1 += 0.274;
	if (rot1 >= 360.0)
		rot1 -= 360.0;


	rot2 += 0.150;
	if (rot2 >= 360.0)
		rot2 -= 360.0;


	rot3 += 0.159;
	if (rot3 >= 360.0)
		rot3 -= 360.0;


	rot4 += 0.12;
	if (rot4 >= 360.0)
		rot4 -= 360.0;


	rot5 += 0.06;
	if (rot5 >= 360.0)
		rot5 -= 360.0;


	rot6 += 0.05;
	if (rot6 >= 360.0)
		rot6 -= 360.0;


	rot7 += 0.04;
	if (rot7 >= 360.0)
		rot7 -= 360.0;


	rot8 += 0.054;
	if (rot8 >= 360.0)
		rot8 -= 360.0;


	rot9 += 0.025;
	if (rot9 >= 360.0)
		rot9 -= 360.0;


	rot10 += 0.03;
	if (rot10 >= 360.0)
		rot10 -= 360.0;

	glutPostRedisplay();
}



void reshape(GLsizei w, GLsizei h)
{


	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLdouble)w / (GLdouble)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);


}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("太阳系");
	init();


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();


	return 0;
}

//#define GL_PI 3.1415f  
//
//
//static GLfloat xRot = 0.0f;
//static GLfloat yRot = 0.0f;
//
//
//GLfloat  whiteLight[] = { 1.0f,1.f,1.0f,1.0f };
//GLfloat  envi_light[] = { 0.2f,0.2f,0.2f,1.0f };
//GLfloat  lightPos[] = { 0.0f,0.0f,0.0f,1.0f };
//
//void RenderScene(void)
//{
//	static float fMoonRot = 0.0f;
//	static float fEarthRot = 0.0f;
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -300.0f);
//
//	//绘制太阳
//	glColor3ub(255, 255, 0);
//	glutSolidSphere(20.0f, 20.0f, 20.0f);
//
//
//	//绘制地球  
//	glColor3ub(0, 0, 255);
//	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
//	glTranslatef(105.0f, 0.0f, 0.0f);
//	glutSolidSphere(15.0f, 15.0f, 15.0f);      //颜色，移动，旋转速度都是要在画之前决定的  
//
//
//	//根据基于地球的坐标进行旋转，并绘制月球  
//	glColor3ub(200, 200, 200);
//	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
//	glTranslatef(30.0f, 0.0f, 0.0f);
//	fMoonRot += 15.0f;
//	if (fMoonRot >= 365.0f)
//		fMoonRot = 0.0f;
//	glutSolidSphere(6.0f, 15.0f, 15.0f);  //旋转角度确定好后才画的月球。
//	glPopMatrix();
//	fEarthRot += 5.0f;
//	if (fEarthRot >= 365.0f)
//		fEarthRot = 0.0f;
//	glutSwapBuffers();
//}
//void ChangeSize(GLsizei w, GLsizei h)
//{
//	GLfloat fAspect;
//	if (h == 0) h = 1;
//	glViewport(0, 0, w, h);
//	fAspect = (GLfloat)w / (GLfloat)h;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0f, fAspect, 1.0, 4000);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	//gluLookAt(0, -200, 200, 0, 0, 0, 0, 1, 0);
//}
//
//void SetupRC(void)
//{
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_COLOR_MATERIAL);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glEnable(GL_LIGHTING);                             //启动光源  
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, envi_light); //使用whiteLght所指定的环境光  
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);         //0号光源的位置  
//	glEnable(GL_LIGHT0);
//}
//
//void SpecialKeys(int key, int x, int y)
//{
//	if (key == GLUT_KEY_UP)
//		xRot -= 5.0f;
//	if (key == GLUT_KEY_DOWN)
//		xRot += 5.0f;
//	if (key == GLUT_KEY_LEFT)
//		yRot -= 5.0f;
//	if (key == GLUT_KEY_RIGHT)
//		yRot += 5.0f;
//
//
//	xRot = (GLfloat)((const int)xRot % 360);
//	yRot = (GLfloat)((const int)yRot % 360);
//	glutPostRedisplay();
//}
//void TimerFunc(int value)
//{
//	glutPostRedisplay();
//	glutTimerFunc(100, TimerFunc, 1);
//}
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Orthographic Projection");
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ChangeSize);
//	//glutSpecialFunc(SpecialKeys);//设置上下左右键对图形旋转的控制 
//	SetupRC();
//	glutTimerFunc(250, TimerFunc, 1); //自动动画，计时器  
//	glutMainLoop();
//	return 0;
//}