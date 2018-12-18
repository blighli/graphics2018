#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<GL/glut.h>

#include<iostream>
#include<conio.h>
#include <stdarg.h>
#include <math.h>

const int win_w=700, win_h=700;
GLfloat default_matrix[16];
GLfloat modelview_matrix[16];
GLfloat modelview_z_dis;
GLfloat x_min=.0, x_max=20.0, y_min=.0, y_max=20.0, z_min=.0, z_max=20.0;

void xyz_line(float len)
{
	GLfloat color[]={.0, .0, .0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

	glBegin(GL_LINES);
	color[0]=1.0; color[1]=.0; color[2]=.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(len, .0, .0);
	color[0]=.0; color[1]=1.0; color[2]=.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, len, .0);
	color[0]=.0; color[1]=.0; color[2]=1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, .0, len);
	glEnd();
}
void draw()
{
	// ����һ����ɫ����
	GLfloat color[]={.4f, .4f, .4f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(8.0, 5.0, 8.0);
	glutSolidSphere(5.0, 30, 50);
	glPopMatrix();

	// ����һ�澵��
	color[0]=1.0; color[1]=1.0; color[2]=1.0; color[3]=1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
	color[0]=.0f; color[1]=.0f; color[2]=.1f; color[3]=1.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(.0, 20.0, .0);
	glBegin(GL_POLYGON);
	glNormal3f(.0, -1.0, .0);
	glVertex3f(.0, .0, .0);
	glVertex3f(20.0, .0, .0);
	glVertex3f(20.0, .0, 20.0);
	glVertex3f(.0, .0, 20.0);
	glEnd();
	glPopMatrix();

	// ��������������
	color[0]=.0; color[1]=.0; color[2]=.0; color[3]=1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

	glBegin(GL_TRIANGLES);
	color[0]=.0f; color[1]=.8f; color[2]=.8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glNormal3f(1.0, .0, .0);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, 15.0, .0);
	glVertex3f(.0, .0, 30.0);
	glEnd();

	// ͸������ŵ����в�͸���������ƣ����򲻻��ϣ���������Ȼ���Ϊֻ����������ڵ�֮�����壩
	glDepthMask(GL_FALSE);
	glBegin(GL_TRIANGLES);
	color[0]=1.0; color[1]=1.0; color[2]=.0; color[3]=0.5;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glNormal3f(.0, .0, 1.0);
	glVertex3f(.0, .0, .0);
	glVertex3f(10.0, .0, .0);
	glVertex3f(.0, 20.0, .0);
	glEnd();
	glDepthMask(GL_TRUE);
}

/* ��ʾ
 */
void display_func()
{
	static int z = 0;
	std::cout << "display: " << z++ << std::endl;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(modelview_matrix);

	draw();
	xyz_line(40.0);

	glutSwapBuffers();
}

/* OpenGL ��ʼ��
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
	gluLookAt(100.0+(x_min+x_max)*.5, 100.0+(y_min+y_max)*.5, 100.0+(z_min+z_max)*.5,
				(x_min+x_max)*.5, (y_min+y_max)*.5, (z_min+z_max)*.5, .0, .0, 1.0);
	modelview_z_dis = 100.0f * sqrt(3.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, default_matrix);
	memcpy(modelview_matrix, default_matrix, sizeof(default_matrix));
	glLoadIdentity();

	// color and lighting
	glClearColor(.2f, .2f, .2f, 1.0f);
	glColor4f(.5f, .5f, .5f, 1.0f);
	glShadeModel(GL_SMOOTH);

	GLfloat vec4f[]={1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vec4f);  // ��Դɢ����ɫ������
	glLightfv(GL_LIGHT0, GL_SPECULAR, vec4f); // ��Դ������ɫ������
	vec4f[0] = .1f; vec4f[1] = .1f; vec4f[2] = .1f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, vec4f);  // ��Դ����ǿ�ȣ���ɫ��0.1 ǿ�Ȱ�ɫ��
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // ����Զ�۲��
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);     // ˫�����
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = .0;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vec4f);	// ȫ�ֻ����⣬��ɫ���޹⣩

	vec4f[0] = .0; vec4f[1] = modelview_z_dis; vec4f[2] = .0; vec4f[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, vec4f); // λ��ʽ��Դ��λ��������б�Ϸ�
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = -1.0;
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vec4f); // ��Դ���ⷽ��

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE); // ʹ���Զ��淶��������������֤���ռ������ȷ��
}

void reshape_func(int w, int h);
void display_func();
void mouse_click_func(int button, int state, int x, int y);
void mouse_move_func(int x, int y);
void keyboard_func(unsigned char key, int x, int y);
void specialkey_func(int key, int x, int y);

/**************************************************************************
 *������ڣ�������
 */
int main(int argc, char** argv)
{
	// glut init
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_DEPTH );
	glutInitWindowSize( win_w, win_h );
	glutInitWindowPosition( 300, 0 );
	glutCreateWindow( "glut test" );
	// The callbacks.
	glutReshapeFunc( reshape_func );
	glutDisplayFunc( display_func );
 	glutMouseFunc( mouse_click_func );
 	glutMotionFunc( mouse_move_func );
	glutKeyboardFunc( keyboard_func );
	glutSpecialFunc( specialkey_func );


	init();
	glutMainLoop();
	return 0;
}

// ���ڴ�С�ı����Ӧ����
void reshape_func(int w, int h)
{
	// ���ڴ�С�仯ʱ���岢�����ţ��Է�ֹ����ʧ��
	glViewport(0, h-win_w, win_w, win_h);
}

/* ���������������������ƽ�ơ���ת�����ţ����Ǿ����Ӿ�(����)�����½���
 * �������� glTranslate,glRotate,glScale �����ھֲ������½���(������)
 * Ϊ�˴ﵽ���Ӿ������²�����Ч������Ҫ��������˵���ǰ����
 */
void absolute_translate(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(modelview_matrix); // ʹ�任������˵���ǰ�����������ʺϾ�������Ŀ���
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_rotate(GLfloat dgree, GLfloat vecx, GLfloat vecy, GLfloat vecz)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// ƽ�ƻ�ȥ��ע��þ�ͺ�����Ҫ��������
	glRotatef(dgree, vecx, vecy, vecz);// ������ת��
	glTranslatef(.0, .0, modelview_z_dis);		// ��ƽ�Ƶ�ԭ��
	glMultMatrixf(modelview_matrix); // ʹ�任������˵���ǰ�����������ʺϾ�������Ŀ���
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_scale(GLfloat factor)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// ƽ�ƻ�ȥ��ע��þ�ͺ�����Ҫ��������
	glScalef(factor, factor, factor);
	glTranslatef(.0, .0, modelview_z_dis);		// ��ƽ�Ƶ�ԭ��
	glMultMatrixf(modelview_matrix); // ʹ�任������˵���ǰ�����������ʺϾ�������Ŀ���
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_default()
{
	memcpy(modelview_matrix, default_matrix, sizeof(default_matrix));
}

// ���״̬������������������¼����϶��¼�֮��ͨ��
static bool l_button_down=false, r_button_down=false, mid_button_down=false;
static int last_x=-1, last_y=-1;
#define  GLUT_WHEEL_UP		3 // ���ֲ���
#define  GLUT_WHEEL_DOWN	4
/* ��������ƶ�������϶���ת���м��϶�ƽ�ƣ��Ҽ��ص������ͼ
 */
void mouse_click_func(int button, int state, int x, int y)
{
	y = win_h - y;
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN) {
			l_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		} else {
			l_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if(state == GLUT_DOWN) {
			mid_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CYCLE);

		} else {
			mid_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN) {
			r_button_down = true;
			absolute_default();
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutPostRedisplay();
		} else {
			r_button_down = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_WHEEL_UP:
		if(state == GLUT_UP){
			absolute_scale(.9f);
			glutPostRedisplay();
		}
		break;
	case GLUT_WHEEL_DOWN:
		if(state == GLUT_UP) {
			absolute_scale(1.1f);
			glutPostRedisplay();
		}
		break;
	}
}
void mouse_move_func(int x, int y)
{
	y = win_h - y;
	if( last_x>=0 && last_y>=0 && (last_x!=x||last_y!=y) ) {
		GLfloat deltax = GLfloat(x - last_x), deltay = GLfloat(y - last_y);
		if(mid_button_down) {
			absolute_translate(deltax * .1f, deltay * .1f, .0f);
			glutPostRedisplay();
		}
		else if(l_button_down) {
			GLfloat dis = sqrt(deltax*deltax+deltay*deltay);
			absolute_rotate(dis, -deltay/dis, deltax/dis, .0);
			glutPostRedisplay();
		}
	}
	last_x = x; last_y = y;
}

/* ���̰���
 */
void keyboard_func(unsigned char key, int x, int y)
{
	;
}

/* ��������������¼�����������ת�����Ҽ�����������ת
 */
void specialkey_func(int key, int x, int y)
{
	GLfloat deltax = .0, deltay = .0;
	switch(key) {
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
	if(abs(deltax) > .0 || abs(deltay) > .0) {
		GLfloat dis = sqrt(deltax*deltax+deltay*deltay);
		absolute_rotate(dis, -deltay/dis, deltax/dis, .0);
		glutPostRedisplay();
	}
}
