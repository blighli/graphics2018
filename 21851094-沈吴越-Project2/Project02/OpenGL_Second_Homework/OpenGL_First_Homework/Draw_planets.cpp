#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

#pragma region
typedef struct {
	int width;
	int height;
	unsigned int texture_ID;
	unsigned char *data;
}texture;

const double PI = 3.1415926;
static int windowWidth = 800, windowHeight = 400;
static int windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
static int windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
static float year = 0.0, month = 0.0, day = 0.0, rotate_speed = 10;
static bool mouseleftdown = false, mouserightdown = false, mousemiddledown = false;
static float mouse_x, mouse_y, camera_distance_x, camera_distance_y, camera_angle_x, camera_angle_y;
static bool first = false;
texture *sun, *earth, *moon;


void mouse(int x, int y)
{
	if (mouseleftdown) {
		rotate_speed += (mouse_y - y)*0.05;
		mouse_y = y;
	}
	glutPostRedisplay();
}

void mouse_click(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouseleftdown = true;
		}
		else {
			mouseleftdown = false;
		}
	}
}

unsigned char * LoadImage(const char * filename, BITMAPINFOHEADER * bmpInfoHeader)
{
	unsigned char * image;
	unsigned int imageIdx = 0;
	FILE * file;
	BITMAPFILEHEADER bmpFileHeader;

	file = fopen(filename, "rb");
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
	fseek(file, bmpFileHeader.bfOffBits, SEEK_SET);
	image = (unsigned char *)malloc(bmpInfoHeader->biSizeImage);
	fread(image, 1, bmpInfoHeader->biSizeImage, file);

	for (imageIdx = 0; imageIdx < bmpInfoHeader->biSizeImage; imageIdx += 3)
	{
		unsigned char temp;
		temp = image[imageIdx];
		image[imageIdx] = image[imageIdx + 2];
		image[imageIdx + 2] = temp;
	}
	fclose(file);
	return image;
}

texture * LoadTexture(const char * filename)
{
	BITMAPINFOHEADER texInfo;
	texture * current;

	current = (texture *)malloc(sizeof(texture));
	current->data = LoadImage(filename, &texInfo);
	current->height = texInfo.biHeight;
	current->width = texInfo.biWidth;
	glGenTextures(1, &current->texture_ID);
	return current;
}

BOOL Textures()
{
	earth = LoadTexture("earth.bmp");
	glBindTexture(GL_TEXTURE_2D, earth->texture_ID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, earth->width, earth->height, GL_RGB, GL_UNSIGNED_BYTE, earth->data);

	sun = LoadTexture("sun.bmp");
	glBindTexture(GL_TEXTURE_2D, sun->texture_ID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, sun->width, sun->height, GL_RGB, GL_UNSIGNED_BYTE, sun->data);

	moon = LoadTexture("moon.bmp");
	glBindTexture(GL_TEXTURE_2D, moon->texture_ID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, moon->width, moon->height, GL_RGB, GL_UNSIGNED_BYTE, moon->data);

	if (sun == NULL || earth == NULL || moon == NULL) {
		return FALSE;
	}
	return TRUE;
}

void DrawPlanet(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
	GLfloat drho = (GLfloat)(PI) / (GLfloat)iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(PI) / (GLfloat)iSlices;
	GLfloat ds = 1.0f / (GLfloat)iSlices;
	GLfloat dt = 1.0f / (GLfloat)iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;

	for (i = 0; i < iStacks; i++)
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for (j = 0; j <= iSlices; j++)
		{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;

			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();

		t -= dt;
	}
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	Textures();
}

void Idle()
{
	day += rotate_speed;
	glutPostRedisplay();
}

void Display()
{

	GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 2.0f };
	year = day / 365;
	month = day / 30;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mat_ambient1[] = { 1, 0, 0, 1 };
	GLfloat mat_emission[] = { 1, 1, 1, 0 };
	GLfloat mat_ambient2[] = { 0.4, 0.4, 0.8, 1 };
	GLfloat no_emission[] = { 0, 0, 0, 1 };

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, sun->texture_ID);
	glRotatef(month, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glRotatef(90, -1, 0, 0);

	glDisable(GL_LIGHTING);
	DrawPlanet(1.0, 60, 40);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glPopMatrix();

	glPushMatrix();
	glRotatef(year, 0.0, 1.0, 0.0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, earth->texture_ID);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(month, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
	glRotatef(90, -1, 0, 0);
	DrawPlanet(0.4, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, moon->texture_ID);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(60, -1, 1, 0);
	glRotatef(month, 0, 1.0, 0);
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(90, -1, 0, 0);
	DrawPlanet(0.07, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
#pragma endregion



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("OpenGL_Second_Homework-21851094-…ÚŒ‚‘Ω");
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMainLoop();
	return 0;
}