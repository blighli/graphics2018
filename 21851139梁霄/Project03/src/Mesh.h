#ifndef MESH_H
#define MESH_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // glm::vec3 Tangent;
    // glm::vec3 Bitangent;
};

struct Texture{
    unsigned int id;
    string type;
    string path;
};

class Mesh{
    public:
        /*    变量     */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        unsigned int VAO;
        /*    函数     */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        unsigned int VBO, EBO;
        void setupMesh();
};

#endif