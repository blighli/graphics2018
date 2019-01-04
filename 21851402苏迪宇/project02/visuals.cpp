#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>

#include "GL/glut.h"
#include "visuals.h"

model md;
int starMatrix[2000];

float sun = 1;
float transun = 15.0;
static float ty = 0.0;
static float tx = 0.0;
static float tz = 0.0;
static bool animate = false;

const int OtherPlanetCode = 0;
const int RedPlanetCode = 1;
const int GreenPlanetCode = 2;
const int BluePlanetCode = 3;

static float rotatePlanet = 0.0f;
static float rot = 0.0f;

using namespace std;

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, tz);

	glRotatef(tx, 1.0, 0.0, 0.0);
	glRotatef(ty, 0.0, 1.0, 0.0);

	glTranslatef(0.0f, 0.0f, -100.0f);

	glPushMatrix();
	stars(transun);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8f, 0.8f, 0.8f);
	star(transun);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.01f, 0.01f, 0.01f);
	CreatePlanet(RedPlanetCode);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.02f, 0.02f, 0.02f);
	CreatePlanet(GreenPlanetCode);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.007f, 0.007f, 0.007f);
	CreatePlanet(BluePlanetCode);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.014f, 0.014f, 0.014f);
	CreatePlanet(OtherPlanetCode);
	glPopMatrix();

	glutSwapBuffers();
}

void Resize(int w, int h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70.0f, (float)w / (float)h, 1.0f, 10000.0f);
}

void CreatePlanet(int colour)
{
	if (colour == RedPlanetCode)
	{
		glPushMatrix();

		glRotatef(rot, 0.0f, 0.5f, 0.0f);
		glTranslatef(2000, 0, 0);
		glRotatef(rotatePlanet, 0.0f, 0.5f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);

		DisplayModel(md);

		glPopMatrix();
	}
	else if (colour == GreenPlanetCode)
	{
		glPushMatrix();

		glRotatef(-rot, 0.0f, 0.5f, 0.0f);
		glTranslatef(-3000, 0, 0);
		glRotatef(rotatePlanet, 0.0f, 0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);

		DisplayModel(md);

		glPopMatrix();
	}
	else if (colour == BluePlanetCode)
	{
		glPushMatrix();

		glRotatef(rot, 0.5f, 0.0f, 0.0f);
		glTranslatef(0, 5000, 0);
		glRotatef(rotatePlanet, 0.0f, 0.5f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);

		DisplayModel(md);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();

		glRotatef(-rot, 0.5f, 0.0f, 0.0f);
		glTranslatef(0, -6000, 0);
		glRotatef(rotatePlanet, 0.0f, 0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);

		DisplayModel(md);
		glPopMatrix();
	}
}

void Setup()
{
	ReadFile(&md);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat light_position[] = {0.0, 0.0, -70.0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glFrontFace(GL_CCW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Idle()
{
	if (animate)
	{
		rot += 5.5f;
		rotatePlanet += 1.0f;
		float dt = 0.01f;
		float g = 10;
		if (transun < 11)
			sun = -sun;
		else
			sun = sun - g * dt;
		transun = transun + sun * dt;
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'd':
		ty += 4.5f;
		break;
	case 'a':
		ty -= 4.5f;
		break;
	case 'w':
		tx += 4.5f;
		break;
	case 's':
		tx -= 4.5f;
		break;
	case 'g':
		animate = !animate;
		break;
	case 't':
		tz += 5.1f;
		break;
	case 'y':
		tz -= 5.1f;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void ReadFile(model *md)
{
	ifstream obj_file("planet.obj");

	if (obj_file.fail())
		exit(1);

	string stringLine;
	int vertexPositionCounter = 0;
	int facesCounter = 0;
	int normalsCounter = 0;
	while (getline(obj_file, stringLine))
	{
		if (stringLine.substr(0, 2) == "v ")
		{
			istringstream s(stringLine.substr(2));

			s >> md->obj_points[vertexPositionCounter].x;
			s >> md->obj_points[vertexPositionCounter].y;
			s >> md->obj_points[vertexPositionCounter].z;

			vertexPositionCounter++;
		}
		else if (stringLine.substr(0, 3) == "vn ")
		{
			istringstream s(stringLine.substr(3));

			s >> md->obj_normalls[normalsCounter].x;
			s >> md->obj_normalls[normalsCounter].y;
			s >> md->obj_normalls[normalsCounter].z;

			normalsCounter++;
		}
		else if (stringLine.substr(0, 2) == "f ")
		{
			istringstream s(stringLine.substr(2));

			s >> md->obj_faces[facesCounter].vtx[0];

			s.ignore(10, '/');
			s.ignore(10, '/');

			s >> md->obj_faces[facesCounter].vtn[0];

			s.ignore(10, ' ');

			s >> md->obj_faces[facesCounter].vtx[1];

			s.ignore(10, '/');
			s.ignore(10, '/');

			s >> md->obj_faces[facesCounter].vtn[1];

			s.ignore(10, ' ');

			s >> md->obj_faces[facesCounter].vtx[2];

			s.ignore(10, '/');
			s.ignore(10, '/');

			s >> md->obj_faces[facesCounter].vtn[2];

			facesCounter++;
		}
	}
	md->vertices = vertexPositionCounter;
	md->normalls = normalsCounter;
	md->faces = facesCounter;

	obj_file.close();
}

void DisplayModel(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);

		glNormal3f(md.obj_normalls[md.obj_faces[i].vtn[0] - 1].x, md.obj_normalls[md.obj_faces[i].vtn[0] - 1].y, md.obj_normalls[md.obj_faces[i].vtn[0] - 1].z);
		glNormal3f(md.obj_normalls[md.obj_faces[i].vtn[1] - 1].x, md.obj_normalls[md.obj_faces[i].vtn[1] - 1].y, md.obj_normalls[md.obj_faces[i].vtn[1] - 1].z);
		glNormal3f(md.obj_normalls[md.obj_faces[i].vtn[2] - 1].x, md.obj_normalls[md.obj_faces[i].vtn[2] - 1].y, md.obj_normalls[md.obj_faces[i].vtn[2] - 1].z);
	}
	glEnd();
	glPopMatrix();
}

void star(float transun)
{
	glColor3f(0.6f, 0.5f, 0.1f);

	glutSolidSphere(10.0, 30, 24);

	glPushMatrix();

	glColor4f(1, 1, 0, (transun - 11) / 4);

	glutSolidSphere(transun, 30, 15);

	glPopMatrix();
}

void stars(float transun)
{
	int i;
	for (i = 0; i < 2000; i = i + 3)
	{

		glPushMatrix();

		glTranslatef(starMatrix[i], starMatrix[i + 1], starMatrix[i + 2]);
		glTranslatef(0.0f, 0.0f, -100.0f);

		glScalef(0.02, 0.02, 0.02);
		star(transun);
		glPopMatrix();
	}
}

void pinakas()
{
	int i, a;

	for (i = 0; i < 2000; i++)
	{
		a = rand() % 600 - 300;
		starMatrix[i] = a;
	}
}
