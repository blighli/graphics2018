import math

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

PI = math.acos(-1.0)
angle = 90
x = -1
y = -1
r = 1.5
h = 0.0
c = PI / 180.0
size = 1.0
step = 0.03


def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(r * math.cos(c * angle), h, r *
              math.sin(c * angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glScalef(size, size, size)
    glutWireTeapot(0.5)
    glutSwapBuffers()


def reDraw(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(75.0, float(w) / h, 1.0, 1000.0)
    glMatrixMode(GL_MODELVIEW)


def zoom(button, event, newx, newy):
    global x, y, size, step
    if event == GLUT_DOWN:
        x = newx
        x = newy
    elif event == GLUT_UP and button == GLUT_LEFT_BUTTON:
        size += step
    elif event == GLUT_UP and button == GLUT_RIGHT_BUTTON:
        size -= step


def move(newx, newy):
    global angle, x, y, h
    angle += newx - x
    h += step * (newy - y)
    if h > 1.0:
        h = 1.0
    elif h < -1.0:
        h = -1.0
    x = newx
    y = newy


def main():
    glutInit()
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
    glutInitWindowSize(800, 600)
    glutCreateWindow("21851086-huyue-homework01")
    glEnable(GL_DEPTH_TEST)
    glutReshapeFunc(reDraw)
    glutDisplayFunc(draw)
    glutIdleFunc(draw)
    glutMouseFunc(zoom)
    glutMotionFunc(move)
    glutMainLoop()


if __name__ == "__main__":
    main()
