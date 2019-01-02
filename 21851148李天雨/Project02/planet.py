from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import numpy as np
import pygame
import constants

class Planet:
    name = 'None'
    texID = -1
    radius = -1
    rot_period = 0
    posX, posY, posZ = 0.0, 0.0, 0.0
    rotX, rotY, rotZ = 0.0, 0.0, 0.0
    center = []
    p, a, e, i, w = 0, 0, 0, 0, 0
    polygon_setted = False
    orbit_poly = []
    orbit_color = 0
    def __init__(self, name):
        self.name = name
        color_id = np.random.randint(len(constants.COLOR_TABLE))
        self.orbit_color = constants.COLOR_TABLE[color_id]
        return

    def init(self):
        return

    def set_factor_orbit(self, center, period, day, a, e, i, w):
        self.center = center
        self.p, self.a, self.e, self.i, self.w = period, a, e, i, w
        coord = self.calc_coord(center, period, day, a, e, i, w)
        self.posX = coord[0]
        self.posY = coord[1]

    def get_coord(self):
        coord = [self.posX, self.posY, self.posZ]
        return coord

    def set_rotation_period(self, p):
        self.rot_period = p
        self.set_rotation(0.0, 0.0, self.rotZ + p)

    def set_rotation(self, x, y, z):
        self.rotX = x
        self.rotY = y
        self.rotZ = z

    def set_radius(self, r):
        self.radius = r

    def loadTex(self, path):
        tex_surface = pygame.image.load('res/' + path)
        tex_data = pygame.image.tostring(tex_surface, "RGBX", 1)

        self.texID = glGenTextures(1)
        glBindTexture(GL_TEXTURE_2D, self.texID)

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex_surface.get_width(), tex_surface.get_height(), 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, tex_data)

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)

    def draw(self, quadratic, draw_func=None):

        glPushMatrix()
        glTranslatef(self.posX, self.posY, self.posZ)
        glColor3f(1.0,0.0,0.0)
        glRotatef(self.rotX,  1.0,  0.0,  0.0)            # Rotate The Cube On It's X Axis
        glRotatef(self.rotY,  0.0,  1.0,  0.0)            # Rotate The Cube On It's Y Axis
        glRotatef(self.rotZ, 0.0, 0.0, 1.0)            # Rotate The Cube On It's Z Axis

        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.texID)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
        gluSphere(quadratic, self.radius, 128, 128)
        glDisable(GL_TEXTURE_2D) 
        glPopMatrix()

        if draw_func is not None:
            draw_func(quadratic)

    def calc_coord(self, transCoord, p, d, a, e, i, w):

        unitAng = 360/p
        ang = (unitAng * d) % 360
        theta = np.deg2rad(ang)
        b = a * np.sqrt(1 - np.power(e, 2))
        x = transCoord[0] + a * np.cos(theta)
        y = transCoord[1] + b * np.sin(theta)
        z = 0.0

        #rotate
        w = np.deg2rad(w)
        x1, y1 = x, y
        #x = transCoord[0] + (x1 * np.cos(w) - y1 * np.sin(w))
        #y = transCoord[1] + (x1 * np.sin(w) + y1 * np.cos(w))

        coord = [x, y, z]
        return coord

    def set_orbit_poly(self):
        polygon = []
        fraction = self.p / 360
        for i in range(0, 360):
            polygon.append(self.calc_coord([0,0,0], self.p, i*fraction, self.a, self.e, self.i, self.w))
        self.orbit_poly = polygon
        self.polygon_setted = True

    def draw_orbit(self):

        glPushMatrix()
        glTranslatef(self.center[0], self.center[1], self.center[2])
        glColor3f(self.orbit_color[0], self.orbit_color[1], self.orbit_color[2])
        glDisable(GL_LIGHTING)
        glBindTexture(GL_TEXTURE_2D, self.texID)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
        glLineWidth(1.0)
        glBegin(GL_LINE_LOOP)
        for i in range(0, 360):
            glVertex3f(self.orbit_poly[i][0], self.orbit_poly[i][1], self.orbit_poly[i][2])
        glEnd()
        glEnable(GL_LIGHTING)
        glPopMatrix()
