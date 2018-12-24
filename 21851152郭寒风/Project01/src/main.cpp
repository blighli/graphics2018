#include <gl/freeglut.h>
#include <cstdio>

int mouseX, mouseY;
double cameraAngleX, cameraAngleY;
bool mouseLeftDown;
float scale = .5f;

void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(cameraAngleX * .1, 1, 0, 0);
    glRotatef(cameraAngleY * .1, 0, 1, 0);
    glutWireTeacup(scale);
    glFlush();
}

void onReshape(int w, int h)
{
    glViewport(0, -(w - h) / 2, w, w);
}

void onMousePress(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if (button == GLUT_LEFT_BUTTON)
    {
        mouseLeftDown = state == GLUT_DOWN;
    }
}

void onMouseWheel(int button, int dir, int x, int y)
{
    scale += ((dir > 0) ? 1.0f : -1.0f) * .03f;

    glutPostRedisplay();
}

void onMouseMotion(int x, int y)
{
    if (mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glEnable(GL_DEPTH_TEST);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Hello OpenGL");

    glutDisplayFunc(&onDisplay);

    glutReshapeFunc(&onReshape);
    glutMouseFunc(&onMousePress);
    glutMotionFunc(&onMouseMotion);
    glutMouseWheelFunc(&onMouseWheel);

    glutMainLoop();
    return 0;
}
