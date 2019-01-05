#include <GLUT/GLUT.h>
#include <math.h>
#define GL_PI 3.1415f


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


GLfloat  whiteLight[]={0.2f,0.2f,0.2f,1.0f};
GLfloat  lightPos[]={0.0f,0.0f,0.0f,1.0f};

void RenderScene(void)
{
    static float fMoonRot = 0.0f;
    static float fEarthRot= 0.0f;
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-300.0f);
    
    //绘制太阳
    glColor3ub(255,0,0);
    glRotatef(1,0.0f,1.0f,0.0f);
    glDisable(GL_LIGHTING);
    //glutWireSphere(20, 20, 20);
    glutSolidSphere(60.0f,60.0f,60.0f);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    
    
    //绘制地球
    glColor3ub(0,0,255);
    glRotatef(fEarthRot,0.0f,1.0f,0.0f);
    glTranslatef(105.0f,0.0f,0.0f);
    glutSolidSphere(15.0f,15.0f,15.0f);
    
    
    //绘制月球
    glColor3ub(200,200,200);
    glRotatef(fMoonRot,0.0f,1.0f,0.0f);
    glTranslatef(30.0f,0.0f,0.0f);
    fMoonRot += 15.0f;
    if(fMoonRot >= 365.0f)
        fMoonRot = 0.0f;
    glutSolidSphere(6.0f,15.0f,15.0f);
    glPopMatrix();
    fEarthRot += 5.0f;
    if(fEarthRot>=365.0f)
        fEarthRot=0.0f;
    glutSwapBuffers();
}
void ChangeSize(GLsizei w,GLsizei h)
{
    GLfloat fAspect;
    if(h==0) h=1;
    glViewport(0,0,w,h);
    fAspect = (GLfloat)w/(GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,fAspect ,1.0,4000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
}

void SpecialKeys(int key ,int x, int y)
{
    if(key==GLUT_KEY_UP)
        xRot -= 5.0f;
    if(key==GLUT_KEY_DOWN)
        xRot +=5.0f;
    if(key == GLUT_KEY_LEFT)
        yRot -=5.0f;
    if(key == GLUT_KEY_RIGHT)
        yRot +=5.0f;
    
    
    xRot = (GLfloat)((const int)xRot %360);
    yRot = (GLfloat)((const int)yRot %360);
    glutPostRedisplay();
}
void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100,TimerFunc,1);
}
int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Orthographic Projection");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    SetupRC();
    glutTimerFunc(250,TimerFunc,1);
    glutMainLoop();
    return 0;
}
