#ifndef __MY_MODEL_H__
#define __MY_MODEL_H__

#include <gl\glut.h>
#include <vector>
#include <string>

struct Vertex
{
	GLfloat    x;
	GLfloat    y;
	GLfloat    z;
};

struct Face
{
	GLushort       Index[3];
	GLushort       MaterialPos;
	Vertex         Normal;
};

struct Chunk
{
	GLushort        ID;
	GLuint          Len;
};

struct Material
{
	std::string        name;
	GLfloat		       ambientColor[3];
	GLfloat		       diffuseColor[3];
	GLfloat		       specularColor[3];
	GLfloat		       emissiveColor[3];
	GLfloat		       shininess;
	GLfloat		       transparency;
};

struct Object 
{
	std::string                  Name;
	std::vector< Vertex >        Vertexs;
	std::vector< Face >          Faces;
};

struct Model 
{
	std::vector< Object >        MyObject;
	std::vector< Material >      MyMaterial;
};

#endif