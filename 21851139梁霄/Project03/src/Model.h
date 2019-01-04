#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

class Model 
{
    public:
        /*  函数   */
        Model(const char *path);
        void Draw(Shader shader);
    private:
        /*  模型数据  */
        vector<Mesh> meshes;
        string directory;
        vector<Texture> textures_loaded;
        /*  函数   */
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
        unsigned int TextureFromFile(const char *path, const string &directory);
};

#endif