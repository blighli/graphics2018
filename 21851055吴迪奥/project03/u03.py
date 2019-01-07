from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math
from objModel import *
global c,r
global degree
global oldPosX
global oldPoxY
path = "teddy.obj"
def setLightPos():
    lightPostion = [1.0,0.0,1.0,0.0]
    lightPostion_2 = [1.0,1.0,0.0,0.0]
    glLightfv(GL_LIGHT0,GL_POSITION,lightPostion)
    glLightfv(GL_LIGHT1, GL_POSITION, lightPostion_2)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
def mouseMove(button,state,x,y):
    global oldPosX
    global oldPoxY
    if(state==GLUT_DOWN):
        oldPosX = x
        oldPoxY = y

def changeViewPoint(x,y):
    global degree
    global oldPosX
    global oldPoxY
    temp = x-oldPosX
    degree += temp
    oldPosX = x
    oldPoxY = y
def init():
    global c, r
    global degree
    global oldPosX
    global oldPoxY
    c = 3.1415926/180.0
    r = 1.0
    degree = 90.0
    oldPosX = -1
    oldPoxY = -1
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGB|GLUT_DOUBLE)
    glutInitWindowSize(500,500)
    glutCreateWindow("ObjLoader")
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)
    setLightPos()
    glEnable(GL_DEPTH_TEST)
def myIde():
    glutPostRedisplay()

def display():
    glColor3f(1.0,1.0,1.0)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0.0,0.0,-100.0)
    setLightPos()
    glPushMatrix()
    global r
    global degree
    global c
    gluLookAt(r*math.cos(c*degree), 0, r*math.sin(c*degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    objmodel = objModel()
    objmodel.SetData(path)
    objmodel.draw()
    glPopMatrix()
    glutSwapBuffers()

def reshape(width,height):
    glViewport(0,0,width,height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0,1.0*width/height,1.0,200.0)
    glMatrixMode(GL_MODELVIEW)

if __name__ =="__main__":
    glutInit()
    init()
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutMouseFunc(mouseMove)
    glutMotionFunc(changeViewPoint)
    glutIdleFunc(myIde)
    glutMainLoop()
