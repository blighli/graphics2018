#pragma once

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class PlanetData {
public:
	PlanetData();
	PlanetData(int _daypersecond, float _rotationt, float _revolutiont, float _sund, float _inita, bool _isclockwise);
	~PlanetData();

	glm::vec3 position;
	glm::mat4 rotateMatrix;

	void UpdateData(GLfloat);
private:
	int dayPerSecond;
	float rotation;
	float rotationT;
	float revolution;
	float revolutionT;
	float sunD;
	float initialAngle;
	bool isClockWise;
	float PI;

	GLfloat lastTime;
	GLfloat deltaTime;
	
	
};