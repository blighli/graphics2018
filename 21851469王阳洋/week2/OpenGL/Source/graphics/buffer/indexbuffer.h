#pragma once


#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

#include  <GL/glew.h>

class IndexBuffer {
private:
	GLuint m_BufferID;
	GLuint m_count;
public:
	IndexBuffer(GLushort *data, GLsizei count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;

	GLuint getCount() const;
};

#endif // !_INDEX_BUFFER_H_
