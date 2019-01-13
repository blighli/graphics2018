from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math

from objloader import *


class ModelRenderer(object):

    def __init__(self):
        self.angle = 0
        self.vertices = []
        self.faces = []
        self.camDist = [0, 0, 0]
        self.camAngle = [.0, .0]
        self.eye = [.0, .0, 5.0]
        self.center = [.0, .0, .0]
        self.scale = 1.0
        self.model = ObjLoader("../model/monkey.obj")

    def render_scene(self):
        glColor3f(1.0, 1.0, 1.0)
        glClearColor(0, 0, 0, 0)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(self.eye[0], self.eye[1], self.eye[2],
                  self.center[0], self.center[1], self.center[2],
                  0, 1, 0)

        glPushMatrix()
        glScalef(self.scale, self.scale, self.scale)
        glTranslatef(self.camDist[0], self.camDist[1], self.camDist[2])
        glRotatef(self.camAngle[0], 1, 0, 0)
        glRotatef(self.camAngle[1], 0, 1, 0)
        self.model.render_scene()
        glPopMatrix()

        glutSwapBuffers()

    def move_up(self, amount):
        self.eye[1] += amount
        self.center[1] += amount

    def move_forward(self, amount):
        self.eye[2] += amount
        self.center[2] += amount

    def move_right(self, amount):
        self.eye[0] += amount
        self.center[0] += amount

    def scaleAll(self, amount):
        self.scale += amount

    def reset(self):
        self.camDist = [0, 0, 0]
        self.camAngle = [.0, .0]
        self.eye = [.0, .0, 5.0]
        self.center = [.0, .0, .0]
        self.scale = 1.0
