#include "buffer.h"
Buffer::Buffer(GLfloat *data, GLsizei count, GLuint componentCount) :m_ComponentCount(componentCount)
{
	glGenBuffers(1, &m_BufferID);													  //创建顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);										  //绑定到GL_ARRAY_BUFFER上
	glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);//把vertices中的数据复制到当前绑定的缓冲中
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
Buffer::~Buffer() 
{
	glDeleteBuffers(1, &m_BufferID);                                       
}
void Buffer::bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);                                 //封装绑定
}
void Buffer::unbind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);                                          //封装解绑
}
