from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
zoom = 1
mouseLeftDown = False;
mouseRightDown = False;
mouseX = 0.0;
mouseY = 0.0;
cameraDistanceX = 0.0;
cameraDistanceY = 0.0;

cameraAngleX = 0.0;
cameraAngleY = 0.0;
def mouseCB(button, state, x, y):
    global mouseX
    global mouseY
    mouseX = x;
    mouseY = y;
    global mouseLeftDown
    global mouseRightDown
    if(button == GLUT_LEFT_BUTTON):
        if(state == GLUT_DOWN):
            mouseLeftDown = True;
        elif (state == GLUT_UP):
            mouseLeftDown = False;

    elif (button == GLUT_RIGHT_BUTTON):
        if(state == GLUT_DOWN):
            mouseRightDown = True
        elif(state == GLUT_UP):
            mouseRightDown = False;


def mouseMotionCB(x,y):
    global cameraAngleX
    global cameraAngleY
    global cameraDistanceX
    global cameraDistanceY
    global mouseX
    global mouseY
    global zoom
    if(mouseLeftDown):
        cameraAngleX += 0.01*(x-mouseX)
        cameraAngleY += 0.01*(y-mouseY)
        mouseX = x
        mouseY = y
    if(mouseRightDown):
        cameraDistanceY = (y-mouseY)*0.01
        # print(cameraDistanceY)
        cameraDistanceX = (x-mouseX)*0.01
        # zoom = (y - mouseY)*0.5
        mouseX = x
        mouseY = y

        # print(zoom)
    glutPostRedisplay()

def wheelMotion(button,direction,x,y):
    global zoom
    if(direction>0):
        zoom +=0.1
    elif (direction < 0):
        zoom -= 0.1


def drawFunc():
    global zoom
    glClear(GL_COLOR_BUFFER_BIT)
    glTranslatef(cameraDistanceX, cameraDistanceY, 0);
    glRotatef(cameraAngleX, 1, 0, 0);
    glRotatef(cameraAngleY, 0, 1, 0);
    glutWireTeapot(zoom)
    glFlush()

glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
glutInitWindowSize(800, 800)
glutCreateWindow("firstWork")
glutMouseFunc(mouseCB);
glutMouseWheelFunc(wheelMotion)
glutMotionFunc(mouseMotionCB);
glutDisplayFunc(drawFunc)
glutMainLoop()

