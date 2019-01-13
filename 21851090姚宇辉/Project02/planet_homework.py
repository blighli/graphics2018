from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import time

def init():
    global a;global b;global c;global d;global e;global f
    glShadeModel(GL_SMOOTH)
    glEnable(GL_DEPTH_TEST)
    #glEnable(GLUT_MULTISAMPLE)
    glEnable(GL_LIGHTING)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_1)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glMatrixMode(GL_PROJECTION) #设置投影矩阵
    glLoadIdentity()
    gluPerspective(60, 1, 0.1, 100000)
    glClearColor(0, 0, 0, 1)
    a = 500
    b = 20.0
    c = 50.0
    d = e = f = 0


def timerFunc(value):
    glutPostRedisplay()
    glutTimerFunc(10, timerFunc, 1)


def display():
    global a;global b;global c
    global l_position;global color_index;global sun;global re_set;global earth;global moon
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) # Clear Screen And Depth Buffer
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glLightfv(GL_LIGHT1, GL_POSITION, l_position)
    gluLookAt(b, c, a,0,0,0,0,1,0)
    glLightfv(GL_LIGHT0, GL_POSITION, l_position)
    glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, color_index)
    glMaterialfv(GL_FRONT, GL_EMISSION, sun)
    glutSolidSphere(50, 100, 100)
    
    glMaterialfv(GL_FRONT, GL_EMISSION, re_set)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth)
    glRotatef(time.clock()*10, 0, 0, 1)
    glTranslated(200, 0, 0)
    glutSolidSphere(30, 100, 100)
    glRotated(time.clock()*10, 0, 0, 1)
    glTranslated(-75, 0, 0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moon)
    glutSolidSphere(10, 30, 30)
    glutSwapBuffers()


l_position = GLfloat_4(0,0,0,1)
tag = 2 #初始表示画多边形
a=0; b=0; c=0; d=0; e=0; f=0
sun= GLfloat_4(1,0.2,0.2,1)
sun_light = GLfloat_4(1,0.8,0.8,1)
re_set= GLfloat_4(0,0,0.0,0)
earth= GLfloat_4(0,0.6,1,1)
earth_ = GLfloat_4(0,0,0.1,0)
color_index = GLfloat_3(1,1,1)
moon= GLfloat_4 (0.8,0.8,0.8,1)
light_1= GLfloat_4(0.2,0.2,0.2,1)

glutInit()
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowSize(500, 500)
glutInitWindowPosition(50, 50)
glutCreateWindow("Hello World")

init()
glutDisplayFunc(display)
glutTimerFunc(10, timerFunc, 1)


glutMainLoop()
