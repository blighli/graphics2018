from constants import *
import math
import objloader as graphics
import numpy as np

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

last_time = 0
class objItem(object):
    
    def __init__(self):
        self.angle = 0
        self.vertices = []
        self.faces = []
        self.coordinates = [0, 0, -65]  # [x,y,z]
        self.teddy = graphics.ObjLoader("teddy.obj")
        self.position = [0, 0, -50]
    
    def render_scene(self):
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        #glClearColor(0.902, 0.902, 1, 0.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(0, 0, 0, math.sin(math.radians(self.angle)), 0, math.cos(math.radians(self.angle)) * -1, 0, 1, 0)
        glTranslatef(self.coordinates[0], self.coordinates[1], self.coordinates[2])

class Scene:
    cm_pos = [0.0, 0.0, 300.0]
    cm_cent = [0.0, 0.0, 0.0]
    cm_up = [0.0, 1.0, 0.0]
    lx, ly, lz = 0.0, 0.0, -30.0
    angleX, angleY = 0, 0

    #xview, yview, zview = 0.0, 0.0, 30.0
    xrot, yrot, zrot = 0.0, 0.0, 0.0
    xpos, ypos, zpos = 0.0, 0.0, 0.0
    day = 0.0
    stopFlag = True
    speed = 0.01
    infoTexID = 0

    objteddy = objItem()
    

    radius = 20.0
    phi = -10.0
    theta = 10.0
    ani_flag = False
    moving_ani = True
    ani_speed = 0.001
    def __init__(self):
        self.lx = np.sin(self.angleY)
        self.ly = np.sin(self.angleX)
        self.lz = -np.cos(self.angleX)
        return

    def resize(self, w, h):
        if h == 0:
            h = 1
        glViewport(0, 0, w, h)

    def init(self):
        glEnable(GL_TEXTURE_2D)
#
        glShadeModel(GL_SMOOTH)
        glClearColor(1.0, 1.0, 1.0, 0.0)
        glClearDepth(1.0)
        glEnable(GL_DEPTH_TEST)
        glDepthFunc(GL_LEQUAL)
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)


        # Add light
        light_ambient =  [0.0, 0.0, 0.0, 1.0]
        light_diffuse =  [1.0, 1.0, 1.0, 1.0]
        light_specular =  [1.0, 1.0, 1.0, 1.0]
        light_position =  [1.0, 1.0, 1.0, 0.0]

        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse)
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular)
        glLightfv(GL_LIGHT0, GL_POSITION, light_position)

        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glEnable(GL_DEPTH_TEST)




    def draw(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(45, 1.0*WIN_SIZE_W/WIN_SIZE_H, 0.5, 300.0)
        gluLookAt(self.cm_pos[0], self.cm_pos[1], self.cm_pos[2],
                  self.cm_pos[0] + self.lx, self.cm_pos[1] + self.ly, self.cm_pos[2] + self.lz,
                  self.cm_up[0], self.cm_up[1], self.cm_up[2])
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

        # stop moving
        if self.stopFlag == True:
            self.day = self.day + self.speed
            # if self.day > 365:
            #     self.day = 0.0

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        glTranslatef(self.xpos, self.ypos, self.xpos)

        #self.draw_info()

        glPushMatrix()

        glTranslatef(0.0,0.0,0.0)
        #glColor3f(1.0,0.0,0.0)
        glRotatef(self.xrot,1.0,0.0,0.0)
        glRotatef(self.yrot,0.0,1.0,0.0)
        glRotatef(self.zrot,0.0,0.0,1.0)

        self.objteddy.teddy.render_scene()



        glPopMatrix()

    def set_obj_rotation(self, x, y, z):
        self.xrot = x
        self.yrot = y
        self.zrot = z

    def set_view_rotation(self, x, y, z):
        self.cm_pos[0] = x
        self.cm_pos[1] = y
        self.cm_pos[2] = z

    def set_ani_value(self):
        if self.moving_ani == True:
            self.cm_pos[0] += self.lx * self.ani_speed
            self.cm_pos[2] += self.lz * self.ani_speed
            self.ani_speed += ACCEL
            if self.ani_speed >= 0.5:
                self.ani_speed = 0.5
        elif self.moving_ani == False and self.ani_flag == True:
            self.xrot -= 0.1

        if self.moving_ani == True:
            if self.cm_pos[2] <= 30.0:
                self.moving_ani = False
        else:
            if self.xrot <= -60:
                self.ani_flag = False

    def set_ani_flag(self, b):
        self.ani_flag = b
    def get_ani_end_flag(self):
        return self.ani_flag

    def draw_orbit(self, obj):
        if obj.polygon_setted == False:
            obj.set_orbit_poly()
        return obj.draw_orbit()
