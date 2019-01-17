#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include "stb_image.h"

#include "linmath.h"

typedef struct {
	GLubyte r;
	GLubyte b;
	GLubyte g;
} ColorByte;

ColorByte blackb = { 0,0,0 };
ColorByte whiteb = { 255,255,255 };
#define B whiteb
#define W whiteb
ColorByte texture_data[] =
{
	B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B
};
void Texture::init(const char* filename)
{
	texture = loadTexture(filename);
}
void Texture::prepare()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}
Texture::Texture(){}
Texture::~Texture(){}
unsigned int Texture::loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}