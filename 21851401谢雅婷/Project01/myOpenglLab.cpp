#include <stdio.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define  GLUT_WHEEL_UP		3  
#define  GLUT_WHEEL_DOWN	4
const int winWeight = 600, winHeight = 600;
GLfloat defaultMatrix[16];
GLfloat currentMatrix[16];
GLfloat distance_z;
bool mouseLefeDown = false, mouseRightDown = false;
int bufX = 0, bufY = 0;


/*初始化
*/
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);             
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 1.0, 10.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100.0, 100.0, 100.0, .0, 0.0, 0.0, .0, 1.0, 0.0);
	distance_z = 100.0f * sqrt(3.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, defaultMatrix);
	memcpy(currentMatrix, defaultMatrix, sizeof(defaultMatrix));
	glLoadIdentity();
}

/* 显示
*/
void display()
{
	static int z = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(currentMatrix);
	glutWireTeapot(8);
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
	glLoadIdentity();																		// 加载单位矩阵
	glTranslatef(x, y, z);																	// 平移
	glMultMatrixf(currentMatrix); 															// 变换矩阵左乘当前矩阵
	glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
	glPopMatrix();
}
void addRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();																		// 加载单位矩阵
	glTranslatef(.0, .0, -distance_z);														// z轴平移复原
	glRotatef(angle, x, y, z);																// 旋转
	glTranslatef(.0, .0, distance_z);														// z轴平移重做	
	glMultMatrixf(currentMatrix);															// 变换矩阵左乘当前矩阵
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
	/*缩放在当前模型坐标下进行
	*/
	else if (button == GLUT_WHEEL_UP) {
		if (state == GLUT_UP) {
			glScalef(.9f, .9f, .9f);
			glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
			glutPostRedisplay();
		}
	}
	else if (button == GLUT_WHEEL_DOWN) {
		if (state == GLUT_UP) {
			glScalef(1.1f, 1.1f, 1.1f);
			glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
			glutPostRedisplay();
		}
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
	printf("操作提示！\n·旋转物体：按下鼠标【左键】拖拽\n·移动物体：按下鼠标【右键】拖拽\n·缩放物体：滚动鼠标【滚轮】");
}

/*主函数
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);																		//初始化GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);												//指定初始模式
	glutInitWindowSize(winWeight, winHeight);													//初始窗口大小
	glutInitWindowPosition(300, 0);																//初始窗口位置
	glutCreateWindow("myOpenGL_Lab");															//创建窗口，指定窗口名称
	printInstrument();																			//终端显示操作提示
	init();																						//调用初始化函数
	glutReshapeFunc(reshape);																	//指定重绘函数
	glutDisplayFunc(display);																	//指定显示内容函数
	glutMouseFunc(mouse);																		//指定鼠标函数
	glutMotionFunc(motion);																		//指定鼠标动作函数
	glutMainLoop();																				//进入主循环并处理事件
	
	return 0;
}