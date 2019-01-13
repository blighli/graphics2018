#include<GLUT/GLUT.h>
#include <math.h>
#include <iostream>
#include "TGATexture.hpp"

static int year = 0, day = 0, moon = 0;
GLfloat blueball[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat yallowball[] = {1.0f, 0.0f, 0.0f, 0.3f};
GLfloat grayball[] = {0.15f, 0.15f, 0.15f, 1.0f};
TextureImage texture[3];

bool init(void)
{
    if(!LoadTGA(&texture[0], "/Users/hechentao/openglproject/StudyOpengl/StudyOpengl/moon.tga"))
        return GL_FALSE;
    if(!LoadTGA(&texture[1], "/Users/hechentao/openglproject/StudyOpengl/StudyOpengl/earth.tga"))
        return GL_FALSE;
    if(!LoadTGA(&texture[2], "/Users/hechentao/openglproject/StudyOpengl/StudyOpengl/sun.tga"))
        return GL_FALSE;
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    //材质反光性设置
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 90.0 };
    GLfloat light_position[] = { 0.0, 0.0, -5.0f, 1.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 10.0 };
    GLfloat Light_Model_Ambient[] = { 0.3 , 0.3 , 0.3 , 1.0 };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    //灯光设置
    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient );  //环境光参数
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
    glEnable(GL_TEXTURE_2D);
    
    return GL_TRUE;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture[2].texID);
    
    GLUquadricObj *qobj = gluNewQuadric();
    
    glPushMatrix();
    glRotatef ((GLfloat) 1, 0.0, 0.0, 1.0);
    gluQuadricTexture(qobj, GL_TRUE);
    gluSphere(qobj,1.0, 30, 30); /* draw sun */
    glPopMatrix();

    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[1].texID);

    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    gluQuadricTexture(qobj, GL_TRUE);
    gluSphere(qobj,0.2, 10, 8); /* draw earth */
    glPopMatrix();

    
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[0].texID);
    glTranslatef(2.5f, 0.0, 0.0);
    glRotatef((GLfloat)moon, 0.0, 1.0, 0.0);
    gluQuadricTexture(qobj, GL_TRUE);
    gluSphere(qobj,0.1, 10, 8); /* draw moon */

    glPopMatrix();
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
    gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd':
            day = (day + 10) % 360;
            moon = (moon + 5) % 360;
            glutPostRedisplay();
            break;
        case 'D':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            day = (day + 10) % 360;
            moon = (moon + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        case 'm':
            moon = (moon + 5) % 360;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("太阳系");

    if (init()==GL_FALSE){
        return -1;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
