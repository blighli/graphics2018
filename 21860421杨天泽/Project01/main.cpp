// GlutColorCubeDemo.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "stdlib.h"
#include <tchar.h>
#include <gl/glut.h>
#include <math.h>
//圆周率宏
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//设置程序的窗口大小
GLint windowWidth = 400;
GLint windowHeight = 300;
//绕x轴旋转角度
GLfloat xRotAngle = 0.0f;
//绕y轴旋转角度
GLfloat yRotAngle = 0.0f;
//受支持的点大小范围
GLfloat sizes[2];
//受支持的点大小增量
GLfloat step;
//最大的投影矩阵堆栈深度
GLint iMaxProjectionStackDepth;
//最大的模型视图矩阵堆栈深度
GLint iMaxModeviewStackDepth;
//最大的纹理矩阵堆栈深度
GLint iMaxTextureStackDepth;

GLint iCoordinateaxis = 2;//是否显示坐标轴
GLint iProjectionMode = 1;//投影模式
void changSize(GLint w, GLint h);

//菜单回调函数
void processMenu(int value) {
	switch (value) {
	case 1:
		iCoordinateaxis = 1;
		break;
	case 2:
		iCoordinateaxis = 2;
		break;
	case 3:
		iProjectionMode = 1;
		//强制调用窗口大小变化回调函数，更改投影模式为正交投影
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case 4:
		iProjectionMode = 2;
		//强制调用窗口大小变化回调函数，更改投影模式为透视投影
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	default:
		break;
	}
	//重新绘制
	glutPostRedisplay();
}

//显示回调函数
void renderScreen(void) {
	//将窗口颜色清理为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//把整个窗口清理为当前清理颜色：黑色；清除深度缓冲区。
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//将当前Matrix状态入栈
	glPushMatrix();

	//坐标系绕x轴旋转xRotAngle
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//坐标系绕y轴旋转yRotAngle
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//进行平滑处理　
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
	if(2==iProjectionMode){
		glTranslatef(0.0f,0.0f,-200.0f);
	}*/
	if (1 == iCoordinateaxis) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-90.0f, 00.0f, 0.0f);
		glVertex3f(90.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -90.0f, 0.0f);
		glVertex3f(0.0f, 90.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -90.0f);
		glVertex3f(0.0f, 0.0f, 90.0f);
		glEnd();

		glPushMatrix();
		glTranslatef(90.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 90.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 90.0f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();
	}

	// Draw six quads
	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	// Front Face
	// White
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Yellow
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(50.0f, 0.0f, 50.0f);

	// Red
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Magenta
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Top Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	// Right face
	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glEnd();

	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
	// Bottom Face
	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Left face
	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Back Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glEnd();

	//恢复压入栈的Matrix
	glPopMatrix();
	//交换两个缓冲区的指针
	glutSwapBuffers();
}

//设置Redering State 
void setupRederingState(void) {
	glEnable(GL_DEPTH_TEST);	//使能深度测试
	//glFrontFace(GL_CCW);		//多边形逆时针方向为正面
	glEnable(GL_CULL_FACE);		//不显示背面
	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//背面正面均使用线填充
	glPolygonMode(GL_FRONT, GL_FILL);//背面正面均使用线填充
	glPolygonMode(GL_BACK, GL_LINE);//背面正面均使用线填充
	glShadeModel(GL_SMOOTH);


	//设置清理颜色为黑色
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//设置绘画颜色为绿色
	glColor3f(1.0f, 1.0f, 0.0f);
	//使能深度测试
	glEnable(GL_DEPTH_TEST);
	//获取受支持的点大小范围
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//获取受支持的点大小增量
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	//获取最大的投影矩阵堆栈深度
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &iMaxProjectionStackDepth);
	//获取最大的模型视图矩阵堆栈深度
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &iMaxModeviewStackDepth);
	//获取最大的纹理矩阵堆栈深度
	glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &iMaxTextureStackDepth);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
	printf("iMaxProjectionStackDepth=%d\n", iMaxProjectionStackDepth);
	printf("iMaxModeviewStackDepth=%d\n", iMaxModeviewStackDepth);
	printf("iMaxTextureStackDepth=%d\n", iMaxTextureStackDepth);
}

//窗口大小变化回调函数
void changSize(GLint w, GLint h) {
	//横宽比率
	GLfloat ratio;
	//设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
	GLfloat coordinatesize = 100.0f;
	//窗口宽高为零直接返回
	if ((w == 0) || (h == 0))
		return;
	//设置视口和窗口大小一致
	glViewport(0, 0, w, h);
	//对投影矩阵应用随后的矩阵操作
	glMatrixMode(GL_PROJECTION);
	//重置当前指定的矩阵为单位矩阵　
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
	//正交投影
	if (1 == iProjectionMode) {
		printf("glOrtho\n");
		if (w < h)
			glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
		else
			glOrtho(-coordinatesize * ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
		//当前矩阵设置为模型视图矩阵
		glMatrixMode(GL_MODELVIEW);
		//重置当前指定的矩阵为单位矩阵　
		glLoadIdentity();
	}
	else {
		printf("gluPerspective\n");
		gluPerspective(60, ratio, 10.0f, 500.0f);
		//当前矩阵设置为模型视图矩阵
		glMatrixMode(GL_MODELVIEW);
		//重置当前指定的矩阵为单位矩阵　
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -200.0f);
	}
}

//按键输入处理回调函数
void specialKey(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN) {
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT) {
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		yRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_F11) {
		glScalef(1.1, 1.1, 1.1);
	}
	else if (key == GLUT_KEY_F12) {
		glScalef(0.9, 0.9, 0.9);
	}
	//重新绘制
	glutPostRedisplay();
}

void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}

int main(int argc, char* argv[])
{
	//菜单
	GLint iMainMenu;
	GLint iCoordinateaxisMenu;
	GLint iOrthoOrPerspectMenu;
	//初始化glut 
	glutInit(&argc, argv);
	//使用双缓冲区、深度缓冲区。
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//获取系统的宽像素
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//获取系统的高像素
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//创建窗口，窗口名字为OpenGL LoadMatrix Demo
	glutCreateWindow("OpenGL color cube Demo");
	//设置窗口大小
	glutReshapeWindow(windowWidth, windowHeight);
	//窗口居中显示
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//窗口大小变化时的处理函数
	glutReshapeFunc(changSize);
	//设置显示回调函数 
	glutDisplayFunc(renderScreen);
	//设置按键输入处理回调函数
	glutSpecialFunc(specialKey);
	//菜单回调函数
	iCoordinateaxisMenu = glutCreateMenu(processMenu);
	//添加菜单
	glutAddMenuEntry("Display coordinate axis", 1);
	glutAddMenuEntry("Don't dispaly coordinate axis", 2);
	iOrthoOrPerspectMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("Ortho", 3);
	glutAddMenuEntry("Perspect", 4);
	iMainMenu = glutCreateMenu(processMenu);
	glutAddSubMenu("Whether Display coordinate axis", iCoordinateaxisMenu);
	glutAddSubMenu("Ortho Or Perspect", iOrthoOrPerspectMenu);
	//将菜单榜定到鼠标右键上
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(10, timerFunc, 1);
	//设置全局渲染参数
	setupRederingState();
	glutMainLoop();

	return 0;
}
