#include "vertexarray.h"
#include "object.h"
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);                 //创建VAO
}
VertexArray::~VertexArray() 
{
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];                          //删除容器中的vbo指针指向的内容
	glDeleteVertexArrays(1, &m_ArrayID);              //删除vao
}
void VertexArray::bind() const                         //封装bind
{
	glBindVertexArray(m_ArrayID);   //绑定VAO对象
}

void VertexArray::unbind() const                     //封装解绑
{
	glBindVertexArray(0);
}
void VertexArray::addBuffer(Buffer *buffer, GLuint index, GLuint stride, const void* offset) {
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);                                                       //激活索引 对应的是vert里的layout
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, stride, offset);    //解释顶点作用，数量，及处理方式
	m_Buffers.push_back(buffer);                                                            //把顶点压入容器

	buffer->unbind();                                                                       //先解绑vbo
	unbind();                                                                               //再解绑vao
}