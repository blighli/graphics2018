from constants import *
from satellite import *

class Background:
    texID = -1

    def loadTex(self, path):
        back_image = pygame.image.load('res/' + path)
        back_image_data = pygame.image.tostring(back_image, "RGBX", 1)

        self.texID = glGenTextures(1)
        glBindTexture(GL_TEXTURE_2D, self.texID)

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, back_image.get_width(), back_image.get_height(), 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, back_image_data)

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)

    def draw(self, quadratic):
        glPushMatrix()
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.texID)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
        gluSphere(quadratic, VIEW_MAX, 64, 64)
        glDisable(GL_TEXTURE_2D) 
        glPopMatrix()
