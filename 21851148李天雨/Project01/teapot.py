from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

#import common
import sys

roate = 0.0 # 设置旋转速率
rote = 0.0 #旋转角度
anglex = 0.0#/X 轴旋转
angley = 0.0 #Y 轴旋转
anglez = 0.0#Z 轴旋转
WinW = 400
WinH = 400
oldx = 0#记录鼠标坐标
oldy = 0
size = 1

def init():
    glClearColor(1.0, 1.0, 1.0, 1.0)
    
def display():
    glClear(GL_COLOR_BUFFER_BIT)
    glutWireTeapot(0.5)
        #rote = rote + roate
        #glRotatef(angle, 0.0, 1.0, 0.0)
        #angle =angle +  1.0
    
    glLoadIdentity()  #加载单位矩阵
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    
    glRotatef(rote, 0.0, 1.0, 0.0)
    glRotatef(anglex, 1.0, 0.0, 0.0)
    glRotatef(angley, 0.0, 1.0, 0.0)
    glRotatef(anglez, 0.0, 0.0, 1.0)
    glScalef(size,size,size)
    
    glutSwapBuffers()
    #glFlush()
    
def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(20.0, w / h, 0.5,10.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    
def motion(x,y):
    global oldx
    global oldy
    global anglex
    global angley
    global anglez
    global WinH
    global WinW
    deltax = oldx - x
    deltay = oldy - y
    anglex += 360 * deltax / WinW #根据屏幕上鼠标滑动的距离来设置旋转的角度
    angley += 360 * deltay / WinH
    anglez += 360 * deltay / WinH
    oldx = x
    oldy = y
    glutPostRedisplay()
    glutPostRedisplay()
    
def mouse(button,state,x,y):
    global oldy
    global oldx
    if (button == GLUT_LEFT_BUTTON):
        if (state == GLUT_DOWN):
            roate = 0
            rote = 0
            oldx = x #记录鼠标坐标
            oldy = y
            print("left")
            print(oldx,oldy)
    
    if (button == GLUT_RIGHT_BUTTON):
        if (state == GLUT_DOWN):
            roate = roate + 1.0
            print("right")

def keypress(key, x, y):
        global size
        key = str(key, encoding = "utf8")
        if key in ('b', 'B'):
            size += 0.1
            print(size)
        if key in ('s', 'S'):
            size -= 0.1
            print(size)

def main():
        global window
        glutInit(sys.argv)
        #glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
        glutInitWindowSize(600,400)
        window = glutCreateWindow("teapot")
        
        #init()
        glutDisplayFunc(display)
        glutReshapeFunc(reshape)
        glutMouseFunc(mouse)
        glutMotionFunc(motion)
        glutIdleFunc(display)
        glutKeyboardFunc(keypress)
        glutMainLoop()

main()








