#pragma once

#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/basics/window.h"

class Camera {
private:
	vec3 m_Position;
	float m_Pitch;
	float m_Yaw;
	Window *m_Window;

public:
	Camera(Window *w) {
		m_Window = w;
		m_Position.x = m_Position.y = m_Position.z = m_Pitch = m_Yaw  = 0;
	};

	void move() {
		if (m_Window->isKeyPressed(87)) {	// W
			m_Position.z += 0.02f;
		}
		if (m_Window->isKeyPressed(83)) {	// S
			m_Position.z -= 0.02f;
		}
		if (m_Window->isKeyPressed(68)) {	// D
			m_Position.x += 0.02f;
		}
		if (m_Window->isKeyPressed(65)) {	// A
			m_Position.x -= 0.02f;
		}
		if (m_Window->isKeyPressed(340)) {	// L_shift
			m_Position.y += 0.02f;
		}
		if (m_Window->isKeyPressed(341)) {	// L_ctrl
			m_Position.y -= 0.02f;
		}
		if (m_Window->isKeyPressed(81)) {	// Q
			m_Yaw -= 0.6f;
		}
		if (m_Window->isKeyPressed(69)) {	// E
			m_Yaw += 0.6f;
		}
		if (m_Window->isKeyPressed(256)) {	// ESC
			m_Window->exit();
		}
	};

	mat4 CreateViewMatrix() {
		mat4 view_matrix(1.0);
		view_matrix *= (mat4::rotation(m_Pitch, vec3(1.0, 0.0, 0.0)));
		view_matrix *= (mat4::rotation(m_Yaw, vec3(0.0, 1.0, 0.0)));
		view_matrix *= (mat4::translation(vec3(-m_Position.x, -m_Position.y, -m_Position.z)));
		return view_matrix;
	}
};