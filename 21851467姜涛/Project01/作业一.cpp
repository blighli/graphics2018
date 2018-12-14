#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

bool flag1 = false;
bool flag2 = false;
bool flag3 = true;
float time = 0.0f, camX = 0.0f, camY, camZ = 10.0f;
float time1 = 1.0f;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //±³¾°
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); 
	glLoadIdentity();    
	if (flag1 == true || flag2 == true)
	{
		if (flag1 == true)
		{
			float radius = 10.0f;
			camX = sin(time++ / 1000) * radius;
			camZ = cos(time++ / 1000) * radius;

		}
		gluLookAt(camX*time1, 0.0, camZ*time1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else
	{

		gluLookAt(camX*time1, 0.0, camZ*time1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	glPushMatrix();						//´´½¨²èºø
	glTranslatef(2.0, 3.0, -6.0);
	glutWireTeapot(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 4, -3.0);
	glRotatef(1.5, 0, 0, 1);
	glutWireTeapot(2.0);
	glPopMatrix();

	glutWireTeapot(2);
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		flag2 = false;
		flag1 = !flag1;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		flag1 = false;
		flag2 = !flag2;
		if (time1 == 2.0f)
			flag3 = false;
		if (time1 == 0.5f)
			flag3 = true;
		if (flag3 == true)
			time1 += 0.5f;
		else
			time1 -= 0.5f;
	}

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}


