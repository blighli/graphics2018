from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import os
import time
global year0, year1, year2, year3, day
def init():
    global year0, year1, year2, year3, day
    year0, year1, year2, year3, day = 0, 0, 0, 0, 0
    mat_spectual = [1.0,1.0,1.0,1.0]
    mat_shiness = [50.0]
    light_position = [1.0,1.0,1.0,0.0]
    Light_Model_Ambient = [0.2,0.2,0.2,1.0]
    white_light= [1.0,1.0,1.0,1.0]
    # glmaterialfv 材料反射指数
    # glLightfv 光源位置
    # glshapemodel 阴影模型
    glClearColor(0.0,0.0,0.0,0.0)
    glShadeModel(GL_SMOOTH)
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spectual)
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shiness)
    glLightfv(GL_LIGHT0,GL_POSITION,light_position)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light)
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient)
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_DEPTH_TEST)

    return
def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)

    glPushMatrix()
    global year0, year1, year2, year3, day
    day = (day + 5) % 360
    year0 = (year0 + 2) % 360
    year1 = (year1 + 2) % 360
    year2 = (year2 + 3) % 360
    year3 = (year3 + 5) % 360

    glRotatef(year0, 0.0, 0.0, 1.0)
    glColor3f(1.0, 0.0, 0.0)
    glutSolidSphere(1.0, 30, 30)

    glPopMatrix()
    glPushMatrix()
    glRotatef(year1, 0.0, 0.0, 1.0)
    glTranslatef(0.0, 1.5, 0.0)
    glRotatef(day, 0.0, 0.0, 1.0)
    glColor3f(0.0, 1.0, 0.0)
    glutSolidSphere(0.25, 30, 30)

    glPopMatrix()
    glPushMatrix()
    glRotatef(year2, 0.0, 0.0, 1.0)
    glTranslatef(0.0, -2.8, 0.0)
    glRotatef(day, 0.0, 0.0, 1.0)
    glColor3f(0.0, 0.0, 1.0)
    glutSolidSphere(0.3, 30, 30) 

    glRotatef(year3, 0.0, 0.0, 1.0)
    glTranslatef(0.0, 0.5, 0.0)
    glRotatef(day, 0.0, 0.0, 1.0)
    glColor3f(0.0, 1.0, 1.0)
    glutSolidSphere(0.08, 30, 30) 

    glutPostRedisplay()
    glPopMatrix()
    glFlush()
    glutSwapBuffers()
    time.sleep(0.05)


def reshape(w,h):
    glViewport(0, 0, w, h)
    ## 设置操作当前的矩阵是投影矩阵
    glMatrixMode(GL_PROJECTION)

    ## 设置当前矩阵为单位矩阵
    glLoadIdentity()

    if (w <= h):
        ## 创建一个正交投影。参数分别为x,y,z的最小最大坐标。
        glOrtho(-1.5, 1.5, -1.5 *  h / w,1.5*h/w, -10.0, 10.0 )
    else:
        glOrtho(-1.5 * w /h, 1.5 *w /h, -1.5, 1.5, -10.0, 10.0)
    ## 对模型视图矩阵堆进行随后的操作
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)

if __name__=="__main__":

    glutInit()
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH)
    glutInitWindowSize(900,600)
    glutInitWindowPosition(100,100)
    glutCreateWindow(b"homework2")
    init()
    glutDisplayFunc(display)
    glutIdleFunc(display)
    glutReshapeFunc(reshape)
    glutMainLoop()