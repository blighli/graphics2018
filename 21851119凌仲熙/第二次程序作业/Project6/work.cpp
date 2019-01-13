#include <windows.h>	
#include <gl/glut.h>				
#include "texture.h"				

#define MAXTEXTURE	4			

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 500;
BOOL isFullScreen = FALSE;

GLfloat	ep_Angle;														
GLfloat	es_Angle;														
GLfloat	mp_Angle;														
GLfloat	ms_Angle;														
GLuint	texture[MAXTEXTURE];											
GLUquadricObj *quadric;													
GLfloat	angle_Z;														

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };					

void InitGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	BuildTexture("Data/1.bmp", texture[0]);
	BuildTexture("Data/3.bmp", texture[2]);
	BuildTexture("Data/4.bmp", texture[3]);
	glEnable(GL_TEXTURE_2D);										

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);						
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);						

	quadric = gluNewQuadric();											
	gluQuadricTexture(quadric, GLU_TRUE);								
	gluQuadricDrawStyle(quadric, GLU_FILL);								
	glEnable(GL_LIGHTING);												
	glEnable(GL_LIGHT1);												

}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);									
	glRotatef(10, 1.0f, 0.0f, 0.0f);									
	glEnable(GL_LIGHT0);												


	glBindTexture(GL_TEXTURE_2D, texture[2]);							
	glEnable(GL_BLEND);													
	glDisable(GL_DEPTH_TEST);											

	glDisable(GL_LIGHTING);											
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);								
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);								
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
	glDisable(GL_BLEND);												
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);											

	glEnable(GL_LIGHTING);												
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);					

	gluSphere(quadric, 0.3f, 32, 32);									

	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);								
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);								

	glDisable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);										

	glTranslatef(-2.5f, 0.0f, 0.0f);										
	glBindTexture(GL_TEXTURE_2D, texture[0]);							

	glPushMatrix();													
	glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);								
	gluSphere(quadric, 0.1f, 32, 32);									
	glPopMatrix();														

	
	glRotatef(mp_Angle, 0.0f, 0.0f, 1.0f);								
	glBindTexture(GL_TEXTURE_2D, texture[3]);							
	glTranslatef(0.2f, 0.0f, 0.0f);										
	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);								
	gluSphere(quadric, 0.02, 32, 32);									

	ep_Angle += 0.5f;
	mp_Angle += 1.5f;
	es_Angle += 1.5f;
	ms_Angle += 1.5f;

	angle_Z += 0.01f;

	glutSwapBuffers();	
}

void Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}


	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);										

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	

	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);					

	glutInitWindowPosition(30, 30);								
	glutCreateWindow("ื๗าต");								

	InitGL();				

	glutDisplayFunc(Display);	

	glutReshapeFunc(Reshape);	

	glutIdleFunc(Display);		

	glutMainLoop();				
}