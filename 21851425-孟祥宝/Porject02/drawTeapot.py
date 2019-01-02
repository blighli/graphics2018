#!/opt/local/bin/python
# _*_ coding: utf-8 _*_

'Real Teapot'

__author__ = 'Ethan Mengoreo'


import sys

from interaction import Interactor

try:
    from OpenGL.GLUT import *
    from OpenGL.GLU import *
    from OpenGL.GL import *
    from PIL import Image
except:
    print('PyOpenGL not found!')
    sys.exit(1)

red = '\x1b[31m'
origin = '\x1b[0m'

print()
print(f'Press {red}ESC{origin} to close the window.')
print(f'Hold and Drag {red}Right Mouse Key{origin} to move.')
print(f'Hold and Drag {red}Left Mouse Key{origin} to rotate.')
print(f'Use {red}Mouse Wheel{origin} to scale, if not working, hold and drag the wheel.')
filename = 'teapot.png'


def display():
    '''Display a "real" teapot.'''
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    xSize, ySize = glutGet(GLUT_WINDOW_WIDTH), glutGet( GLUT_WINDOW_HEIGHT)
    gluPerspective(60, float(xSize) / float(ySize), 0.1, 50)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0, 0, -4)
    global interaction
    interaction.applyTransformation()
    glCallList(tkList)
    glDisable(GL_LIGHTING)
    glColor3f(1, 1, 0.3)
    glRasterPos3f(1.8, .5, 0)

    glEnable(GL_LIGHTING)
    glutSwapBuffers()

def loadTextureFromFile(filename):
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glShadeModel(GL_FLAT)
    glEnable(GL_DEPTH_TEST)

    image = Image.open(filename)

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    # print(type(self.image))
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.size[0], image.size[1], 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image)


def init():
    glClearColor (0.99, 0.99, 0.99, 0)

    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_TEXTURE_2D)

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 0)
    image = Image.open(filename)


    # Lights on


    glLightfv(GL_LIGHT0, GL_POSITION, [4, 4, 4, 1])
    lA = 0.8
    glLightfv(GL_LIGHT0, GL_AMBIENT, [lA, lA, lA, 1])
    lD = 1
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [lD, lD, lD, 1])
    lS = 1
    glLightfv(GL_LIGHT0, GL_SPECULAR, [lS, lS, lS, 1])

    # Teapot Apperance
    # glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [0.2125, 0.1275, 0.054, 1])
    # glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.714, 0.4284, 0.18144, 1])
    # glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.393548, 0.271906, 0.16672, 1])
    # glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.6)
    # glClearColor(0.0, 0.0, 0.0, 0.0)
    # glShadeModel(GL_FLAT)
    # glEnable(GL_DEPTH_TEST)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    # print(type(self.image))
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.size[0], image.size[1], 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image.tobytes('raw', 'RGBA', 0, -1))

    # Load Texture
    # loadTextureFromFile(filename)

    # Initialise interaction

    global interaction
    interaction = Interactor(.01, 1)
    global tkList
    tkList = glGenLists(1)
    glNewList(tkList, GL_COMPILE)
    glutSolidTeapot(1.0)


    glEndList()

# Show it
glutInit(sys.argv)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowSize(500, 500)
glutCreateWindow('Real Teapot')
init()
glutDisplayFunc(display)
interaction.registerCallbacks()
glutMainLoop()
