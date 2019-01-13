import sys
from math import pi as PI
from math import sin, cos
from math import sqrt

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


def ReduceToUnit(vector):
    length = sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
    if (length == 0.0):
        length = 1.0
    vector[0] /= length
    vector[1] /= length
    vector[2] /= length


def calcNormal(v, out):
    v1 = [0.0 for i in range(3)]
    v2 = [0.0 for i in range(3)]
    out = [0.0 for i in range(3)]
    xx = 0
    yy = 1
    zz = 2

    v1[xx] = v[0][xx] - v[1][xx]
    v1[yy] = v[0][yy] - v[1][yy]
    v1[zz] = v[0][zz] - v[1][zz]

    v2[xx] = v[1][xx] - v[2][xx]
    v2[yy] = v[1][yy] - v[2][yy]
    v2[zz] = v[1][zz] - v[2][zz]

    out[xx] = v1[yy] * v2[zz] - v1[zz] * v2[yy]
    out[yy] = v1[zz] * v2[xx] - v1[xx] * v2[zz]
    out[zz] = v1[xx] * v2[yy] - v1[yy] * v2[xx]

    ReduceToUnit(out)


def RenderHead():
    global x, y, angle
    height = 25.0
    diameter = 30.0
    corners = [[0.0 for i in range(3)] for i in range(4)]
    normal = [0.0 for i in range(3)]
    step = (PI / 3.0)

    glColor3f(255, 255, 255)

    glFrontFace(GL_CCW)
    glBegin(GL_TRIANGLE_FAN)
    glNormal3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.0, height / 2.0)

    glVertex3f(0.0, diameter, height / 2.0)

    angle = (2.0 * PI) - step
    while angle > 0:
        x = diameter * sin(angle)
        y = diameter * cos(angle)
        glVertex3f(x, y, height / 2.0)
        angle -= step

    glVertex3f(0.0, diameter, height / 2.0)
    glEnd()

    glBegin(GL_TRIANGLE_FAN)

    glNormal3f(0.0, 0.0, -1.0)
    glVertex3f(0.0, 0.0, -height / 2.0)

    angle = 0
    while angle < (2.0 * PI) - step:
        x = diameter * sin(angle)
        y = diameter * cos(angle)
        glVertex3f(x, y, -height / 2.0)
        angle += step

    glVertex3f(0.0, diameter, -height / 2.0)
    glEnd()

    glBegin(GL_QUADS);
    angle = 0
    while angle < (2.0 * PI) - step:
        x = diameter * sin(angle)
        y = diameter * cos(angle)
        corners[0][0] = x
        corners[0][1] = y
        corners[0][2] = -height / 2.0

        corners[1][0] = x
        corners[1][1] = y
        corners[1][2] = height / 2.0

        x = diameter * sin(angle + step)
        y = diameter * cos(angle + step)

        if (angle + step < 3.1415 * 2.0):
            corners[2][0] = x
            corners[2][1] = y
            corners[2][2] = height / 2.0

            corners[3][0] = x
            corners[3][1] = y
            corners[3][2] = -height / 2.0
        else:
            corners[2][0] = 0.0
            corners[2][1] = diameter
            corners[2][2] = height / 2.0

            corners[3][0] = 0.0
            corners[3][1] = diameter
            corners[3][2] = -height / 2.0

        calcNormal(corners, normal)
        glNormal3fv(normal)

        glVertex3fv(corners[0])
        glVertex3fv(corners[1])
        glVertex3fv(corners[2])
        glVertex3fv(corners[3])
        angle += step

    glEnd()


def RenderShaft():
    global x, z, angle
    height = 75.0
    diameter = 20.0
    corners = [[0.0 for i in range(3)] for i in range(2)]
    normal = [0.0 for i in range(3)]
    step = (PI / 50.0)

    glColor3f(255, 255, 255)

    glBegin(GL_QUAD_STRIP)

    angle = (2.0 * PI)
    while angle > 0:
        x = diameter * sin(angle)
        z = diameter * cos(angle)

        corners[0][0] = x
        corners[0][1] = -height / 2.0
        corners[0][2] = z
        corners[1][0] = x
        corners[1][1] = height / 2.0
        corners[1][2] = z

        normal[0] = corners[1][0]
        normal[1] = 0.0
        normal[2] = corners[1][2]
        ReduceToUnit(normal)
        glNormal3fv(normal)
        glVertex3fv(corners[0])
        glVertex3fv(corners[1])
        angle -= step

    glVertex3f(diameter * sin(2.0 * PI), -height / 2.0, diameter * cos(2.0 * PI))
    glVertex3f(diameter * sin(2.0 * PI), height / 2.0, diameter * cos(2.0 * PI))
    glEnd()

    glBegin(GL_TRIANGLE_FAN)
    glNormal3f(0.0, -1.0, 0.0)

    glVertex3f(0.0, -height / 2.0, 0.0)

    angle = (2.0 * PI)
    while angle > 0:
        x = diameter * sin(angle)
        z = diameter * cos(angle)
        glVertex3f(x, -height / 2.0, z)
        angle -= step
    glVertex3f(diameter * sin(2.0 * PI), -height / 2.0, diameter * cos(2.0 * PI))
    glEnd()


def RenderThread():
    global x, y, z, angle
    height = 75.0
    diameter = 20.0
    corners = [[0.0 for i in range(3)] for i in range(4)]
    normal = [0.0 for i in range(3)]
    step = (PI / 32.0)
    revolutions = 7.0
    threadWidth = 2.0
    threadThick = 3.0
    zstep = 0.125

    glColor3f(255, 255, 255)
    z = -height / 2.0 + 2

    angle = 0
    while angle < (2.0 * PI) * revolutions:
        x = diameter * sin(angle)
        y = diameter * cos(angle)
        corners[0][0] = x
        corners[0][1] = y
        corners[0][2] = z
        x = (diameter + threadWidth) * sin(angle)
        y = (diameter + threadWidth) * cos(angle)
        corners[1][0] = x
        corners[1][1] = y
        corners[1][2] = z
        x = (diameter + threadWidth) * sin(angle + step)
        y = (diameter + threadWidth) * cos(angle + step)
        corners[2][0] = x
        corners[2][1] = y
        corners[2][2] = z + zstep
        x = (diameter) * sin(angle + step)
        y = (diameter) * cos(angle + step)
        corners[3][0] = x
        corners[3][1] = y
        corners[3][2] = z + zstep
        glFrontFace(GL_CCW)
        glBegin(GL_TRIANGLES)

        calcNormal(corners, normal)
        glNormal3fv(normal)
        glVertex3fv(corners[0])
        glVertex3fv(corners[1])
        glVertex3fv(corners[2])

        glVertex3fv(corners[2])
        glVertex3fv(corners[3])
        glVertex3fv(corners[0])

        glEnd()
        corners[0][2] += threadThick
        corners[3][2] += threadThick

        calcNormal(corners, normal)
        normal[0] = -normal[0]
        normal[1] = -normal[1]
        normal[2] = -normal[2]

        glFrontFace(GL_CW)

        glBegin(GL_TRIANGLES)
        glNormal3fv(normal)

        glVertex3fv(corners[0])
        glVertex3fv(corners[1])
        glVertex3fv(corners[2])

        glVertex3fv(corners[2])
        glVertex3fv(corners[3])
        glVertex3fv(corners[0])

        glEnd()

        z += zstep
        angle += step


def RenderScene():
    global xRot, yRot
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glRotatef(xRot, 1.0, 0.0, 0.0)
    glRotatef(yRot, 0.0, 0.0, 1.0)
    RenderShaft()
    glPushMatrix()
    glRotatef(-90.0, 1.0, 0.0, 0.0)
    RenderThread()
    glTranslatef(0.0, 0.0, 45.0)
    RenderHead()
    glPopMatrix()

    glPopMatrix()
    glutSwapBuffers()


def SetupRC():
    ambientLight = [0.4, 0.4, 0.4, 1.0]
    diffuseLight = [0.7, 0.7, 0.7, 1.0]
    specular = [0.9, 0.9, 0.9, 1.0]
    lightPos = [-50.0, 200.0, 200.0, 1.0]
    specref = [0.6, 0.6, 0.6, 1.0]

    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)
    glFrontFace(GL_CCW)

    glEnable(GL_LIGHTING)

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight)
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular)

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos)
    glEnable(GL_LIGHT0)

    glEnable(GL_COLOR_MATERIAL)

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE)

    glMaterialfv(GL_FRONT, GL_SPECULAR, specref)
    glMateriali(GL_FRONT, GL_SHININESS, 64)

    glClearColor(0.0, 0.0, 0.0, 1.0)


def ChangeSize(w, h):
    nRange = 100.0
    if (h == 0):
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if (w <= h):
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange * 2.0, nRange * 2.0)
    else:
        glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange * 2.0, nRange * 2.0)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def SpecialKeys(key, x, y):
    global xRot, yRot
    if (key == GLUT_KEY_UP):
        xRot -= 5.0
    if (key == GLUT_KEY_DOWN):
        xRot += 5.0
    if (key == GLUT_KEY_LEFT):
        yRot -= 5.0
    if (key == GLUT_KEY_RIGHT):
        yRot += 5.0
    if (key > 356.0):
        xRot = 0.0
    if (key < -1.0):
        xRot = 355.0
    if (key > 356.0):
        yRot = 0.0
    if (key < -1.0):
        yRot = 355.0
    glutPostRedisplay()


xRot = 0.0
yRot = 0.0
print("箭头键可以改变视！")
glutInit()
glutInitWindowSize(700, 700)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutCreateWindow("Completed Bolt")

glutReshapeFunc(ChangeSize)
glutSpecialFunc(SpecialKeys)
glutDisplayFunc(RenderScene)
SetupRC()
glutMainLoop()


