#pragma once

#include <GL/glew.h>
#include <string>
#include"stb_image.h"

class Texture {
private:
	GLuint m_TextureID;
	GLuint m_ComponentCount;
	GLuint m_TextUnit;
public:
	Texture( const char *paths,GLuint componentCount, GLuint textUnit);
	~Texture();
	void bind() const;
	void unbind() const;
	void aBind() const;

	GLuint getComponentCount() const { return m_ComponentCount; }
};