#define FREEGLUT_STATIC
#include <GLUT/freeglut.h>
#include <GLUT/glut.h>
#include <iostream>
using namespace std;

const int scrW = 600, scrH = 600;//定义窗口大小
GLfloat initialMatrix[16];//保存最初的模型视图状态
GLfloat currentMatrix[16];//存储当前的模型视图状态
GLfloat modelDistance;//旋转时要用到这个变量，至于为什么不知道
static bool left_button_down = false, right_button_down = false, middle_button_down = false;
static int lastX = -1, lastY = -1;//鼠标位置，注意窗口坐标系和opengl坐标系的y轴区别

void init();
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void absolute_translate(GLfloat x, GLfloat y, GLfloat z);
void absolute_rotate(GLfloat degree, GLfloat vecx, GLfloat vecy, GLfloat vecz);
void absolute_scale(GLfloat factor);
void absolute_initialMatrix();

int main(int argc, char** argv) {
	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(scrW, scrH);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("openGL真的好难啊");
	//callback
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);
	init();
	glutMainLoop();//进入GLUT事件处理循环，让所有的与“事件”有关的函数调用无限循环
	return 0;
}
void init() {
	glMatrixMode(GL_PROJECTION);//投影变换
	glLoadIdentity();
	gluPerspective(15.0,1.0, 10.0,300.0);
	glMatrixMode(GL_MODELVIEW);//模型视图变换
	glLoadIdentity();
	gluLookAt(100,100.0,100.0,0.0,0.0,0.0,0.0,1.0,0.0);//相机在(100,100,100),物体在(0,0,0),相机头顶朝上，起始状态
	modelDistance = 100.0f*sqrt(3.0f);//模型到相机的距离，为什么呢？我还是不知道
	glGetFloatv(GL_MODELVIEW_MATRIX, initialMatrix);//将初始化模型视图矩阵存储到initialMatrix中，用于恢复
	memcpy(currentMatrix, initialMatrix, sizeof(initialMatrix));//给当前模型视图矩阵赋值
	glClearColor(1.0, 1.0, 1.0, 1.0);//白色背景
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(currentMatrix);//用参数中的矩阵替代当前矩阵，display无限循环，每次都加载当前矩阵
	glColor3f(1.0, 0.0, 0.0);//红色
	glutWireTeapot(5.0);
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//物体变形就变形吧，随他去了，以后再说
}
//鼠标事件相关
void absolute_translate(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	//glMultMatrixf（T）
	//M是当前矩阵，在这里M就是在单位矩阵基础上平移后的矩阵,可以看成是平移变换矩阵，T是参数中的矩阵，M=MT
	//当前矩阵可以是投影矩阵，也可以是模型视图矩阵，也可以是纹理矩阵，主要看matrix mode，参数中的矩阵也是列主序的
	glMultMatrixf(currentMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);//这边就是相当于把变换后的矩阵赋值给T,就是按照我们正常习惯左乘变换矩阵，因为在display中始终调用glLoadMatrixf(currentMatrix);
	glPopMatrix();
}
void absolute_rotate(GLfloat degree, GLfloat vecx, GLfloat vecy, GLfloat vecz)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0,0.0, -modelDistance);	//这点很重要，不然物体就跑没了，但是不知道到为什么这么做，谁能告诉我为什么啊？？
	glRotatef(degree, vecx, vecy, vecz);//rotate计算一个绕从原点出发，通过(x,y,z)的矢量逆时针旋转angle度的矩阵
	glTranslatef(0.0,0.0, modelDistance);	//为什么呢？？？？
	glMultMatrixf(currentMatrix); 
	glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
	glPopMatrix();
}
void absolute_scale(GLfloat factor)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -modelDistance);//这是为什么呢？
	glScalef(factor, factor, factor);
	glTranslatef(0.0, 0.0, modelDistance);	//我不能理解啊，但是没有这个还不行啊
	glMultMatrixf(currentMatrix); 
	glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
	glPopMatrix();
}
void absolute_initialMatrix()
{
	memcpy(currentMatrix, initialMatrix, sizeof(initialMatrix));//恢复原状
}
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
void mouse(int button, int state, int x, int y) {
	switch (button) {
		//鼠标左键按住进行旋转
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			left_button_down = true;
			lastX = x, lastY = y;
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			cout <<"鼠标左键按下进行旋转"<<endl;
		}		
		else{
			left_button_down = false;
			lastX = -1; lastY = -1;
		}
		break;
		//鼠标右键按下恢复原状
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			right_button_down = true;
			absolute_initialMatrix();
			glutPostRedisplay();
			cout << "鼠标右键按下恢复原始状态" << endl;
		}
		else {
			right_button_down = false;
			lastX = -1; lastY = -1;
		}
		break;
		//鼠标中键按住进行平移
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			middle_button_down = true;
			lastX = x; lastY = y;
			cout << "鼠标中键按下进行平移" << endl;
		}
		else {
			middle_button_down = false;
			lastX = -1; lastY = -1;
		}
		break;
		//鼠标滚轮上下进行缩放
	case GLUT_WHEEL_UP:
		if (state == GLUT_UP) {
			absolute_scale(1.1f);
			glutPostRedisplay();
			cout << "鼠标滚轮向上进行放大" << endl;
		}
		break;
	case GLUT_WHEEL_DOWN:
		if (state == GLUT_UP) {
			absolute_scale(0.9f);
			glutPostRedisplay();
			cout << "鼠标滚轮向下进行缩小" << endl;
		}
		break;
	}
}
void motion(int x, int y) {
	y = scrH - y;//窗口坐标系和opengl坐标系相互转换，窗口坐标系向下为y正轴，opengl向上为y正轴
	if (lastX >= 0 && lastY >= 0 && (lastX != x || lastY != y)) {
		GLfloat deltax = GLfloat(x - lastX), deltay = GLfloat(y - lastY);
		if (middle_button_down) {
			absolute_translate(deltax *0.1f, deltay *0.1f, 0.0f);//平移时要注意敏感度，不然物体就跑没了
			glutPostRedisplay();
		}
		else if (left_button_down) {
			GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
			//x的变换对应的是y轴偏航角，y的变换对应的是x轴俯仰角
			//鼠标从1处变换至2处，横轴纵轴之差构成三角形，旋转轴是垂直的法向量，旋转轴长度看成1时,(-sin,cos,0),sin=deltay / dis,cos= deltax / dis
			//rotate是逆时针旋转，右手法则，至于旋转多少度自己定
			absolute_rotate(dis, -deltay / dis, deltax / dis,0.0);
			glutPostRedisplay();
		}
	}
	lastX = x; lastY = y;
}
