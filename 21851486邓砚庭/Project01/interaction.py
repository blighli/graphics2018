
__author__ = 'Dante'

import sys
import math

from interactionMatrix import InteractionMatrix

try:
    from OpenGL.GLUT import *
    from OpenGL.GLU import *
    from OpenGL.GL import *
    from OpenGL._bytes import as_8_bit
except:
    print('PyOpenGL not found!')
    sys.exit()

class Interactor(object):
    '''Mouse and Keyboard Interaction'''
    def __init__(self, translationScale=0.1, rotationScale=.2):
        self.scalingFactorRotation = rotationScale
        self.scalingFactorTranslation = translationScale
        self.rotationMatrix = InteractionMatrix()
        self.translationMatrix = InteractionMatrix()
        self.mouseButtonPressed = None
        self.oldMousePos = [0, 0]

    def mouseButton(self, button, mode, x, y):
        if mode == GLUT_DOWN:
            self.mouseButtonPressed = button
        else:
            self.mouseButtonPressed = None
        self.oldMousePos[0], self.oldMousePos[1] = x, y
        glutPostRedisplay()

    def mouseMotion(self, x, y):
        oldX = x - self.oldMousePos[0]
        oldY = y - self.oldMousePos[1]
        if self.mouseButtonPressed == GLUT_RIGHT_BUTTON:
            tX = oldX * self.scalingFactorTranslation
            tY = oldY * self.scalingFactorTranslation
            self.translationMatrix.addTranslation(tX, -tY, 0)
        elif self.mouseButtonPressed == GLUT_LEFT_BUTTON:
            rY = oldX * self.scalingFactorRotation
            self.rotationMatrix.addRotation(rY, 0, 1, 0)
            rX = oldY * self.scalingFactorRotation
            self.rotationMatrix.addRotation(rX, 1, 0, 0)
        else:
            tZ = oldY * self.scalingFactorTranslation
            self.translationMatrix.addTranslation(0, 0, tZ)
        self.oldMousePos[0], self.oldMousePos[1] = x, y
        glutPostRedisplay()

    def applyTransformation(self):
        glMultMatrixf(self.translationMatrix.getCurrentMatrix())
        glMultMatrixf(self.rotationMatrix.getCurrentMatrix())

    def keyPressed(self, *args):
        # If ESC pressed
        if args[0] == as_8_bit('\033'):
            sys.exit()

    def registerCallbacks(self):
        glutMouseFunc(self.mouseButton)
        glutMotionFunc(self.mouseMotion)
        glutKeyboardFunc(self.keyPressed)
