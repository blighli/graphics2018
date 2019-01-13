from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math

PI = math.acos(-1.0)
angle = 90
prevX = -1
prevY = -1
r = 1.5
h = 0.0
c = PI / 180.0
currSize = 1.0
zoomStep = 0.03


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(r * math.cos(c * angle), h, r * math.sin(c * angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glColor3f(1.0, 1.0, 1.0)    #设置颜色
    glScalef(currSize, currSize, currSize)
    glutWireTeapot(0.4)
    glutSwapBuffers()


def Mouse(button, state, x, y):
    global prevX, prevY, currSize, zoomStep
    if state == GLUT_DOWN:
        prevX = x
        prevY = y
    elif state == GLUT_UP and button == GLUT_LEFT_BUTTON:
        currSize += zoomStep
    elif state == GLUT_UP and button == GLUT_RIGHT_BUTTON:
        currSize -= zoomStep

def onMouseMove(x, y):
    global prevX, prevY, angle, h
    angle += x - prevX
    h += 0.03 * (y - prevY)
    if h > 1.0:
        h = 1.0
    elif h < -1.0:
        h = -1.0
    prevX = x
    prevY = y


def init():
    glEnable(GL_DEPTH_TEST)


def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(75.0, float(w) / h, 1.0, 1000.0)
    glMatrixMode(GL_MODELVIEW)

def keyborad(key, x, y):
    global currSize, zoomStep
    if key == GLUT_KEY_UP:
        currSize += zoomStep
    elif key == GLUT_KEY_DOWN:
        currSize -= zoomStep

def main():
    glutInit()
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(500, 500)
    glutCreateWindow("jiangfeng")
    init()
    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    glutIdleFunc(display)
    glutKeyboardFunc(keyborad)
    glutMouseFunc(Mouse)
    glutMotionFunc(onMouseMove)
    glutMainLoop()

if __name__ == "__main__":
    main()
