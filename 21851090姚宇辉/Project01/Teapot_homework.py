from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math

"""设置光照"""
def init():
    specular=GLfloat_4(1.0, 1.0, 1.0, 1.0)
    shininess=GLfloat(20.0)
    light_position=GLfloat_4(5.0,5.0,10.0,1.0)
    white_light=GLfloat_4(1.0,1.0,1.0,1.0)
    model_ambient=GLfloat_4(0.2,0.2,0.2,1.0)

    glClearColor(0.0,0.0,0.0,0.0)
    glShadeModel(GL_SMOOTH)
    #定义物体材质（反射光线参数）
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular) #使用镜面材质颜色
    glMaterialfv(GL_FRONT,GL_SHININESS,shininess) #使用光泽度

    glLightfv(GL_LIGHT0,GL_POSITION,light_position) #定义光源位置
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light) #定义散射光为白色
    glLightfv(GL_LIGHT0,GL_SPECULAR,white_light) #定义镜面光为白色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,model_ambient) #光照模型为全局环境光

    glEnable(GL_LIGHTING) #驱动光源
    glEnable(GL_LIGHT0) #启动特定光源
    glEnable(GL_DEPTH_TEST)

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(r*math.cos(c*angle), h, r*math.sin(c*angle), 0.0,0.0,0.0, 0.0,1.0,0.0);
    #glScalef(scale_x,scale_y,scale_z)
    glutSolidTeapot(0.5*ratio)
    glutSwapBuffers();

def reshape(w,h):
    glViewport(0,0,GLsizei(w),GLsizei(h))
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    #这里用的是正视投影
    if w<h:
        glOrtho(-1.5,1.5,-1.5*h/w,1.5*h/w,-10.0,10.0)
    else:
        glOrtho(-1.5,1.5,-1.5*w/h,1.5*w/h,-10.0,10.0)
    glMatrixMode(GL_MODELVIEW)

"""鼠标滑轮改变缩放比控制远近"""
def  wheelMotion(button,dirt,x,y):
    global ratio
    if dirt>0 and ratio <2:
        ratio+=0.01
    elif dirt<0 and ratio>0 :
        ratio-=0.01
    
    
def mouseButton(button,state,x,y):
    if state==GLUT_DOWN:
        startX=x
        startY=y

def mouseMotion(x,y):
    global startX;global startY;global angle;global h
    angle=x-startX+angle  #改变视点与x轴的夹角从而左右旋转
    h=0.03*(y-startX)             #通过鼠标y的变化改变视点高度从而上下旋转，0.03调整旋转敏感度
    
    #防止物体消失
    if h>5:                                         
        h=5
    elif h<-5:
        h=-5
    startX=x
    startY=y

#主函数
startX=-1                       #鼠标移动起始位置x
startY=-1                       #鼠标移动起始位置y
angle=90                       #视点与x轴的夹角
h=0.0                               #视点高度（即y轴坐标）
c=math.pi/180.0     
r=1.5                                #视点绕y轴旋转的半径
scale_x=1.0;scale_y=1.0;scale_z=1.0   #缩放比
ratio=1.0

glutInit()
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH)
glutInitWindowPosition(100,100)
glutInitWindowSize(600,600)
glutCreateWindow("Hello Teapot")
init()
glutDisplayFunc(display)
glutReshapeFunc(reshape)
glutMouseFunc(mouseButton)
glutMotionFunc(mouseMotion)
glutMouseWheelFunc(wheelMotion)
glutIdleFunc(display)
glutMainLoop()

