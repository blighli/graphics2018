#pragma once

typedef struct {
	float x, y, z;
	float r, g, b;
} PointColor;

typedef struct {
	float x, y, z;
} Point;


class Shader {
public:
	Shader();
	virtual ~Shader();
	GLuint program, vertex_shader, fragment_shader;
	GLuint MVP_location[3];
	GLuint vpos_location, vcol_location;
};
#include "linmath.h"
class Shape 
{
protected:
	mat4x4 MVP[3];
	GLuint vao;
	Shader* shader;
	virtual void bindData() {};
	virtual void prepareMVP() {};
	virtual void drawData() {};
public:
	void init(Shader *shader);
	void mvp(mat4x4 model, mat4x4 view, mat4x4 projection);
	void draw();
};

class Coordinate : public Shape 
{
public :
	Coordinate() {};
	virtual ~Coordinate() {};
protected:
	virtual void bindData() override;
	virtual void prepareMVP() override;
	virtual void drawData() override;
};

class Cube : public Shape
{
public:
	Cube() {};
	virtual ~Cube() {};
protected:
	virtual void bindData() override;
	virtual void prepareMVP() override;
	virtual void drawData() override;
};