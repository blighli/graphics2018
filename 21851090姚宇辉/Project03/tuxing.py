from opengl.Pic import Point3,FaVector,Mian,WenLi
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math

"""导入obj 3D模型"""
def readPic(type):
    f=[];v=[];vn=[];vt=[]
    with open("bunny.obj") as read_Obj:
        lines=read_Obj.readlines()
    m=len(lines)
    for line in lines:
        if line[0]=='v':
            if line[1]=='t':
                lineArr=line.strip('\n ').split(' ')
                wenli=WenLi(float(lineArr[1]),float(lineArr[2]))
                vt.append(wenli)
            elif line[1]=='n':
                lineArr=line.strip('\n ').split(' ')
                faVector=FaVector(float(lineArr[1]),float(lineArr[2]),float(lineArr[3]))
                vn.append(faVector)
            else:
                lineArr=line.strip('\n ').split(' ')
                point=Point3(float(lineArr[1]),float(lineArr[2]),float(lineArr[3]))
                v.append(point)
        elif line[0]=='f' and type==1:
            lineArr=line.strip('\n ').split(' ')
            V=[];T=[];N=[]
            for i in range(1,len(lineArr)):
                IndexArr=lineArr[i].split('/')
                V.append(int(IndexArr[0])-1)
                T.append(int(IndexArr[1])-1)
                N.append(int(IndexArr[2])-1)
            mian=Mian(V,T,N)
            f.append(mian)
        elif line[0]=='f' and type==0:
            lineArr = line.strip('\n ').split(' ')
            V = [];T=[];N = []
            for i in range(1, len(lineArr)):
                IndexArr = lineArr[i].split('//')
                V.append(int(IndexArr[0]) - 1)
                N.append(int(IndexArr[1]) - 1)
            mian = Mian(V, T, N)
            f.append(mian)
    return f,v,vn,vt

"""根据内存中的各个obj结构绘制3D模型"""
def draw():
    global f;global v;global vt;global vn
    for i in range(len(f)):
        glBegin(GL_TRIANGLES)
        #绘制上顶点
        if len(vt)!=0:
            glTexCoord2f(vt[f[i].T[0]].TU,vt[f[i].T[0]].TU)
        if len(vn)!=0:
            glNormal3f(vn[f[i].N[0]].NX,vn[f[i].N[0]].NY,vn[f[i].N[0]].NZ)
        glVertex3f(v[f[i].V[0]].X/700,v[f[i].V[0]].Y/700,v[f[i].V[0]].Z/700)
        #绘制左下顶点
        if len(vt)!=0:
            glTexCoord2f(vt[f[i].T[1]].TU,vt[f[i].T[1]].TU)
        if len(vn)!=0:
            glNormal3f(vn[f[i].N[1]].NX,vn[f[i].N[1]].NY,vn[f[i].N[1]].NZ)
        glVertex3f(v[f[i].V[1]].X/700,v[f[i].V[1]].Y/700,v[f[i].V[1]].Z/700)
        #绘制右下顶点
        if len(vt)!=0:
            glTexCoord2f(vt[f[i].T[2]].TU,vt[f[i].T[2]].TU)
        if len(vn)!=0:
            glNormal3f(vn[f[i].N[2]].NX,vn[f[i].N[2]].NY,vn[f[i].N[2]].NZ)
        glVertex3f(v[f[i].V[2]].X/700,v[f[i].V[2]].Y/700,v[f[i].V[2]].Z/700)
        glEnd()

"""初始化场景参数"""
def initScene():
    glClearColor(0.000,0.000,0.000,1.0)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_LIGHT0) #启用0号灯到7号灯（光源）  光源要求由函数glLight函数完成
    glEnable(GL_LIGHTING)   #启用光源
    glEnable(GL_DEPTH_TEST) #启用深度测试
    glEnable(GL_TEXTURE_2D) #启用二维纹理

    #global glfMatAmbient;global glfMatDiffuse;global glfMatSpecular;global glfMatEmission;global fShininess
    glfMatAmbient=GLfloat_4(0.000,0.450,1.000,1.0)
    glfMatDiffuse = GLfloat_4(0.000, 0.000, 0.580, 1.0)
    glfMatSpecular = GLfloat_4(1.000, 1.000, 1.000, 1.0)
    glfMatEmission = GLfloat_4(0.000, 0.000, 0.000, 1.0)
    fShininess=128.000

    """指定光照计算的当前材质属性"""
    glMaterialfv(GL_FRONT,GL_AMBIENT,glfMatAmbient)
    glMaterialfv(GL_FRONT, GL_DIFFUSE,glfMatDiffuse)
    glMaterialfv(GL_FRONT,GL_SPECULAR,glfMatSpecular)
    glMaterialfv(GL_FRONT,GL_EMISSION,glfMatEmission)
    glMaterialfv(GL_FRONT,GL_SHININESS,fShininess)

"""视景体及模型"""
def drawScene():
    global ratio;global updown_angle;global rl_angle
    global trans_x;global trans_y
    global a;global b;global c

    m_fRatio=GLfloat(ratio)
    m_fAngle_updown=GLfloat(updown_angle)
    m_fAngle_rl=GLfloat(rl_angle)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    gluPerspective(30.0,1.0,1.0,100)
    glViewport(0,0,600,600)
    #glMatrixMode(GL_MODELVIEW)

    glfLight=GLfloat_4(-4.0,4.0,4.0,0.0)
    glLightfv(GL_LIGHT0,GL_POSITION,glfLight)

    gluLookAt(a,b,c,0,0,-1,0,1,0)

    glTranslatef(0.0,0.0,-5.0)
    glTranslatef(trans_x,0.0,0.0)
    glTranslatef(0.0,trans_y,0.0)
    glScalef(m_fRatio,m_fRatio,m_fRatio)
    glRotatef(30.0,1.0,0.0,0.0)
    glRotatef(m_fAngle_rl,0.0,1.0,0.0)
    glRotatef(m_fAngle_updown,1.0,0.0,0.0)

    drawTudi()
    draw()
    glutSwapBuffers()

"""鼠标按下时触发事件，记录初始鼠标坐标"""
def mouseButton(button, state, x, y):
    global startX;global startY
    if state == GLUT_DOWN:
        startX = x
        startY = y

"""鼠标移动的瞬间捕捉事件，根据鼠标移动位置改变视点角度"""
def mouseMotion(x, y):
    global startX;global startY;global trans_x;global trans_y
    trans_x = (x - startX)*0.01  # 左右平移量
    trans_y = -(y - startY)*0.01  #上下平移量

def keyMotion(key,x,y):
    global updown_angle;global rl_angle
    if key==GLUT_KEY_UP:
        updown_angle+=3
    elif key==GLUT_KEY_DOWN:
        updown_angle-=3
    elif key==GLUT_KEY_RIGHT:
        rl_angle+=3
    elif key==GLUT_KEY_LEFT:
        rl_angle-=3


"""鼠标滑轮改变缩放比控制远近"""
def  wheelMotion(button,dirt,x,y):
    global ratio
    if dirt>0 and ratio <2:
        ratio+=0.02
    elif dirt<0 and ratio>0 :
        ratio-=0.02

def keyButton(key,x,y):
    global a;global b;global c
    if key==b'a':
        a+=0.01
    elif key==b'd':
        a-=0.01
    elif key==b'w':
        c-=0.02
    elif key==b's':
        c+=0.02
    elif key==b'i':
        b+=0.01
    elif key==b'k':
        b-=0.01

"""创建地面"""
def drawTudi():
    MAX_COORD=300
    x_ambient=GLfloat_3(1.0,0.0,0.0)
    y_ambient = GLfloat_3(0.0, 1.0, 0.0)
    z_ambient = GLfloat_3(0.0, 0.0, 1.0)
    axis_ambient = GLfloat_3(1.0, 1.0, 1.0)
    other_ambient = GLfloat_3(1.0, 1.0, 1.0)
    glLineWidth(1.0)
    glBegin(GL_LINES)
    i=-MAX_COORD
    for i in range(-MAX_COORD,MAX_COORD+1):
        if i<2 and i>-2:
            pass
        else:
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, other_ambient)
            glVertex3i(MAX_COORD, 0, i)
            glVertex3i(-MAX_COORD, 0, i)
            glVertex3i(i, 0, MAX_COORD)
            glVertex3i(i, 0, -MAX_COORD)
            glVertex3i(MAX_COORD, i, 0)
            glVertex3i(-MAX_COORD, i, 0)

    glEnd()

ratio=1.0  #缩放比
trans_x=0.0;trans_y=0.0    #平移量
updown_angle=0.0;rl_angle=0.0  #旋转角度
a=0;b=0;c=0       #视点位置

f,v,vn,vt=readPic(0)  #obj对象参数
glutInit()
glutInitDisplayMode( GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH )
glutInitWindowPosition(0,0)
glutInitWindowSize(600, 600)
glutCreateWindow("Hello World")
initScene()
glutDisplayFunc(drawScene)
glutIdleFunc(drawScene)
glutMouseFunc(mouseButton)
glutMotionFunc(mouseMotion)
glutMouseWheelFunc(wheelMotion)
glutSpecialFunc(keyMotion)
glutKeyboardFunc(keyButton)

glutMainLoop()




"""旋转函数"""
"""
def rotateModel():
    global rotate_x;global rotate_y;global mat_rotate;global mat_saved
    init_mat(mat_saved);init_mat(mat_rotate)
    if rotate_y>0.01 or rotate_y<-0.01:
        matrix_rotate_y(mat_rotate,rotate_y)
        matrix_multi_f(mat_saved,mat_rotate)
        rotate_y=0
    init_mat(mat_rotate)
    if rotate_x>0.01 or rotate_x<-0.01:
        matrix_rotate_x(mat_rotate,rotate_x)
        matrix_multi_f(mat_saved,mat_rotate)
        rotate_x=0
    glMultMatrixf(mat_saved)

def matrix_rotate_x(mat,angle):
    radius=math.pi*angle/180.0
    mat[0]=1.0
    mat[15]=1.0
    mat[5]=math.cos(radius)
    mat[6]=-math.sin(radius)
    mat[9]=0-mat[6]
    mat[10]=mat[5]

def matrix_rotate_y(mat,angle):
    radius=math.pi*angle/180.0
    mat[5]=1.0
    mat[15]=1.0
    mat[0]=math.cos(radius)
    mat[8]=-math.sin(radius)
    mat[2]=0-mat[8]
    mat[10]=mat[0]

def matrix_multi_f(mat_ori,mat_mul):
    tmp=mat_ori.copy()
    for o_r in range(4):
        for m_c in range(4):
            for i in range(4):
                tmp[o_r*4+m_c]+=mat_ori[o_r*4+i]*mat_mul[i*4+m_c]
    for i in range(16):
        mat_ori[i]=tmp[i]
"""

