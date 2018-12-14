#include <windows.h>
#include <glut.h>
#include <math.h>

const double PI = acos(-1.0);
static int windowWidth = 600, windowHeight = 600;
static int windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
static int windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
static int angle = 90;
static int prevX = -1, prevY = -1;
static float r = 1.5f, h = 0.0f;
static float c = PI / 180.0;
static float currSize = 1.0f, zoomStep = 0.03f;

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(r*cos(c*angle), h, r*sin(c*angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(currSize, currSize, currSize);
	glutWireTeapot(0.5f);
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN) {
		prevX = x, prevY = y;
	}
	else if (state == GLUT_UP && button == GLUT_WHEEL_UP) {
		currSize += zoomStep;
	}
	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) {
		currSize -= zoomStep;
	}
}

void onMouseMove(int x, int y) {
	angle += x - prevX;
	h += 0.03 * (y - prevY);
	if (h > 1.0) h = 1.0;
	else if (h < -1.0) h = -1.0;
	prevX = x, prevY = y;
}

void init() {
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (float)w / h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("OpenGL ²èºø");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutMainLoop();
	return 0;
}