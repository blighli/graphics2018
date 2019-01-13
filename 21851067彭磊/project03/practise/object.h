#pragma once
#include<string>
#include<iostream>
#include"Mat_Vec.h"
#include<vector>





struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};
/*struct texture {
	unsigned int id;
	string type;
};*/
class Object
{
public:
	std::vector<Vertex> vertices;
	std::vector<vec3u> indices;
	/*std::vector<texture> textures;*/

	Object(const char *);
};

