#include "DrawCommand.h"

DrawCommand::DrawCommand(EDrawType type)
	: type(type)
{
}

DrawCommand::~DrawCommand()
{
	glDeleteBuffers(1, &vbo);
}

void DrawCommand::init()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void DrawCommand::draw()
{
	glBindVertexArray(vao);
}

TriangleDrawCommand::TriangleDrawCommand(vec4 vertex_coord[], vec3 normal_coord[], vec2 texture_coord[])
	: DrawCommand(EDrawType::TRIANGLE)
{
	GLfloat* index = vertex_data;
	for (int i = 0; i < 3; i++) {
		memcpy(index, vertex_coord[i], sizeof(GLfloat) * 4);
		memcpy(index + 4, normal_coord[i], sizeof(GLfloat) * 3);
		memcpy(index + 7, texture_coord[i], sizeof(GLfloat) * 2);
		index += 9;
	}
}

void TriangleDrawCommand::init()
{
	DrawCommand::init();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 7));
}

void TriangleDrawCommand::draw()
{
	DrawCommand::draw();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

QuadrangleDrawCommand::QuadrangleDrawCommand(vec4 vertex_coord[], vec3 normal_coord[], vec2 texture_coord[])
	: DrawCommand(EDrawType::QUADRANGLE)
{
	GLfloat* index = vertex_data;
	for (int i = 0; i < 4; i++) {
		memcpy(index, vertex_coord[i], sizeof(GLfloat) * 4);
		memcpy(index + 4, normal_coord[i], sizeof(GLfloat) * 3);
		memcpy(index + 7, texture_coord[i], sizeof(GLfloat) * 2);
		index += 9;
	}
}

void QuadrangleDrawCommand::init()
{
	DrawCommand::init();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 7));
}

void QuadrangleDrawCommand::draw()
{
	DrawCommand::draw();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
