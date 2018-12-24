#include <gl/glut.h>
#include <Windows.h>
#include <algorithm>
#include <math.h>

static int window_width = 800, window_height = 800;
static int display_pos_x = (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2;
static int display_pos_y = (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2;
static bool mouseleftdown = false, mouserightdown = false, mousemiddledown = false;
static float mouse_x, mouse_y, camera_distance_x, camera_distance_y, camera_angle_x, camera_angle_y, size = 1.0;


void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(80.0, (float)width / height, 1.0, 1000);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	glScalef(size, size, size);
	glTranslatef(camera_distance_x, camera_distance_y, 0);
	glRotatef(camera_angle_x, 1, 0, 0);
	glRotatef(camera_angle_y, 0, 1, 0);
	glutWireTeapot(0.5);
	glutSwapBuffers();
}

void mouse_click(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	size = 1.0;
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouseleftdown = true;
		}
		else {
			mouseleftdown = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouserightdown = true;
		}
		else {
			mouserightdown = false;
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN) {
			mousemiddledown = true;
		}
		else {
			mousemiddledown = false;
		}
	}
}

void mouse(int x, int y)
{
	if (mouseleftdown) {
		camera_angle_y += (x - mouse_x);
		camera_angle_x += (y - mouse_y);
		mouse_x = x;
		mouse_y = y;
	}
	if (mouserightdown) {
		camera_distance_x += (x - mouse_x)*0.002;
		camera_distance_y -= (y - mouse_y)*0.002;
		mouse_x = x;
		mouse_y = y;
	}
	if (mousemiddledown) {
		size += (mouse_y - y)*0.002;
		mouse_y = y;
	}
	glutPostRedisplay();
}


void init()
{
	glEnable(GL_DEPTH_TEST);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(display_pos_x, display_pos_y);
	glutCreateWindow("OpenGL-第一次作业-沈吴越21851094-绘制茶壶");
	init();
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}