#include "ObjLoader.hpp"
#include <iostream>
using namespace std;
//模型路径
string filePath = "/Users/hechentao/openglproject/StudyOpengl/StudyOpengl/Resource/teddy.obj";

ObjLoader objModel = ObjLoader(filePath);

static float c = 3.1415926 / 180.0f;
static float r = 1.0f;
static int degreex = 90;
static int degreey = 90;
static int oldPosY = -1;
static int oldPosX = -1;
static float dist = -20.0f;;
GLfloat anglex = 0.0;
GLfloat angley = 0.0;
GLfloat anglez = 0.0;
GLint WinW = 500;
GLint WinH = 500;
int method = 0;

void setLightRes() {
    
    GLfloat light_position[] = { -2.0, 2.0, 1.0f, 0.0 };
    GLfloat light_position2[] = { 2.0, 2.0, 1.0f, 0.0 };
    GLfloat light_position3[] = { -2.0, -2.0, 1.0f, 0.0 };
    GLfloat light_position4[] = { 2.0, -2.0, 1.0f, 0.0 };
    
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat blue_light[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat green_light[] = { 1.0, 1.0, 0.0, 1.0 };
    
    GLfloat Light_Model_Ambient[] = { 0.3 , 0.3 , 0.3 , 1.0 };
    
    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient );  //环境光参数
    
    
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);   //散射光属性
    glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);  //镜面反射光
    
    glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, red_light);   //散射光属性
    glLightfv(GL_LIGHT2, GL_SPECULAR, red_light);  //镜面反射光
    
    glLightfv(GL_LIGHT3, GL_POSITION, light_position4);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, green_light);   //散射光属性
    glLightfv(GL_LIGHT3, GL_SPECULAR, green_light);  //镜面反射光
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    
}


void init() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    
    setLightRes();
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, dist);
    setLightRes();
    glPushMatrix();
    
    if (method == 1){
        gluLookAt(r*cos(c*degreex), r*sin(c*degreey), r*sin(c*degreex), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(anglex, 1, 0, 0);
        glRotatef(angley, 0, 1, 0);
        glRotatef(anglez, 0, 0, 1);
    }
    else if (method == 0){
        gluLookAt(r*cos(c*degreex), r*sin(c*degreey), r*sin(c*degreex), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }
    objModel.Draw();//绘制obj模型
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void moseMove(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            dist = -20.0f;
            glutPostRedisplay();
        }
    }
    if (state == GLUT_DOWN) {
        oldPosX = x;
        oldPosY = y;
    }
}

void keyboard( unsigned char key, int x, int y ){
    if (key == '+' || key == '=')
    {
        dist += 1.0f;
        std::cout<<"+"<<std::endl;
        glutPostRedisplay();
    }
    
    else if (key == '-' || key == '_')
    {
        dist -= 1.0f;
        std::cout<<"-"<<std::endl;
        glutPostRedisplay();
    }
    else if (key == 'c' || key == 'C')
    {
        method = 1^method;
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    if (method == 1){
        GLint deltax = oldPosX - x;
        GLint deltay = oldPosY - y;
        anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;
        angley += 360 * (GLfloat)deltax / (GLfloat)WinH;
        anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
        oldPosX = x;
        oldPosY = y;
        glutPostRedisplay();
    }
    else if (method == 0){
        int tempx = x - oldPosX;
        int tempy = y - oldPosY;
        degreex += tempx;
        degreey += tempy;
        oldPosX = x;
        oldPosY = y;
    }
}

void myIdle()
{
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("ObjLoader");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(moseMove);
    glutMotionFunc(motion);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(&keyboard);
    glutMainLoop();
    return 0;
}
