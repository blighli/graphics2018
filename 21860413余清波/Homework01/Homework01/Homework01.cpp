#include "stdafx.h"
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f

GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;

GLint windowWidth = 400;
GLint windowHeight = 300;

GLfloat xRotAngle = 0.0f;

GLfloat yRotAngle = 0.0f;

GLfloat sizes[2];

GLfloat step;

GLint iMaxProjectionStackDepth;

GLint iMaxModeviewStackDepth;

GLint iMaxTextureStackDepth;

GLint iCoordinateaxis = 2;
GLint iProjectionMode = 1;
void changSize(GLint w, GLint h);

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
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case 4:
		iProjectionMode = 2;
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void renderScreen(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	glFrontFace(GL_CW);
	glBegin(GL_QUADS);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(50.0f, 50.0f, 50.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(50.0f, 0.0f, 50.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(0.0f, 0.0f, 50.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(0.0f, 50.0f, 50.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glEnd();

	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void setupRederingState(void) {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0, 0.0, 1.0f);

	glColor3f(1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);

	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &iMaxProjectionStackDepth);

	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &iMaxModeviewStackDepth);

	glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &iMaxTextureStackDepth);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
	printf("iMaxProjectionStackDepth=%d\n", iMaxProjectionStackDepth);
	printf("iMaxModeviewStackDepth=%d\n", iMaxModeviewStackDepth);
	printf("iMaxTextureStackDepth=%d\n", iMaxTextureStackDepth);
}

void changSize(GLint w, GLint h) {

	GLfloat ratio;

	GLfloat coordinatesize = 100.0f;

	if ((w == 0) || (h == 0))
		return;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;

	if (1 == iProjectionMode) {
		printf("glOrtho\n");
		if (w < h)
			glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
		else
			glOrtho(-coordinatesize * ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
	}
	else {
		printf("gluPerspective\n");
		gluPerspective(60, ratio, 10.0f, 500.0f);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -200.0f);
	}
}


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

	glutPostRedisplay();
}

void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}

int main(int argc, char* argv[])
{

	GLint iMainMenu;
	GLint iCoordinateaxisMenu;
	GLint iOrthoOrPerspectMenu;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);

	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	glutCreateWindow("OpenGL color cube Demo");

	glutReshapeWindow(windowWidth, windowHeight);

	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);

	glutReshapeFunc(changSize);

	glutDisplayFunc(renderScreen);

	glutSpecialFunc(specialKey);

	iCoordinateaxisMenu = glutCreateMenu(processMenu);

	glutAddMenuEntry("Display coordinate axis", 1);
	glutAddMenuEntry("Don't dispaly coordinate axis", 2);
	iOrthoOrPerspectMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("Ortho", 3);
	glutAddMenuEntry("Perspect", 4);
	iMainMenu = glutCreateMenu(processMenu);
	glutAddSubMenu("Whether Display coordinate axis", iCoordinateaxisMenu);
	glutAddSubMenu("Ortho Or Perspect", iOrthoOrPerspectMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(10, timerFunc, 1);

	setupRederingState();
	glutMainLoop();

	return 0;
}