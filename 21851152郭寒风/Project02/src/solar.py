from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from PIL import Image
import sys

global angle1, angle2
angle1, angle2 = 0, 0


def loadTexture(imagePath):
    image = Image.open(imagePath)

    ix = image.size[0]
    iy = image.size[1]
    image = image.tobytes("raw", "RGBX", 0, -1)

    texture_id = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texture_id)

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image)
    # glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    # glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    # glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)

    return texture_id


def drawTexturedSphere(texturePath, radius):
    glEnable(GL_TEXTURE_2D)
    loadTexture(texturePath)

    sphere = gluNewQuadric()
    gluQuadricOrientation(sphere, GLU_OUTSIDE)
    gluQuadricNormals(sphere, GLU_SMOOTH)
    gluQuadricTexture(sphere, GL_TRUE)
    gluSphere(sphere, radius, 50, 50)
    gluDeleteQuadric(sphere)


def onDisplay():
    global angle1, angle2

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    glPushMatrix()

    glTranslatef(0.0, 0.0, -50.0)
    glRotatef(angle1, 0.0, 1.0, 0.0)
    glMaterialfv(GL_FRONT, GL_AMBIENT, [.8, .4, .3, .5])
    drawTexturedSphere("../imgs/sun.bmp", 1.3)

    glPushMatrix()
    glTranslatef(5.0, 0.0, 0.0)
    glRotatef(angle1 * .9, 3.0, 4.0, 5.0)
    glMaterialfv(GL_FRONT, GL_EMISSION, [.5, .5, .5, .8])
    glMaterialfv(GL_FRONT, GL_AMBIENT, [.4, .4, .4, .8])
    drawTexturedSphere("../imgs/earth.bmp", .8)
    glPopMatrix()

    glPushMatrix()
    glTranslatef(6.5, 0.0, 0.0)
    glRotatef(angle2, 2.0, 3.0, 4.0)
    glMaterialfv(GL_FRONT, GL_EMISSION, [.5, .5, .5, 1.0])
    glMaterialfv(GL_FRONT, GL_AMBIENT, [.4, .4, .4, 1.0])
    drawTexturedSphere("../imgs/moon.bmp", .3)
    glPopMatrix()

    glPopMatrix()
    glutSwapBuffers()
    angle1 = (angle1 + 4) % 360
    angle2 = (angle2 + 20) % 360


def setup():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glDepthFunc(GL_LEQUAL)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    glMatrixMode(GL_MODELVIEW)

    glLightfv(GL_LIGHT0, GL_AMBIENT, [0.5, 0.5, 0.5, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [1.0, 1.0, 1.0, 1.0])
    glLightfv(GL_LIGHT0, GL_SPECULAR, [1.0, 1.0, 1.0, 1.0])
    glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 0.0, 20.0, 1.0])
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)


def onWindowReshape(w, h):
    if h == 0:
        h = 1

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(15.0, float(w)/float(h), 0.1, 100.0)
    glMatrixMode(GL_MODELVIEW)


def tick(x):
    glutPostRedisplay()
    glutTimerFunc(100, tick, 1)


glutInit(sys.argv)
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(1280, 720)
glutCreateWindow("Solar Sim")

glutReshapeFunc(onWindowReshape)
glutDisplayFunc(onDisplay)
glutTimerFunc(500, tick, 1)

setup()
glutMainLoop()
