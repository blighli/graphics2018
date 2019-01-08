#include "Bitmap24.h"
#include "Car.h"
#include <iostream>
using namespace std;
Bitmap24 *pBitmap24 (0);
Car *pCar (0);
const GLfloat X = 1690.0f;
const GLfloat Z = 1280.0f;
const GLfloat Y = -31.6f;
void Init()
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0, 0.0, 0.0, 0.0);
	glClearDepth( 1.0 );

	GLfloat Ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Diffuse[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat Position[4] = { 0.0, 0.0, -1.0, 0.0 };
	GLfloat GlobalLight[4] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat shininess[] = {100.0f};

	glLightfv( GL_LIGHT0, GL_AMBIENT, Ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse );
	glLightfv( GL_LIGHT0, GL_POSITION, Position );
	glLightfv( GL_LIGHT0, GL_SHININESS, shininess );

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, GlobalLight );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
}
void redisplay()
{
	pCar->redisplay();
	glutPostRedisplay();
}
void Display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	gluLookAt(pCar->getDisplacementX()+600, 500, pCar->getDisplacementY()-100, 
		pCar->getDisplacementX(), 0, pCar->getDisplacementY(), 
		0, 1.0, 0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,  pBitmap24->getTexture());
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(X, Y, -Z);
    glTexCoord2f(1.0, 0.0); glVertex3f(-X, Y, -Z);
    glTexCoord2f(1.0, 1.0); glVertex3f(-X, Y, Z);
    glTexCoord2f(0.0, 1.0); glVertex3f(X, Y, Z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	pCar->draw();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void Reshape( int width, int high )
{
	if ( high == 0 )high = 1;
	glViewport( 0, 0, static_cast< GLsizei >( width ), static_cast< GLsizei >( high ) );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, static_cast< GLdouble >( width ) / static_cast< GLdouble >( high ), 0.1, 10000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//gluLookAt(0, 1800, -1200, 0, 0, 0, 0, 1.0, 0);
}

void keyboard(const unsigned char key, const int x, const int y)
{
	switch(key)
	{
	case 'W':case 'w':
		pCar->accelerate(0.1f);
		break;
	case 'S':case 's':
		pCar->decelerate(0.1f);
		break;
	case 'D':case 'd':
		pCar->turnRight(30.0f);
		break;
	case 'A':case 'a':
		pCar->turnLeft(30.0f);
		break;
	case ' ':
		pCar->brake();
		break;
	default:
		return;
	}
	glutPostRedisplay();
}
int main( int argc, char* argv[] )
try
{
	pCar = new Car("Car.3DS");
	pBitmap24 = new Bitmap24("paodao1.bmp");
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 800, 600 );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "MySystem" );
	Init();
	glutDisplayFunc( Display );
	glutReshapeFunc( Reshape );
	glutIdleFunc( redisplay );
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	delete pBitmap24;
	delete pCar;
	return 0;
}
catch(const std::runtime_error e)
{
	std::cerr << e.what() << std::endl;
	return 0;
}
catch(...)
{
	std::cerr << "ERROR!" << std::endl;
	return 0;
}