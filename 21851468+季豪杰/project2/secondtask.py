from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

WIDTH = 400
HEIGHT = 400
ANGLE = 0.0

def myDisplay():
    global ANGLE
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    sun_light_positon = [0.0,0.0,0.0,1.0]
    sun_light_ambient = [0.0,0.0,0.0,1.0]
    sun_light_diffuse = [1.0,1.0,1.0,1.0]
    sun_light_specular = [1.0,1.0,1.0,1.0]

    glLightfv(GL_LIGHT0,GL_POSITION,sun_light_positon)
    glLightfv(GL_LIGHT0,GL_AMBIENT,sun_light_ambient)
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sun_light_diffuse)
    glLightfv(GL_LIGHT0,GL_SPECULAR,sun_light_specular)

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    sun_mat_ambient = [0.0, 0.0, 0.0, 1.0];
    sun_mat_diffuse = [0.0, 0.0, 0.0, 1.0];
    sun_mat_specular = [0.0, 0.0, 0.0, 1.0];
    sun_mat_emission = [0.5, 0.0, 0.0, 1.0];
    sun_mat_shininess = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
    glutSolidSphere(2.0, 40, 32);


    earth_mat_ambient = [0.0, 0.0, 0.5, 1.0];
    earth_mat_diffuse = [0.0, 0.0, 0.5, 1.0];
    earth_mat_specular = [0.0, 0.0, 1.0, 1.0];
    earth_mat_emission= [0.0, 0.0, 0.0, 1.0];
    earth_mat_shininess = 30.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
    glRotatef(ANGLE, 0.0, -1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0);
    glutSolidSphere(2.0, 40, 32);

    glutSwapBuffers();

def myIdle():
    global ANGLE
    ANGLE += 1.0;
    if (ANGLE >= 360.0):
        ANGLE = 0.0;
    myDisplay();

glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
glutInitWindowSize(800, 800)
glutCreateWindow("firstWork")
# glutMouseFunc(mouseCB);
#glutMouseWheelFunc(wheelMotion)
# glutMotionFunc(mouseMotionCB);
glutDisplayFunc(myDisplay)
glutIdleFunc(myIdle)
glutMainLoop()
