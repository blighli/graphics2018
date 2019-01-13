#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

#include <vector>
#include <cstdio>
#include <cstring>

#include "camera.h"
#include "model.h"

// OpenGL Window attributes
#define WIN_SIZE 1000
#define WIN_POS 100


// Default orientation
// Defined in task 4
#define X_LEFT -1.0
#define X_RIGHT 1.0
#define Y_LEFT -1.0
#define Y_RIGHT 1.0
#define NEAR 1.0
#define FAR 100.0

using namespace std;

// Global vectors of vertex and faces
std::vector< glm::vec3 > v;
std::vector< std::vector< int > > f;


// Decides whether the model should be scaled ( DEBUGGING ONLY )
bool getScale = true;

// ID for the display list which the faces are modelled
GLuint displayListId = 0;

// Fog Mode ( Task 11 )
// Initially it is disabled
bool fogMode = false;

// Enables perspective projection -- Disabled by default
bool perspectiveProjection = false;


// Object representing the camera
Camera cam;

// Object representing the loaded model
Model mdl;


GLfloat backgroundColor[4] = { 1.0, 1.0, 1.0, 0.0 };


// Reads OBJ file and populates the vertex and faces vectors
bool parseFile(const char *path, std::vector< glm::vec3 > &vertices, std::vector< std::vector< int > > &faces) {

	FILE *fp = fopen(path, "r");

	if (fp == NULL)
		return false;


	while (true) {

		// Checks whether it's a face or a vertex
		char header[100];
		int res = fscanf_s(fp, " %s", header);

		if (res == EOF) break;


		if (strcmp(header, "v") == 0) {

			glm::vec3 vertex;
			fscanf_s(fp, " %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(header, "f") == 0) {

			char line[500];
			fgets(line, 500, fp);

			// Faces can have 3 or 4 vertices
			int faceVertexIndices[4];
			int count = sscanf_s(line, " %d %d %d %d", &faceVertexIndices[0], &faceVertexIndices[1], &faceVertexIndices[2], &faceVertexIndices[3]);

			if (count < 3 || count > 4) {
				fprintf(stderr, "Wrong number of indices for face.\n");
				return false;
			}

			std::vector< int > newFace;
			for (int i = 0; i < count; i++) {
				newFace.push_back(--faceVertexIndices[i]);
			}
			faces.push_back(newFace);


		}
		else {
			char discardBuffer[1000];
			fgets(discardBuffer, 1000, fp);
		}

	}

	fclose(fp);

	return true;
}


// Creates a list for object described in the file
// Returns an identifier of this list
GLuint transformObject() {
	GLuint id;

	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	std::vector< std::vector< int > >::iterator itF;
	// Iterates on the list of faces
	for (itF = mdl.faces.begin(); itF != mdl.faces.end(); itF++) {

		if (itF->size() == 4) {
			glBegin(GL_QUADS);
		}
		else {
			glBegin(GL_TRIANGLES);
		}
		std::vector< int >::iterator itV;
		// Iterates on each vertex of this face
		// Scale and center each vertex
		for (itV = itF->begin(); itV != itF->end(); itV++) {
			glVertex3f((mdl.vertices[*itV].x - mdl.center.x) / mdl.scale, (mdl.vertices[*itV].y - mdl.center.y) / mdl.scale, ((mdl.vertices[*itV].z - mdl.center.z) / mdl.scale));
		}

		glEnd();

	}

	glEndList();

	return id;

}


// SETS FOG MODE ON/OFF
void setFog() {

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, backgroundColor);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 5.0f);

	if (fogMode)
		glEnable(GL_FOG);
	else
		glDisable(GL_FOG);


}

// Drawing function
void drawScene(void) {

	//glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	glLoadIdentity();

	gluLookAt(cam.eye.x, cam.eye.y, cam.eye.z, cam.center.x, cam.center.y, cam.center.z, cam.up.x, cam.up.y, cam.up.z);



	// Rotates on the camera
	glRotatef(cam.angle.z, 0.0, 0.0, 1.0);
	glRotatef(cam.angle.y, 0.0, 1.0, 0.0);
	glRotatef(cam.angle.x, 1.0, 0.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	glColor3f(0.0, 0.0, 0.0);


	setFog();


	//  Translate model
	glTranslatef(mdl.pos.x, mdl.pos.y, mdl.pos.z);

	// Rotate model
	glRotatef(mdl.ang.z, 0.0, 0.0, 1.0);
	glRotatef(mdl.ang.y, 0.0, 1.0, 0.0);
	glRotatef(mdl.ang.x, 1.0, 0.0, 0.0);




	glCallList(displayListId); // Draws the 3D mesh


	glutSwapBuffers();

}

// Switch between projections
void setProjection() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (perspectiveProjection) {
		glFrustum(X_LEFT, X_RIGHT, Y_LEFT, Y_RIGHT, NEAR, FAR);
	}
	else {
		glOrtho(X_LEFT, X_RIGHT, Y_LEFT, Y_RIGHT, NEAR, FAR);

	}
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

}

// Initialization procedures
// Called when model and camera are reset
void init() {

	// Sets Background color to white
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);


	// Sets model to the initial position and scales it.
	mdl.reset();
	mdl.setup(v, f);
	mdl.translate(0.0, 0.0, -2.0); // The model should be moved to (0,0,-2), so it can be seen.


	// Resets camera position
	cam.startPosition();

	// Fog mode is initially disabled
	fogMode = false;


	// Codes the faces in a display list	
	displayListId = transformObject();

}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		// MODEL ROTATIONS
	case 'P':
		mdl.rotate(10.0, 0.0, 0.0);
		break;
	case 'p':
		mdl.rotate(-10.0, 0.0, 0.0);
		break;
	case 'Y':
		mdl.rotate(0.0, 10.0, 0.0);
		break;
	case 'y':
		mdl.rotate(0.0, -10.0, 0.0);
		break;
	case 'R':
		mdl.rotate(0.0, 0.0, 10.0);
		break;
	case 'r':
		mdl.rotate(0.0, 0.0, -10.0);
		break;
		// MODEL TRANSLATIONS
	case 'L':
		mdl.translate(0.1, 0.0, 0.0);
		break;
	case 'l':
		mdl.translate(-0.1, 0.0, 0.0);
		break;
	case 'D':
		mdl.translate(0.0, 0.1, 0.0);
		break;
	case 'd':
		mdl.translate(0.0, -0.1, 0.0);
		break;
	case 'N':
		mdl.translate(0.0, 0.0, 0.1);
		break;
	case 'n':
		mdl.translate(0.0, 0.0, -0.1);
		break;
		// MODEL EXPORT
	case 'w':
		mdl.exportScheme(); // Write model to the output ( Task 2 )
		break;
		// FOG EFFECT
	case 'f':
		fogMode = false; // Disable FOG effect
		break;
	case 'F':
		fogMode = true; // Enable FOG effect

		break;
		// EXIT
	case 'q':
		exit(0);
		break;
		// RESET 
	case 's':
		init();
		break;
		// CAMERA TRANSLATIONS
	case 'I':
		cam.translate(0.0, 0.0, 0.1);
		break;
	case 'i':
		cam.translate(0.0, 0.0, -0.1);
		break;
		// Switch between projection types
	case 'V':
		perspectiveProjection = true;
		setProjection();
		break;
	case 'v':
		perspectiveProjection = false;
		setProjection();
		break;
	case 'T':
		cam.rotate(10.0, 0.0, 0.0);
		break;
	case 't':
		cam.rotate(-10.0, 0.0, 0.0);
		break;
	case 'A':
		cam.rotate(0.0, 10.0, 0.0);
		break;
	case 'a':
		cam.rotate(0.0, -10.0, 0.0);
		break;
	case 'C':
		cam.rotate(0.0, 0.0, 10.0);
		break;
	case 'c':
		cam.rotate(10.0, 0.0, -10.0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) cam.translate(0.0, 0.1, 0.0);
	else if (key == GLUT_KEY_DOWN) cam.translate(0.0, -0.1, 0.0);
	else if (key == GLUT_KEY_LEFT) cam.translate(-0.1, 0.0, 0.0);
	else if (key == GLUT_KEY_RIGHT) cam.translate(0.1, 0.0, 0.0);
	glutPostRedisplay();
}



// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	setProjection();

}


int main(int argc, char **argv)
{


	glutInit(&argc, argv);
	glutInitWindowSize(WIN_SIZE, WIN_SIZE);
	glutInitWindowPosition(WIN_POS, WIN_POS);

	// 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Complex3DModel");

	//
	if (!parseFile(argv[1], v, f)) {
		fprintf(stderr, "File could not be parsed\n");
		exit(-1);
	}

	init();

	glutDisplayFunc(drawScene);

	// Register reshape routine.
	glutReshapeFunc(resize);

	glutKeyboardFunc(keyInput);

	// Register the callback function for non-ASCII key entry.
	glutSpecialFunc(specialKeyInput);

	glutMainLoop();

	return 0;

}