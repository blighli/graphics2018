import sys

from interaction import Interactor

try:
    from OpenGL.GLUT import *
    from OpenGL.GLU import *
    from OpenGL.GL import *
except:
    print('PyOpenGL not found!')
    sys.exit(1)

red = '\x1b[31m'
origin = '\x1b[0m'



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
    glColor3f(0.0, 0.0, 1.0)
    glRasterPos3f(1.8, .5, 0)

    glEnable(GL_LIGHTING)
    glutSwapBuffers()

def init():
    glClearColor (1.0, 1.0, 0.6, 1.0)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)

    # Lights on
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0)
    glLightfv(GL_LIGHT0, GL_POSITION, [4, 4, 4, 1])
    lA = 0.8
    glLightfv(GL_LIGHT0, GL_AMBIENT, [lA, lA, lA, 1])
    lD = 1
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [lD, lD, lD, 1])
    lS = 1
    glLightfv(GL_LIGHT0, GL_SPECULAR, [lS, lS, lS, 1])

    # Teapot Apperance
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [0.2, 0.1, 0.05, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.7, 0.4, 0.1, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.3, 0.2, 0.1, 1])
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 2)

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
glutInitWindowSize(700, 700)
glutCreateWindow('Real Teapot')
init()
interaction.registerCallbacks()
glutDisplayFunc(display)
glutMainLoop()