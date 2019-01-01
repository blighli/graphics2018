#include <stdio.h>
#include "gl/glut.h"
#include <stdlib.h>
#include <time.h>

#include "visuals.h"

int main(int argc,char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	glutInitWindowSize(1024,840);
	glutInitWindowPosition(50,50);

	glutCreateWindow("SolarSystem");
	
	srand(time(NULL));

	pinakas();


	Setup();

	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	

	glutMainLoop();
	
	return 0;

}
