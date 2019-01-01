#pragma once

#ifndef _BUFFER_H_
#define _BUFFER_H_
	
#include "GL/glew.h"

class Buffer{

private:
	GLuint m_BufferID;
	GLuint m_ComponentCount;

public:
	Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
	~Buffer();
	void bind() const;
	void unbind() const;
	GLuint getComponentCount() const;

};

#endif