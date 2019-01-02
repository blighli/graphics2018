#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


using namespace std;
bool bPersp = false;
int year = 0, day = 0,  marsYear = 0;
int speed = 12;
float light_angle = 0;
bool bWire = false;
float light_radius = 8.0;
float eye[] = {5.5, 1.7, 1.7};
float center[] = { 0, 0, 0 };
int wHeight = 0;
int wWidth = 0;
int state = 1;
float star[1000][3];
GLUquadricObj *g_text;
void lPosition()
{
    float y, z;
    y = light_radius * cos(light_angle);
    z = light_radius * sin(light_angle);
    float light_position[] = { 3.0, y, z, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    lPosition();
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    g_text = gluNewQuadric();
}
void init_stars()
{
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 3; j++)
            star[i][j] = rand() % 20 - 10;
}
void stars()
{
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 1000; ++i) {
        glVertex3f(star[i][0], star[i][1], star[i][2]);
    }
    glEnd();
}
void sun()
{
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    gluSphere(g_text, 0.7, 32, 32);
    glPopMatrix();
}
void earth()
{
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef((GLfloat)year / 10, 0.0, 0.0, 1.0);
    glTranslatef(2.1, 0.0, 0.0);
    glRotatef((GLfloat)day / 10, 0.0, 0.0, 1.0);
    gluSphere(g_text, 0.25, 20, 16);

    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef((GLfloat)year / 10, 0.0f, 0.0f, 1.0f);
    glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.3f, 0.0f, 0.0f);
    gluSphere(g_text, 0.06, 20, 16);
    glPopMatrix();
}
void mars()
{
    glPushMatrix();
    glColor3f(166.0 / 256, 119.0 / 356, 67.0 / 256);
    glRotatef((GLfloat)marsYear / 10, 0.0, -1.0, 1.0);
    glTranslatef(3.2, 1.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 0.0, 1.0);
    gluSphere(g_text, 0.23, 20, 16);
    glPopMatrix();
}


void redraw(void)
{
    lPosition();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glColor3f(1.0, 1.0, 1.0);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_2D);
    stars();
    sun();
    earth();
    mars();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void cPosition()
{
    glLoadIdentity();
    cout << "eye[0] : " << eye[0] << " eye[1] : "
         << eye[1] << " eye[2] : " << eye[2] << endl;
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0.0, 0.0, 1.0);

}

void updateView(int width, int height)
{

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (!bPersp) {
        gluPerspective(65.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
    }
    else {
        glOrtho(-3, 3, -3, 3, -100, 100);
    }
    glMatrixMode(GL_MODELVIEW);
    cPosition();
}
void reshape(int width, int height)
{
    wHeight = height;
    wWidth = width;
    updateView(wWidth, wHeight);

}

void move()
{
    year = (year + 8) % 3600;
    marsYear = (marsYear + 6) % 3600;
    day = (day + 30) % 3600;
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'p': {
        bPersp = !bPersp;
        updateView(wWidth, wHeight);
        break;
    }


    case 'o': {bWire = !bWire; break; }


    case 'w': {
        eye[0] += 1;
        center[0] += 1;
        cPosition();
        break;
    }
    case 'a': {
        eye[1] += 1;
        center[1] += 1;
        cPosition();
        break;
    }
    case 's': {
        eye[0] -= 1;
        center[0] -= 1;
        cPosition();
        break;
    }
    case 'd': {
        eye[1] -= 1;
        center[1] -= 1;
        cPosition();
        break;
    }
    case 'z': {
        eye[2] -= 1;
        center[2] -= 1;
        cPosition();
        break;
    }
    case 'c': {
        eye[2] += 1;
        center[2] += 1;
        cPosition();
        break;
    }
    case 'r':
        eye[0] = 5.5;
        eye[1] = 1.7;
        eye[2] = 1.7;
        center[0] = 0;
        center[1] = 0;
        center[2] = 0;
        cPosition();
        break;
    case 'q': {exit(0); break; }
    default:
        break;
    }
}

void myIdle(void)
{
    Sleep(speed);
    move();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    cout << "WASDZC change the Camera Position" << endl;
    cout << " O change GL_LINE GL_FILL" << endl;
    cout << " P change the Perspective orthographic projection" << endl;
    cout << " R reset the Camera" << endl;
    cout << endl
         << endl
         << "By Zhang Sidan : Nov. 2018" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1080, 680);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    init_stars();
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(&myIdle);
    glutMainLoop();
    return 0;
}
