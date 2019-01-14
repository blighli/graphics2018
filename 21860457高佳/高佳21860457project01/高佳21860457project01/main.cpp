/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>

#define PI 3.14
#define  GLUT_WHEEL_UP		3 // 滚轮操作
#define  GLUT_WHEEL_DOWN	4

/* GLUT callback Handlers */
const int win_w = 700, win_h = 700;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

// 鼠标状态变量，用来在鼠标点击事件和拖动事件之间通信
static bool l_button_down = false, r_button_down = false, mid_button_down = false;
static int last_x = -1, last_y = -1;

GLfloat default_matrix[16];
GLfloat modelview_matrix[16];
GLfloat modelview_z_dis;
GLfloat x_min = .0, x_max = 20.0, y_min = .0, y_max = 20.0, z_min = .0, z_max = 20.0;


void xyz_line(float len)
{
	GLfloat color[] = { .0, .0, .0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

	glBegin(GL_LINES);
	color[0] = 1.0; color[1] = .0; color[2] = .0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(len, .0, .0);
	color[0] = .0; color[1] = 1.0; color[2] = .0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, len, .0);
	color[0] = .0; color[1] = .0; color[2] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, .0, len);
	glEnd();
}

//绘制一个球体
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
 float step_z = PI/M;
 float step_xy = 2*PI/N;
 float x[4],y[4],z[4];

 float angle_z = 0.0;
 float angle_xy = 0.0;
 int i=0, j=0;
 glBegin(GL_QUADS);
  for(i=0; i<M; i++)
  {
   angle_z = i * step_z;

   for(j=0; j<N; j++)
   {
    angle_xy = j * step_xy;

    x[0] = radius * sin(angle_z) * cos(angle_xy);
    y[0] = radius * sin(angle_z) * sin(angle_xy);
    z[0] = radius * cos(angle_z);

    x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
    y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
    z[1] = radius * cos(angle_z + step_z);

    x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
    y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
    z[2] = radius*cos(angle_z + step_z);

    x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
    y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
    z[3] = radius * cos(angle_z);

    for(int k=0; k<4; k++)
    {
     glVertex3f(xx+x[k], yy+y[k],zz+z[k]);
    }
   }
  }
 glEnd();
}
/* 显示
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(modelview_matrix);

	drawSphere(15.0,15.0,15.0,10.0,50.0,50.0);
	xyz_line(40.0);

	glutSwapBuffers();
}

/* OpenGL 初始化
 */
void init()
{
	// projection matrix init
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 10.0, 300.0);
	// default_matrix, modelview_matrix, modelview_z_dis init
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100.0 + (x_min + x_max)*.5, 100.0 + (y_min + y_max)*.5, 100.0 + (z_min + z_max)*.5,
		(x_min + x_max)*.5, (y_min + y_max)*.5, (z_min + z_max)*.5, .0, .0, 1.0);
	modelview_z_dis = 100.0f * sqrt(3.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, default_matrix);
	memcpy(modelview_matrix, default_matrix, sizeof(default_matrix));
	glLoadIdentity();

	// color and lighting
	glClearColor(.2f, .2f, .2f, 1.0f);
	glColor4f(.5f, .5f, .5f, 1.0f);
	glShadeModel(GL_SMOOTH);

	GLfloat vec4f[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vec4f);  // 光源散射颜色，纯白
	glLightfv(GL_LIGHT0, GL_SPECULAR, vec4f); // 光源镜面颜色，纯白
	vec4f[0] = .1f; vec4f[1] = .1f; vec4f[2] = .1f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, vec4f);  // 光源环境强度，灰色（0.1 强度白色）
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // 有限远观察点
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);     // 双面光照
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = .0;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vec4f);	// 全局环境光，黑色（无光）

	vec4f[0] = .0; vec4f[1] = modelview_z_dis; vec4f[2] = .0; vec4f[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, vec4f); // 位置式光源，位置在物体斜上方
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = -1.0;
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vec4f); // 光源发光方向

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE); // 使能自动规范化法线向量，保证光照计算的正确性
}

void reshape(int w, int h);
void display();
void mouse_click(int button, int state, int x, int y);
void mouse_move(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialkey(int key, int x, int y);


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Graphics Homework1");


    glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);

    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}


// 窗口大小改变的响应函数
void reshape(int w, int h)
{
	// 窗口大小变化时物体并不缩放，以防止比例失调
	glViewport(0, h - win_w, win_w, win_h);
}

/* 以下三个函数对物体进行平移、旋转、缩放，他们均在视觉(绝对)坐标下进行
 * 正常调用 glTranslate,glRotate,glScale 均是在局部坐标下进行(按正序看)
 * 为了达到在视觉坐标下操作的效果，需要将矩阵左乘到当前矩阵
 */
void absolute_translate(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_rotate(GLfloat dgree, GLfloat vecx, GLfloat vecy, GLfloat vecz)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// 平移回去，注意该句和后两句要倒序来看
	glRotatef(dgree, vecx, vecy, vecz);// 积累旋转量
	glTranslatef(.0, .0, modelview_z_dis);		// 先平移到原点
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_scale(GLfloat factor)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// 平移回去，注意该句和后两句要倒序来看
	glScalef(factor, factor, factor);
	glTranslatef(.0, .0, modelview_z_dis);		// 先平移到原点
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_default()
{
	memcpy(modelview_matrix, default_matrix, sizeof(default_matrix));
}

/* 鼠标点击和移动，左键拖动旋转，中键拖动平移，右键回到最初视图
 */
void mouse_click(int button, int state, int x, int y)
{
	y = win_h - y;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			l_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		}
		else {
			l_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			mid_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CYCLE);

		}
		else {
			mid_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			r_button_down = true;
			absolute_default();
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutPostRedisplay();
		}
		else {
			r_button_down = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_WHEEL_UP:
		if (state == GLUT_UP) {
			absolute_scale(.9f);
			glutPostRedisplay();
		}
		break;
	case GLUT_WHEEL_DOWN:
		if (state == GLUT_UP) {
			absolute_scale(1.1f);
			glutPostRedisplay();
		}
		break;
	}
}
void mouse_move(int x, int y)
{
	y = win_h - y;
	if (last_x >= 0 && last_y >= 0 && (last_x != x || last_y != y)) {
		GLfloat deltax = GLfloat(x - last_x), deltay = GLfloat(y - last_y);
		if (mid_button_down) {
			absolute_translate(deltax * .1f, deltay * .1f, .0f);
			glutPostRedisplay();
		}
		else if (l_button_down) {
			GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
			absolute_rotate(dis, -deltay / dis, deltax / dis, .0);
			glutPostRedisplay();
		}
	}
	last_x = x; last_y = y;
}

/* 键盘按键
 */
void keyboard(unsigned char key, int x, int y)
{
	;
}

/* 键盘特殊键，上下键进行上下旋转，左右键进行左右旋转
 */
void specialkey(int key, int x, int y)
{
	GLfloat deltax = .0, deltay = .0;
	switch (key) {
	case GLUT_KEY_UP:
		deltay += 1.0;
		break;
	case GLUT_KEY_DOWN:
		deltay -= 1.0;
		break;
	case GLUT_KEY_LEFT:
		deltax -= 1.0;
		break;
	case GLUT_KEY_RIGHT:
		deltax += 1.0;
		break;
	}
	if (abs(deltax) > .0 || abs(deltay) > .0) {
		GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
		absolute_rotate(dis, -deltay / dis, deltax / dis, .0);
		glutPostRedisplay();
	}
}
