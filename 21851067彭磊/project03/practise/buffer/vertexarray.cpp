#include "vertexarray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);                 //创建VAO
}
VertexArray::~VertexArray() 
{
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];                          //删除容器中的vbo指针指向的内容
	for (int i = 0; i < m_Textures.size(); i++)
		delete m_Textures[i];
	glDeleteVertexArrays(1, &m_ArrayID);              //删除vao
}
void VertexArray::bind() const                         //封装bind
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		(*it)->aBind();
	}
	glBindVertexArray(m_ArrayID);   //绑定VAO对象
}

void VertexArray::unbind() const                     //封装解绑
{
	glBindVertexArray(0);
}
void VertexArray::addBuffer(Buffer *buffer, GLuint index, GLuint stride, GLuint offset) {
	bind();
	buffer->bind();

	                                                     //激活索引 对应的是vert里的layout
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, stride* sizeof(GLfloat), (void*)(offset*sizeof(GLfloat)));    //解释顶点作用，数量，及处理方式
	glEnableVertexAttribArray(index);
	m_Buffers.push_back(buffer);                                                            //把顶点压入容器

	                                                                    //先解绑vbo
	                                                                              //再解绑vao
}
void VertexArray::addTexture(Texture *texture, GLuint index, GLuint stride, GLuint offset)
{
	bind();
	texture->bind();
	//激活索引 对应的是vert里的layout

	glVertexAttribPointer(index, texture->getComponentCount(), GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
	glEnableVertexAttribArray(index);
	m_Textures.push_back(texture);
	
	
	
}