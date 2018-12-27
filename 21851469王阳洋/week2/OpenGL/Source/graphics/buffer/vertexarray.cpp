#include "vertexarray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray() {
	for (int i = 0; i < m_Buffers.size(); i++) {
		delete m_Buffers[i];
	}
	glDeleteVertexArrays(1, &m_ArrayID);
}

void VertexArray::bind() const {
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addBuffer(Buffer * buffer, GLuint index) {
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT,
		GL_FALSE, 0, 0);
	m_Buffers.push_back(buffer);

	buffer->unbind();
	unbind();

}

void VertexArray::addInterLeadBuffer(Buffer * buffer, int index) {

	bind();
	buffer->bind();

	int length[4] = { 4,4,4,4 };

	int total = 4 * 4;

	int vertexByteCount = sizeof(GLfloat) * total;
	total = 0;
	for (int i =0; i < 4; i++) {
		glVertexAttribPointer(i + index, length[i], GL_FLOAT, GL_FALSE, vertexByteCount, (GLvoid *)(sizeof(GLfloat) * total));
		glEnableVertexAttribArray(i + index);
		glVertexAttribDivisor(i + index, 1);
		total += length[i];
	}
	m_Buffers.push_back(buffer);

	buffer->unbind();
	unbind();	
}


//添加实例化离散的缓存
//所有的数据都默认为GLFLOAT
//默认实例变化都为1
//index表示添加缓存的位置
//dataFormat表示了数据在缓冲里面的格式
void VertexArray::addInterLeavedBuffer(Buffer * buffer, int index, const std::vector<int> & dataFormat) {
	
	bind();
	buffer->bind();

	int LEN = dataFormat.size();

	//统计数据步长
	int total = 0;
	for (int i = 0; i < LEN; i++) {
		total += dataFormat[i];
	}
	int vertexByteCount = sizeof(GL_FLOAT) * total;

	
	total = 0;
	for (int i = 0; i < LEN; i++) {
		//设置顶点格式
		glVertexAttribPointer(index + i, dataFormat[i], GL_FLOAT, GL_FALSE, vertexByteCount, (GLvoid *)(total * sizeof(GL_FLOAT)));

		//启用
		glEnableVertexAttribArray(index + i);

		//
		glVertexAttribDivisor(index + i, 1);

		//计算偏移
		total += dataFormat[i];
	}

	m_Buffers.push_back(buffer);

	buffer->unbind();
	unbind();
	
}