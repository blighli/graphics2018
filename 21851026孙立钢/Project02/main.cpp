// author sunligang 
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
 
static int year0 = 0 ,year1 = 0,year2=0, year3=0,day = 0;
 
void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //
 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); //
	glEnable( GL_COLOR_MATERIAL );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
 
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
 
	glPushMatrix();
	day = (day + 5) % 360;
	year0 = (year0 + 2) % 360;
	year1 = (year1 + 2) % 360;
	year2 = (year2 + 3)% 360;
	year3 = (year3 + 5)% 360;
	
	glRotatef ((GLfloat) year0, 0.0, 0.0, 1.0);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(1.0, 30, 30); /* draw sun */
 
	
	glPopMatrix();
	glPushMatrix();
	glRotatef ((GLfloat) year1, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 1.5, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	glColor3f(0.0,1.0,0.0);
	glutSolidSphere(0.25, 30, 30); // draw smaller planet 
 
	glPopMatrix();
	glPushMatrix();
	glRotatef ((GLfloat) year2, 0.0, 0.0, 1.0);
	glTranslatef (0.0, -2.8, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	glColor3f(0.0,0.0,1.0);
	glutSolidSphere(0.3, 30, 30); //画一个行星 
	
	glRotatef ((GLfloat) year3, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 0.5, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	glColor3f(0.0,1.0,1.0);
	glutSolidSphere(0.08, 30, 30); //画一个卫星
 
 
 
 
	glutPostRedisplay();
	glPopMatrix();
    glFlush ();
 
	glutSwapBuffers();
	Sleep(50);//延时0.05秒后执行
}
 
 
 
 
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
 
 
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	else
		glOrtho(1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}
 
 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (900, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
 
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
 
	glutMainLoop();
	return 0;
}
