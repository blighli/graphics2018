#pragma once


#include <GL/glew.h>
#include "soil.h"


class Texture {
private:
	int m_width;
	int m_height;
	
	GLuint m_textureID;

public:
	Texture(const char * picPath) {
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		unsigned char* image = SOIL_load_image(picPath, &m_width, &m_height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void bind() {
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};