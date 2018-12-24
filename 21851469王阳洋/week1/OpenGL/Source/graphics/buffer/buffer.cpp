#include "buffer.h"

Buffer::Buffer(GLfloat *data, GLsizei count, GLuint componentCount) 
	:m_ComponentCount(componentCount){
	glGenBuffers(1, &m_BufferID);//获得ID
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);//绑定ID
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GL_FLOAT), data, GL_STATIC_DRAW);//传输数据
	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑
}

Buffer::~Buffer(){
	glDeleteBuffers(1,&m_BufferID);
}

void Buffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void Buffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Buffer::getComponentCount() const {
	return m_ComponentCount;
}
