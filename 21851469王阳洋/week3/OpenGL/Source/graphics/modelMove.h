#pragma once

#include "Window.h"
#include "../maths/maths_func.h"

class ModelMove {
private:
	vec3 trans;
	float m_theta = 0;
	float m_speed = 10;

public:
	void move(Window * window,float deltaTime) {
		if(window->isKeyPressed(GLFW_KEY_I)) {
			trans.z -= deltaTime * m_speed;
		}
		if (window->isKeyPressed(GLFW_KEY_K)) {
			trans.z += deltaTime * m_speed;
		}
		if (window->isKeyPressed(GLFW_KEY_J)) {
			trans.x -= deltaTime * m_speed;
		}
		if (window->isKeyPressed(GLFW_KEY_L)) {
			trans.x += deltaTime * m_speed;
		}
		if (window->isKeyPressed(GLFW_KEY_U)) {
			m_theta += deltaTime * m_speed;
		}
		if (window->isKeyPressed(GLFW_KEY_O)) {
			m_theta -= deltaTime * m_speed;
		}
	}

	mat4 getModelMatrix() {
		return mat4::translation(trans) * mat4::rotation(m_theta, vec3(0, 1, 0));
	}
};