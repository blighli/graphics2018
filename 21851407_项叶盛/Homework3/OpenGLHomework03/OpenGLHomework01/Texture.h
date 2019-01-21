#pragma once
#include <vgl.h>

class Texture
{
protected:
	GLuint texture; 
	unsigned int loadTexture(char const * path);
public:
	void init(const char* filename);
	void prepare();
	Texture();
	virtual ~Texture();
};
