#include <string>
#include<iostream>

#include "Shapes.h"
#include "ModelLoader.h"

void Shape::init(Shader* shader)
{
	this->shader = shader;
	mat4x4_identity(model);
	//初始化顶点数组对象
	for (DrawCommand* cmd : drawCommands) {
		cmd->init();
	}
}
void Shape::prepare()
{
	prepareModel();
	if (shader != nullptr) {
		glUseProgram(shader->program);
	}
}
void Shape::draw() {
	for (DrawCommand* cmd : drawCommands) {
		cmd->draw();
	}
}
void Shape::appendCmd(DrawCommand * cmd)
{
	drawCommands.push_back(cmd);
}
int Shape::getCmdSize()
{
	return drawCommands.size();
}
void Shape::prepareModel(){}
Shape::Shape() {}
Shape::~Shape()
{
	for (DrawCommand* cmd : drawCommands) {
		delete cmd;
	}
	drawCommands.clear();
}

void Sphere::prepareModel()
{
	texture.prepare();
}

Sphere::Sphere()
{
	ModelLoader loader;
	loader.loadShapeFromFile(this, "C:\\Users\\xys\\source\\repos\\OpenGLHomework01\\resource\\sphere\\sphere.obj");
}
Sphere::~Sphere() {}

void Sun::prepareModel()
{
	Sphere::prepareModel();
	mat4x4_identity(model);
}
Sun::Sun(){
	texture.init("C:\\Users\\xys\\source\\repos\\OpenGLHomework01\\resource\\sphere\\sun.jpg");
}
Sun::~Sun(){}

void RoatableSphere::prepareModel()
{
	Sphere::prepareModel();
	angle += M_PI * speed;
	mat4x4_identity(model);
	mat4x4_rotate_Z(model, model, angle);
	mat4x4_translate_in_place(model, roate_radius, 0.0f, 0.0f);
	mat4x4_scale_aniso(model, model, 0.25, 0.25, 0.25);
}

Mercury::Mercury()
{
	texture.init("C:\\Users\\xys\\source\\repos\\OpenGLHomework01\\resource\\sphere\\mercury.jpg");
	speed *= 87.968f / 365.f;
	roate_radius *= 0.38709893f;
}
Mercury::~Mercury(){}

Venus::Venus()
{
	texture.init("C:\\Users\\xys\\source\\repos\\OpenGLHomework01\\resource\\sphere\\venus.jpg");
	speed *= 224.701f / 365.f;
	roate_radius *= 0.7255305f;
}
Venus::~Venus(){}

Earth::Earth() {
	texture.init("C:\\Users\\xys\\source\\repos\\OpenGLHomework01\\resource\\sphere\\earth.jpg");
}
Earth::~Earth() {}