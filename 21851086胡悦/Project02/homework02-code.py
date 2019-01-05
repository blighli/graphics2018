from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from PIL import Image
import math
import time

wide = 800
height = 600
size = 10
day = 0
mercuryYear = 0
venusYear = 0
year = 0
marsYear = 0
jupiterYear = 0
saturnYear = 0
uranusYear = 0
neptuneYear = 0
g_text = gluNewQuadric()
star = [[0 for i in range(3)] for i in range(2000)]

# light_angle = 0.0
# light_radius = 8.0
cam_radius = 7.0
cam_radius1 = 0.0
cam_position = [0 for i in range(3)]
cam_angle_u = 0.3
cam_angle_v = 0.3
state = 1
BUFSIZE = 512
selectBuff = (GLuint * BUFSIZE)()

isSelected = [False for x in range(9)]


def init():
    global g_text, sun_texture, mercury_texture, venus_texture, earth_texture, moon_texture, mars_texture, jupiter_texture, saturn_texture, uranus_texture, neptune_texture, background_texture
    global suninfo, mercuryinfo, venusinfo, earthinfo, marsinfo, jupiterinfo, saturninfo, uranusinfo, neptuneinfo
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glShadeModel(GL_SMOOTH)  # 选择平面明暗模式或光滑明暗模式
    glEnable(GL_LIGHT0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_TEXTURE_2D)
    g_text = gluNewQuadric()
    sun_texture = load_texture("./texture/sun.bmp")
    mercury_texture = load_texture("./texture/mercury.bmp")
    venus_texture = load_texture("./texture/venus.jpg")
    earth_texture = load_texture("./texture/earth.jpg")
    moon_texture = load_texture("./texture/moon.bmp")
    mars_texture = load_texture("./texture/mars.jpg")
    jupiter_texture = load_texture("./texture/jupiter.bmp")
    saturn_texture = load_texture("./texture/saturn.jpg")
    uranus_texture = load_texture("./texture/uranus.jpg")
    neptune_texture = load_texture("./texture/neptune.jpg")
    suninfo = load_texture("./information/suninfo.jpg")
    mercuryinfo = load_texture("./information/mercuryinfo.jpg")
    venusinfo = load_texture("./information/venusinfo.jpg")
    earthinfo = load_texture("./information/earthinfo.jpg")
    marsinfo = load_texture("./information/marsinfo.jpg")
    jupiterinfo = load_texture("./information/jupiterinfo.jpg")
    saturninfo = load_texture("./information/saturninfo.jpg")
    uranusinfo = load_texture("./information/uranusinfo.jpg")
    neptuneinfo = load_texture("./information/neptuneinfo.jpg")


def reshape(w, h):
    glViewport(0, 0, GLsizei(w), GLsizei(h))  # 改变显示区域，起始位置为客户端窗口左下角（非坐标原点
    glMatrixMode(GL_PROJECTION)  # 修改投影矩阵
    glLoadIdentity()  # 用指定的矩阵替换当前矩阵
    gluPerspective(60.0, float(w) / float(h), 1.0, 20)  # 宽高比改为当前值，视线区域与屏幕大小一致；
    glMatrixMode(GL_MODELVIEW)  # 指定矩阵为当前矩阵
    cPosition()  # cam position


def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    # glRotatef(1,1,1,1)
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR)
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR)
    glEnable(GL_TEXTURE_GEN_S)
    glEnable(GL_TEXTURE_GEN_T)
    glEnable(GL_TEXTURE_2D)
    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    drawSun()
    drawMercury()
    drawVenus()
    drawEarth()
    drawMars()
    drawJupiter()
    drawSaturn()
    drawUranus()
    drawNeptune()
    rotate()
    drawinfo()
    glPopMatrix()
    glDisable(GL_TEXTURE_2D)
    glutSwapBuffers()  # 双缓冲(解决了频繁刷新导致的画面闪烁问题
    glFlush()  # 刷新窗口以显示当前绘制图形


def load_texture(filename):
    image = Image.open(filename)
    ix = image.size[0]
    iy = image.size[1]
    image = image.tobytes("raw", "RGBX", 0, -1)
    # Create Texture
    texture = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texture)  # 2d texture (x and y size)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image)
    # set the texture's minification properties (mapping textures to bigger areas)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    # set the texture's stretching properties (mapping textures to smaller areas)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
    return texture


def drawSun():
    glPushMatrix()
    glPushName(1)
    glBindTexture(GL_TEXTURE_2D, sun_texture)
    gluSphere(g_text, 0.6, 32, 32)
    glPopName()
    glPopMatrix()


def drawMercury():
    glPushMatrix()
    glPushName(2)
    glBindTexture(GL_TEXTURE_2D, mercury_texture)
    glRotatef(float(mercuryYear), 0.0, 0.0, 1.0)  # year为旋转角度，绕z轴旋转
    glTranslatef(0.8, 0.0, 0.0)  # 距离中心x方向偏离0.8 即半径
    glRotatef(float(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.13, 20, 16)  # 二次曲面，球体半径
    glPopName()
    glPopMatrix()
    drawOrbit(0.8)


def drawVenus():
    glPushMatrix()
    glPushName(3)
    glBindTexture(GL_TEXTURE_2D, venus_texture)
    glRotatef(GLfloat(venusYear), 0.0, 0.0, 1.0)
    glTranslatef(1.3, 0.0, 0.0)
    glRotatef(float(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.2, 20, 16)  # draw smaller planet
    glPopName()
    glPopMatrix()
    drawOrbit(1.3)


def drawMoon():
    glPushMatrix()
    glPushName(10)
    glBindTexture(GL_TEXTURE_2D, moon_texture)
    glRotatef(GLfloat(year), 0.0, 0.0, 1.0)
    glTranslatef(0.3, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.05, 20, 16)
    glPopName()
    glPopMatrix()
    drawOrbit(0.3)


def drawEarth():
    glPushMatrix()
    glPushName(4)
    glBindTexture(GL_TEXTURE_2D, earth_texture)
    glRotatef(GLfloat(year), 0.0, 0.0, 1.0)
    glTranslatef(1.8, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.16, 20, 16)
    glPopName()
    drawMoon()
    glPopMatrix()
    drawOrbit(1.8)


def drawMars():
    glPushMatrix()
    glPushName(5)
    glBindTexture(GL_TEXTURE_2D, mars_texture)
    glRotatef(GLfloat(marsYear), 0.0, 0.0, 1.0)
    glTranslatef(2.2, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.14, 20, 16)
    glPopName()
    glPopMatrix()
    drawOrbit(2.2)


def drawJupiter():
    glPushMatrix()
    glPushName(6)
    glBindTexture(GL_TEXTURE_2D, mars_texture)
    glRotatef(GLfloat(jupiterYear), 0.0, 0.0, 1.0)
    glTranslatef(2.7, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.22, 20, 16)
    glPopName()
    glPopMatrix()
    drawOrbit(2.7)


def park():
    glBegin(GL_TRIANGLE_FAN)
    glVertex3f(0, 0, 0)
    for i in range(0, 380, 20):
        p = float(i*3.14/180)
        glVertex3f(float(math.sin(p) * 0.22), float(math.cos(p) * 0.22), 0.0)
    glEnd()


def drawSaturn():
    glPushMatrix()
    glPushName(7)
    glBindTexture(GL_TEXTURE_2D, saturn_texture)
    glRotatef(GLfloat(saturnYear), 0.0, 0.0, 1.0)
    glTranslatef(3.15, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.14, 20, 16)
    glRotatef(0.2, 1.0, 0.0, 0.0)
    park()
    glPopName()
    glPopMatrix()
    drawOrbit(3.15)


def drawUranus():
    glPushMatrix()
    glPushName(8)
    glBindTexture(GL_TEXTURE_2D, uranus_texture)
    glRotatef(GLfloat(uranusYear), 0.0, 0.0, 1.0)
    glTranslatef(3.55, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.12, 20, 16)
    glPopName()
    glPopMatrix()
    drawOrbit(3.55)


def drawNeptune():
    glPushMatrix()
    glPushName(9)
    glBindTexture(GL_TEXTURE_2D, neptune_texture)
    glRotatef(GLfloat(jupiterYear), 0.0, 0.0, 1.0)
    glTranslatef(3.8, 0.0, 0.0)
    glRotatef(GLfloat(day), 0.0, 0.0, 1.0)
    gluSphere(g_text, 0.10, 20, 16)
    glPopName()
    glPopMatrix()
    drawOrbit(3.8)


def rotate():
    global day, mercuryYear, venusYear, year, marsYear, jupiterYear, saturnYear, uranusYear, neptuneYear
    mercuryYear += 3
    if mercuryYear >= 360:
        mercuryYear -= 360
    venusYear += 2
    if venusYear >= 360:
        venusYear -= 360
    year += 1.0
    if year >= 360:
        year -= 360
    marsYear += 0.8
    if marsYear >= 360:
        marsYear -= 360
    jupiterYear += 0.3
    if jupiterYear >= 360:
        jupiterYear -= 360
    saturnYear += 0.2
    if saturnYear >= 360:
        saturnYear -= 360
    uranusYear += 0.05
    if uranusYear >= 360:
        uranusYear -= 360
    neptuneYear += 0.01
    if neptuneYear >= 360:
        neptuneYear -= 360
    glutPostRedisplay()


def drawOrbit(radius):
    glBegin(GL_LINE_STRIP)
    for i in range(100):
        glVertex2f(radius * math.cos(2 * math.pi / 100 * i),
                   radius * math.sin(2 * math.pi / 100 * i))
    glEnd()


def cPosition():
    cam_radius1 = cam_radius*math.cos(cam_angle_v)
    cam_position[0] = cam_radius1*math.cos(cam_angle_u)
    cam_position[1] = cam_radius1*math.sin(cam_angle_u)
    cam_position[2] = cam_radius*math.sin(cam_angle_v)
    glLoadIdentity()
    gluLookAt(cam_position[0], cam_position[1],
              cam_position[2], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)  # 观察者位置
    # eyex, eyey,eyez 相机在世界坐标的位置
    # centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
    # upx,upy,upz 相机向上的方向在世界坐标中的方向


def select(button, state, x, y):
    if button != GLUT_LEFT_BUTTON or state != GLUT_DOWN:
        return
    viewport = (GLint * 4)()  # 视口
    glSelectBuffer(BUFSIZE, selectBuff)  # 为选项模式值建立一个缓冲区;
    glGetIntegerv(GL_VIEWPORT, viewport)  # 返回一个选中参数的值
    glMatrixMode(GL_PROJECTION)  # 点击矩阵 在projection模式下
    glInitNames()  # 初始化名字栈
    glPushMatrix()
    glRenderMode(GL_SELECT)  # 进入选择模式
    glLoadIdentity()  # 用指定的矩阵替换当前矩阵
    gluPickMatrix(x, viewport[3]-y+viewport[1], 10,
                  10, viewport)  # 定义一个拾取区域 10*10为拾取框大小
    gluPerspective(60.0, float(wide) / float(height), 1.0, 10)  # 设置透视投影矩阵
    glMatrixMode(GL_MODELVIEW)  # 绘制 在modelview模式下
    draw()  # 绘制
    glMatrixMode(GL_PROJECTION)  # 点击矩阵 在projection模式下
    glPopMatrix()
    glMatrixMode(GL_MODELVIEW)  # 会到初始modeleview模式
    hits = glRenderMode(GL_RENDER)  # 确定选择模式下的命中次数
    if hits:
        process(selectBuff[3])
    else:
        print("Please click on the sun or planets!")
        for i in range(len(isSelected)):
            isSelected[i] = False
    glutPostRedisplay()
    # glutPostRedisplay 标记当前窗口需要重新绘制。
    # 通过glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板。
    # 多次调用glutPostRedisplay，在下一个显示回调只产生单一的重新显示回调


def process(id):
    muteOthers(id)
    if id == 1:
        print("You clicked on the Sun!")
    elif id == 2:
        print("You clicked on Mercury!")
    elif id == 3:
        print("You clicked on Venus!")
    elif id == 4:
        print("You clicked on Earth!")
    elif id == 5:
        print("You clicked on Mars!")
    elif id == 6:
        print("You clicked on Jupiter!")
    elif id == 7:
        print("You clicked on Saturn!")
    elif id == 8:
        print("You clicked on Uranus!")
    elif id == 9:
        print("You clicked on Neptune!")
    else:
        print("Nothing was clicked on!")


def muteOthers(id):
    global isSelected
    for i in range(len(isSelected)):
        isSelected[i] = False
    isSelected[id - 1] = True


def drawinfo():
    if isSelected[0]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, suninfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[1]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, mercuryinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[2]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, venusinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[3]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, earthinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[4]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, marsinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[5]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, jupiterinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[6]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, saturninfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[7]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, uranusinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()
    if isSelected[8]:
        glPushMatrix()
        glLoadIdentity()
        glBindTexture(GL_TEXTURE_2D, neptuneinfo)
        glTranslatef(-2.8, 1.5, 0)
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        glRectf(0, 0, 1, 1)
        glPopMatrix()


def orbitL():
    global day, mercuryYear, venusYear, year, marsYear, jupiterYear, saturnYear, uranusYear, neptuneYear
    mercuryYear = (mercuryYear+12) % 360
    venusYear = (venusYear+20) % 360
    year = (year + 8) % 360
    marsYear = (marsYear+6) % 360
    jupiterYear = (jupiterYear+5) % 360
    saturnYear = (saturnYear+4) % 360
    uranusYear = (uranusYear+3) % 360
    neptuneYear = (neptuneYear+1) % 360
    day = (day+30) % 360


def orbitR():
    global day, mercuryYear, venusYear, year, marsYear, jupiterYear, saturnYear, uranusYear, neptuneYear
    mercuryYear = (mercuryYear-12) % 360
    venusYear = (venusYear-20) % 360
    year = (year - 8) % 360
    marsYear = (marsYear-6) % 360
    jupiterYear = (jupiterYear-5) % 360
    saturnYear = (saturnYear-4) % 360
    uranusYear = (uranusYear-3) % 360
    neptuneYear = (neptuneYear-1) % 360
    day = (day-30) % 360


def keyboard(key, x, y):
    global day, year, light_angle, cam_radius, cam_angle_v, cam_angle_u, camera_position
    if key == b'k':
        cam_radius += 0.2
        cPosition()
        glutPostRedisplay()
        return
    elif key == b'K':
        cam_radius -= 0.2
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'w':
        cam_angle_v += 1.0/30
        if cam_angle_v > 1.0:
            cam_angle_v = 1.0
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b's':
        cam_angle_v -= 1.0/30
        if cam_angle_v < -1.0:
            cam_angle_v = -1.0
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'a':
        cam_angle_u += 1.0/30
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'd':
        cam_angle_u -= 1.0/30
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'r':
        cam_radius = 5.0
        cam_angle_u = 0
        cam_angle_v = 0
        cPosition()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'q':
        orbitL()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    elif key == b'Q':
        orbitR()
        glutPostRedisplay()
        time.sleep(0.1)
        return
    else:
        time.sleep(0.1)
        return


def myidle():  # rotation
    global day
    day += 1
    if day >= 360:
        day = day-360
    glutPostRedisplay()


def myTimer():
    draw()
    glutTimerFunc(20, myTimer, 1)


def main():
    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(wide, height)
    glutCreateWindow("21851086-huyue-homework02")
    init()
    glutDisplayFunc(draw)
    glutReshapeFunc(reshape)
    glutMouseFunc(select)
    glutKeyboardFunc(keyboard)
    glutIdleFunc(myidle)
    glutMainLoop()


if __name__ == "__main__":
    main()
