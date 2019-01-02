from background import *

last_time = 0
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
    quadratic = gluNewQuadric()
    background = Background()
    earth = Planet('earth')
    sun = Planet('sun')
    moon = Satellite('moon')
    jupiter = Planet('jupiter')

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
        # Create a quadratic object for sphere rendering
        #quadratic = gluNewQuadric()
        #gluQuadricDrawStyle( quadratic, GLU_FILL )
        #gluQuadricDrawStyle( quadratic, GLU_LINE )
        #gluQuadricDrawStyle( quadratic, GLU_SILHOUETTE )
        gluQuadricNormals(self.quadratic, GLU_SMOOTH)
        gluQuadricTexture(self.quadratic, GL_TRUE)
        glEnable(GL_TEXTURE_2D)

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


    def loadTex(self):

        self.sun.loadTex('Sun.bmp')
        self.earth.loadTex('Earth.bmp')
        self.moon.loadTex('Moon.bmp')
        self.jupiter.loadTex('Jupiter.jpg')
        self.background.loadTex('stars_milkyway.jpg')
        #self.loadInfoTex()

    def loadInfoTex(self):
        font = pygame.font.Font(None, 64)
        textureSurface = font.render("the Sun", True, (255,255,0,255))
        textureData = pygame.image.tostring(textureSurface, "RGBX", True)

        self.infoTexID = glGenTextures(1)
        glBindTexture(GL_TEXTURE_2D, self.infoTexID)

        #glPixelStorei(GL_UNPACK_ALIGNMENT,1)
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureSurface.get_width(), textureSurface.get_height(), 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, textureData)

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
        #glDisable(GL_TEXTURE_2D)

    def draw_info(self):

        glPushMatrix()
        glDisable(GL_LIGHTING)

        glColor4f(1, 0, 0, 1)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glEnable(GL_BLEND)
        glEnable(GL_CULL_FACE)
        glTranslatef(5, 5, 10)
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.infoTexID)

        glBegin(GL_QUADS)
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0,  1.0)
        glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0,  1.0)
        glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0,  1.0)
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0,  1.0)
        glEnd()

        glDisable(GL_BLEND)
        glDisable(GL_CULL_FACE)
        glEnable(GL_LIGHTING)
        glPopMatrix()

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
        glColor3f(1.0,0.0,0.0)
        glRotatef(self.xrot,1.0,0.0,0.0)
        glRotatef(self.yrot,0.0,1.0,0.0)
        glRotatef(self.zrot,0.0,0.0,1.0)

    #    glPushMatrix()
    #    glDisable(GL_LIGHTING)
        #y axis
    #    glLineWidth(3.0)
    #    glColor3f(0.0,1.0,0.0)
    #    glBegin(GL_LINE_STRIP)
    #    glVertex3f(0.0, 0.0, 0.0)
    #    glVertex3f(0.0, 50.0, 0.0)
    #    glEnd()

        #x axis
    #    glColor3f(1.0,0.0,0.0)
    #    glBegin(GL_LINE_STRIP)
    #    glVertex3f(0.0, 0.0, 0.0)
    #    glVertex3f(50.0, 0.0, 0.0)
    #    glEnd()

        #z axis
    #    glColor3f(0.0,0.0,1.0)
    #    glBegin(GL_LINE_STRIP)
    #    glVertex3f(0.0, 0.0, 0.0)
    #    glVertex3f(0.0, 0.0, 50.0)
    #    glEnd()
    #    glEnable(GL_LIGHTING)
    #    glPopMatrix()

        self.background.draw(self.quadratic)
        sun_coord = [0.0, 0.0, 0.0]
        # sun
        self.sun.set_rotation_period(0.008)
        self.sun.set_radius(1.5)
        self.sun.draw(self.quadratic)

        # earth
        self.earth.set_factor_orbit(sun_coord, 365, self.day, 6, 0.5, 0.0, 70)
        self.earth.set_rotation_period(0.01)
        self.earth.set_radius(0.25)

        # earth has a satellite : moon
        earth_coord = self.earth.get_coord()
        self.moon.set_factor_orbit(earth_coord, 30, self.day, 1.5, 0.3, 0.0, 70)
        self.moon.set_rotation_period(0.03)
        self.moon.set_radius(0.1)
        self.earth.draw(self.quadratic, self.moon.draw)
        self.draw_orbit(self.earth)
        self.draw_orbit(self.moon)

        self.jupiter.set_factor_orbit(sun_coord, 1200, self.day, 10, 0.5, 0.0, 70)
        self.jupiter.set_rotation_period(0.02)
        self.jupiter.set_radius(0.5)
        self.jupiter.draw(self.quadratic)
        self.draw_orbit(self.jupiter)

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
