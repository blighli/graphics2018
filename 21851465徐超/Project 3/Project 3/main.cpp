//
//  main.cpp
//  Project 3
//
//  Created by 祈越 on 2019/1/3.
//  Copyright © 2019 QiyueX. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

static int angelWithX = 30;
static int originX = -1;
static int originY = -1;
static float viewPointDistance = 300;
static float viewPointHeight = 300;
static float angelToRadius = 3.1415926535 / 180.0;
static float lookAtX = -20;
static float lookAtY = -150;
static float lookAtZ = 160;

class obj2model {
    struct vertex {
        double x, y, z;
    };
    struct face {
        unsigned int v1, v2, v3;
    };
    std::vector<vertex> vertexs;
    std::vector<face> faces;
    
    public :
    
    void parse(const char *fileName);
    void draw();
};

void obj2model::parse(const char *fileName) {
    std::string line;
    std::ifstream file(fileName);
    if (!file) {
        return;
    }
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "vt") {
            continue;
        } else if (line.substr(0, 2) == "vn") {
            continue;
        } else if (line.substr(0, 1) == "v") {
            vertex v;
            std::istringstream s(line.substr(2));
            s >> v.x;
            s >> v.y;
            s >> v.z;
            vertexs.push_back(v);
        } else if (line.substr(0, 1) == "f") {
            face f;
            std::istringstream s(line.substr(2));
            s >> f.v1;
            std::string eatString;
            s >> eatString;
            s >> f.v2;
            s >> eatString;
            s >> f.v3;
            faces.push_back(f);
        }
    }
    file.close();
}

void obj2model::draw() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        GLint firstVertexIndex = faces[i].v1 - 1;
        GLint secondVertexIndex = faces[i].v2 - 1;
        GLint thirdVertexIndex = faces[i].v3 - 1;
        glVertex3f(vertexs[firstVertexIndex].x, vertexs[firstVertexIndex].y, vertexs[firstVertexIndex].z);
        glVertex3f(vertexs[secondVertexIndex].x, vertexs[secondVertexIndex].y, vertexs[secondVertexIndex].z);
        glVertex3f(vertexs[thirdVertexIndex].x, vertexs[thirdVertexIndex].y, vertexs[thirdVertexIndex].z);
    }
    glEnd();
}

obj2model obj;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
    glutReshapeWindow(600, 600);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    glEnable(GL_LIGHTING);
    
    GLfloat light0Pos[] = {0.0, 0.0, 600.0, 1.0};
    GLfloat ambientLight0[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuseLight0[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat specularLight0[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
    glEnable(GL_LIGHT0);
    
    GLfloat light1Pos[] = {0.0, 500.0, 500.0, 1.0};
    GLfloat ambientLight1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuseLight1[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat specularLight1[] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
    glEnable(GL_LIGHT1);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat specref[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 10);
    
    obj.draw();
    
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (viewPointHeight <= 400) {
                viewPointHeight += 50;
            }
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        case 's':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (viewPointHeight >= -400) {
                viewPointHeight -= 50;
            }
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        case 'a':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            lookAtX -= 10;
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        case 'd':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            lookAtX += 10;
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        case 'q':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            lookAtZ -= 10;
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        case 'e':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            lookAtZ += 10;
            gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        originX = x;
        originY = y;
    }
}

void mouseMove(int x, int y) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    angelWithX += x - originX;
    if (viewPointDistance + y - originY >= 100 && viewPointDistance + y - originY <= 500) {
        float newViewPointDistance = viewPointDistance + y - originY;
        viewPointHeight = viewPointHeight * newViewPointDistance / viewPointDistance;
        viewPointDistance = newViewPointDistance;
    }
    originX = x;
    originY = y;
    gluLookAt(viewPointDistance * cos(angelToRadius * angelWithX) + lookAtX, viewPointHeight, viewPointDistance * sin(angelToRadius * angelWithX) + lookAtZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Project 3");
    obj.parse("KeyboardAndMouse.obj");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutMainLoop();
    return 0;
}
