from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import numpy as np
import sys
def drawfunc():
    glClear(GL_COLOR_BUFFER_BIT)
    glutWireTeapot(0.5)
    glFlush()

def keyboardFunc(key,x,y):
    if(key==b'W' or key == b'w'):
        glTranslate(0, 0.1, 0)
    elif(key==b'A' or key == b'a'):
        glTranslate(-0.1,0,0)
    elif (key == b'D' or key == b'd'):
        glTranslate(0.1,0,0)
    elif (key == b'S' or key == b's'):
        glTranslate(0,-0.1,0)
    elif (key ==b'T' or key==b't'):
        glRotate(1.0,1,0,0)
    elif (key ==b'g' or key==b'G'):
        glRotate(-1.0,1,0,0)
    elif (key ==b'f' or key==b'F'):
        glRotate(1.0,0,1,0)
    elif (key ==b'h' or key==b'H'):
        glRotate(-1.0,0,1,0)
    elif (key ==b'R' or key==b'r'):
        glRotate(-1.0,0,0,1)
    elif (key ==b'y' or key==b'y'):
        glRotate(1.0,0,0,1)

if __name__ == '__main__':
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB)
    # glutInitWindowPosition(100,100)
    glutInitWindowSize(600,600)
    glutCreateWindow(b"function plotter")
    glutDisplayFunc(drawfunc)
    glutIdleFunc(drawfunc)
    # glClearColor(1.0,1.0,1.0,1.0) 背景颜色
    # gluOrtho2D(-5.0,5.0,-5.0,5.0) 显示范围
    glutKeyboardFunc(keyboardFunc)
    glutMainLoop()