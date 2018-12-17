#include<GLUT/GLUT.h>
#include <math.h>
#include <iostream>

bool mouseLeftDown;
bool mouseRightDown;
GLfloat anglex = 0.0;
GLfloat angley = 0.0;
GLfloat anglez = 0.0;
GLint WinW = 800;
GLint WinH = 800;
GLfloat oldx;
GLfloat oldy;
GLfloat distance;

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(anglex, 1, 0, 0);
    glRotatef(angley, 0, 1, 0);
    glRotatef(anglez, 0, 0, 1);
    glTranslatef(0, 0, distance);


    glutWireTeapot(2);
    
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            oldx = x;
            oldy = y;
        }
        
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            anglex = 0.0f;
            angley = 0.0f;
            anglez = 0.0f;
            distance = 0.0f;
            glutPostRedisplay();
        }
    }
}

void keyboard( unsigned char key, int x, int y ){
    if (key == '+' || key == '=')
    {
        distance += 0.1f;
        std::cout<<"+"<<std::endl;
        glutPostRedisplay();
    }
    
    else if (key == '-' || key == '_')
    {
        distance -= 0.1f;
        std::cout<<"-"<<std::endl;
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    GLint deltax = oldx - x;
    GLint deltay = oldy - y;
    anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;
    angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
    anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
    oldx = x;
    oldy = y;
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("opengl1");
    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(&reshape);
    glutMouseFunc(&mouse);
    glutMotionFunc(&motion);
    glutKeyboardFunc(&keyboard);
    glutMainLoop();
    return 0;
}
