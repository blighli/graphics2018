#pragma once
#include <vgl.h>
#include "linmath.h"

enum EDrawType {
	TRIANGLE,
	QUADRANGLE
};

class DrawCommand {
protected:
	GLuint vao, vbo;
public:
	DrawCommand(EDrawType type);
	virtual ~DrawCommand();
	EDrawType type;
	virtual void init();
	virtual void draw();
};
class TriangleDrawCommand : public DrawCommand {
protected:
	GLfloat vertex_data[27];
public:
	TriangleDrawCommand(vec4 vertex_coord[], vec3 normal_coord[], vec2 texture_coord[]);
	virtual ~TriangleDrawCommand() {};
	virtual void init() override;
	virtual void draw() override;
};
class QuadrangleDrawCommand : public DrawCommand {
protected:
	GLfloat vertex_data[36];
public:
public:
	QuadrangleDrawCommand(vec4 vertex_coord[], vec3 normal_coord[], vec2 texture_coord[]);
	virtual ~QuadrangleDrawCommand() {};
	virtual void init() override;
	virtual void draw() override;
};