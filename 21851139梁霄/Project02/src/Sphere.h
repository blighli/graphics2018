#ifndef SPHERE_H
#define SPHERE_H
#include <stdio.h>
#include <glad/glad.h>

class Sphere{
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int u_strip, v_strip;
    int u_num, v_num;
    int numVertex;
    int numTriangle;
    Sphere();
    void draw();
private:
    void getVBO();
    void getEBO(); 
};

#endif