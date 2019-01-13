from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from modelRenderer import *

global renderer, lastPos, mouseButtonDown
renderer = ModelRenderer()
lastPos = [0, 0]
mouseButtonDown = [False, False]


def lighting():
    glLightfv(GL_LIGHT0, GL_POSITION, [0, 0, 0])

    glLightfv(GL_LIGHT1, GL_POSITION, [0, 0, 100])
    glLightfv(GL_LIGHT1, GL_AMBIENT, [.317, .267, .576, 1.0])
    glLightfv(GL_LIGHT1, GL_DIFFUSE, [.7, .7, .7, 1.0])

    glLightfv(GL_LIGHT2, GL_POSITION, [-100, 0, 0])
    glLightfv(GL_LIGHT2, GL_AMBIENT, [.0, .0, 1.0, 1.0])
    glLightfv(GL_LIGHT2, GL_DIFFUSE, [.7, .7, .7, 1.0])

    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glEnable(GL_LIGHT2)


def init():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_LIGHTING)


def reshape(w, h):
    if h == 0:
        h = 1

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(w)/float(h), 0.1, 1000.0)
    glMatrixMode(GL_MODELVIEW)


def idle():
    glutPostRedisplay()


def display():
    global renderer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    lighting()
    glColor3f(1.0, 1.0, 1.0)
    renderer.render_scene()


def mouseMove(button, state, x, y):
    lastPos[0], lastPos[1] = x, y

    if button == GLUT_LEFT_BUTTON:
        mouseButtonDown[0] = state == GLUT_DOWN
    if button == GLUT_RIGHT_BUTTON:
        mouseButtonDown[1] = state == GLUT_DOWN
    pass


def mouseMotion(x, y):
    if mouseButtonDown[0]:
        renderer.camAngle[1] += (x - lastPos[0]) * .5
        renderer.camAngle[0] += (y - lastPos[1]) * .5
        lastPos[0], lastPos[1] = x, y
    if mouseButtonDown[1]:
        renderer.camDist[0] += (x - lastPos[0]) * .03
        renderer.camDist[1] -= (y - lastPos[1]) * .03
        lastPos[0], lastPos[1] = x, y
    pass


def keyboard(key, x, y):
    if key == b'w':
        renderer.move_forward(-.3)
    elif key == b's':
        renderer.move_forward(.3)

    elif key == b'a':
        renderer.move_right(-.3)
    elif key == b'd':
        renderer.move_right(.3)

    elif key == b'q':
        renderer.move_up(.3)
    elif key == b'e':
        renderer.move_up(-.3)

    elif key == b'z':
        renderer.scaleAll(-.05)
    elif key == b'c':
        renderer.scaleAll(.05)

    elif key == b'f':
        renderer.reset()


glutInit(sys.argv)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowPosition(100, 100)
glutInitWindowSize(800, 600)
glutCreateWindow(b"The Monkey")
init()
glutReshapeFunc(reshape)
glutDisplayFunc(display)
glutMouseFunc(mouseMove)
glutMotionFunc(mouseMotion)
glutKeyboardFunc(keyboard)
glutIdleFunc(idle)
glutMainLoop()
