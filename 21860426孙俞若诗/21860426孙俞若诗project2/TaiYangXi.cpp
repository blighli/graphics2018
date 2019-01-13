#include<iostream>
#include<fstream>
#include<GL/glew.h>//使用glew库使用VBO
#include <GL/glut.h>
#include<cmath>
#include<ctime>
#include<vector>
#include<string>
#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL+bytes)
#define T 100
#pragma comment(lib, "glew32.lib")//加个glew使用VBO，啧
using namespace std;
GLfloat l_position[4] = { 0,0,0,1 };
GLfloat r_x1, r_y1, r_x2, r_y2;//鼠标拖动参数
GLint tag = 2;//初始表示画多边形
GLfloat mov_x1, mov_y1, mov_x2, mov_y2;//平移变量
GLfloat trans_x, trans_y;
GLfloat a, b, c, d, e, f;
GLint flag;//0表示鼠标左键按下，1表示中键按下
GLfloat sun[] = { 1,0.2,0.2,1 };
GLfloat sun_light[] = { 1,0.8,0.8,1 };
GLfloat re_set[] = { 0,0,0.0,0 };
GLfloat earth[] = { 0,0.6,1,1 };
GLfloat earth_[] = { 0,0,0.1,0 };
GLfloat color_index[] = { 1,1,1 };
GLfloat moon[] = { 0.8,0.8,0.8,1 };
GLfloat light_1[] = { 0.2,0.2,0.2,1 };
void init(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_1);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glMatrixMode(GL_PROJECTION);//设置投影矩阵
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100000);
	glClearColor(0, 0, 0, 1);
	a = 500;
	b = 20.0;
	c = 50.0;
	d = e = f = 0;
	trans_x = trans_y = 0;
	r_x1 = r_y1 = r_x2 = r_y2 = 0;
	mov_x1 = mov_y1 = mov_x2 = mov_y2 = 0;
}
void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_POSITION, l_position);
	gluLookAt(b, c, a,
		0, 0, 0,
		0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);
	glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, color_index);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun);
	glutSolidSphere(50, 100, 100);
	glMaterialfv(GL_FRONT, GL_EMISSION, re_set);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth);
	glRotatef(clock() / 10, 0, 0, 1);
	glTranslated(300, 0, 0);
	glutSolidSphere(30, 100, 100);
	glRotated(clock() / 10, 0, 0, 1);
	glTranslated(-100, 0, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon);
	glutSolidSphere(10, 30, 30);
	glutSwapBuffers();
}
void s_input(int key, int x, int y)//方向键改变相机Z
{
	if (key == GLUT_KEY_DOWN)
		a += 10;
	if (key == GLUT_KEY_UP)
		a -= 10;
}
void input(unsigned char key, int x, int y)
{
	switch (key)//你还是可以通过键盘控制参数
	{
	case'w':c += 10; break;//相机x,y移动
	case's':c -= 10; break;
	case'a':b -= 10; break;
	case'd':b += 10; break;
	case'h':d -= 5; break;//三个旋转度设置
	case'k':d += 5; break;
	case'u':e -= 5; break;
	case'j':e += 5; break;
	case'i':f += 5; break;
	case'y':f -= 5; break;
	default:
		break;
	}
 
}
void start(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)//记录旋转拖动起始点
	{
		flag = 0;
		r_x1 = r_x2 = x;
		r_y1 = r_y2 = y;
 
	}
	if (state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON)//记录旋转拖动起始点
	{
		flag = 1;
		mov_x1 = mov_x2 = x;
		mov_y1 = mov_y2 = y;
 
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)//记录旋转拖动最终点并将旋转量储存进d,e
	{
		d += (r_x2 - r_x1) / 3;
		e -= (r_y2 - r_y1) / 3;
		r_x1 = r_x2 = r_y1 = r_y2 = 0;
	}
	if (state == GLUT_UP && button == GLUT_MIDDLE_BUTTON)//记录平移最终点，并将平移量存入trans_x,trans_y
	{
		trans_x += mov_x2 - mov_x1;
		trans_y += mov_y1 - mov_y2;
		mov_x1 = mov_y1 = mov_x2 = mov_y2 = 0;
	}
}
void end(int x, int y)
{
	if (!flag)
	{
		r_x2 = x;
		r_y2 = y;
	}
	if (flag == 1)
	{
		mov_x2 = x;
		mov_y2 = y;
	}
}
void menu(int value)
{
	tag = value;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	GLenum err = glewInit();//初始化glew
	if (GLEW_OK != err)
	{
		exit(0);
	}
	init();
	glutDisplayFunc(display);
	glutTimerFunc(10, timerFunc, 1);
	glutSpecialFunc(s_input);
	glutKeyboardFunc(input);
	glutMouseFunc(start);
	glutMotionFunc(end);
	glutMainLoop();
	return 0;
}
