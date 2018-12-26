
__author__ = 'Dante'

import sys

try:
  from OpenGL.GLUT import *
  from OpenGL.GL import *
  from OpenGL.GLU import *
except:
  print('PyOpenGL not found.')
  sys.exit()

class InteractionMatrix(object):

    def __init__(self):
        self.__currentMatrix = None
        self.reset()

    def reset(self):
        """Initialise internal matrix with identity"""
        glPushMatrix()
        glLoadIdentity()
        self.__currentMatrix = glGetFloatv(GL_MODELVIEW_MATRIX)
        glPopMatrix()

    def addTranslation(self, tx, ty, tz):
        """Concatenate the internal matrix with a translation matrix"""
        glPushMatrix()
        glLoadIdentity()
        glTranslatef(tx, ty, tz)
        glMultMatrixf(self.__currentMatrix)
        self.__currentMatrix = glGetFloatv(GL_MODELVIEW_MATRIX)
        glPopMatrix()

    def addRotation(self, ang, rx, ry, rz):
        """Concatenate the internal matrix with a translation matrix"""
        glPushMatrix()
        glLoadIdentity()
        glRotatef(ang, rx, ry, rz)
        glMultMatrixf(self.__currentMatrix)
        self.__currentMatrix = glGetFloatv(GL_MODELVIEW_MATRIX)
        glPopMatrix()

    def getCurrentMatrix(self):
        return self.__currentMatrix
