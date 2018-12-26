#pragma once


#include <vector>
#include <GL/glew.h>

#include "buffer.h"

class VertexArray {
private:
	GLuint m_ArrayID;
	std::vector<Buffer*> m_Buffers;      //盛装指向buffer指针的容器

public:
	VertexArray();
	~VertexArray();
	void addBuffer(Buffer *buffer, GLuint index, GLuint stride, const void* offset);
	void bind() const;
	void unbind() const;
};