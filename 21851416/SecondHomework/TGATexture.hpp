
#ifndef TGATexture_hpp
#define TGATexture_hpp


#include <GLUT/GLUT.h>
#include <iostream>

using namespace std;

typedef struct
{
    GLubyte *imageData;
    GLuint bpp;
    GLuint width;
    GLuint height;
    GLuint texID;
}TextureImage;

bool LoadTGA(TextureImage *texture,char *fileName);

#endif /* TGATexture_hpp */
