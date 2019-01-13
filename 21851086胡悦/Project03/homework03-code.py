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


def init():
    glClearColor(0, 0, 0, 0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glLightfv(GL_LIGHT0, GL_AMBIENT,
              [0.0, 0.0, 0.0, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE,
              [1.0, 1.0, 1.0, 1.0])
    glLightfv(GL_LIGHT0, GL_POSITION,
              [0.0, 3.0, 3.0, 0.0])
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
                   [0.2, 0.2, 0.2, 1.0])
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMaterialfv(GL_FRONT, GL_AMBIENT,
                 [0.1745, 0.0, 0.1, 0.0])
    glMaterialfv(GL_FRONT, GL_DIFFUSE,
                 [0.1, 0.0, 0.6, 0.0])
    glMaterialfv(GL_FRONT, GL_SPECULAR,
                 [0.7, 0.6, 0.8, 0.0])
    glMaterialf(GL_FRONT, GL_SHININESS, 80)
    glLoadIdentity()
    gluLookAt(r * math.cos(c * angle), h, r *
              math.sin(c * angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glScalef(size, size, size)
    glutSolidTeapot(0.5)
    glutSwapBuffers()


def reshape(w, h):
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(250, 250)
    glutCreateWindow("21851086-huyue-homework03")
    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    init()
    glutIdleFunc(display)
    glutMouseFunc(zoom)
    glutMotionFunc(move)
    glutMainLoop()


if __name__ == "__main__":
    main()
