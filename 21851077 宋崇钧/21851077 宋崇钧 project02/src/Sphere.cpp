#include "Sphere.h"

Sphere::Sphere(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    getVBO();
    getEBO();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}
void Sphere::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3*numTriangle, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Sphere::getVBO(){
    FILE *fin = fopen("../src/sphere.dat", "r");
    fscanf(fin, "%d %d ", &u_strip, &v_strip);
    u_num = 360 / u_strip + 1;
    v_num = 180 / v_strip + 1;
    numVertex = u_num*v_num;
    // 读取数据
    float *data = new float[8*numVertex];
    int i=0;
    while(fscanf(fin, "%f", data+i) == 1)i++;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8*numVertex*sizeof(float), data, GL_STATIC_DRAW);
    delete[] data;
}
void Sphere::getEBO(){
    // 生成索引
    int i=0, j=0, k=0;
    numTriangle  = (u_num-1)*2 + (v_num-1)*(u_num-1)*2;
    unsigned int *indices = new unsigned int[3*numTriangle];
    for(i=0; i<v_num; i++){
        for(j=0; j<u_num-1; j++){
            indices[k++] = i*u_num+j;
            indices[k++] = i*u_num+j+1;
            indices[k++] = (i+1)*u_num+j;
            indices[k++] = i*u_num+j+1;
            indices[k++] = (i+1)*u_num+j;
            indices[k++] = (i+1)*u_num+j+1;
        }
    }
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*numTriangle*sizeof(unsigned int), indices, GL_STATIC_DRAW);
    delete[] indices;
}
