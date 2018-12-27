#include "cameraRPG.h"
#include <iostream>


void CameraRPG::init() {

	m_Move = vec3(0.0f, 0.0f, 0.0f);
	m_Front = vec3(0.0, 0.0f, -1.0f);//默认朝向z轴负方向
	m_Zoom = m_Front;
	m_WorldUp = AXISY;

	m_Speed = SPEED;
	m_Sensitivity = SENSITIVTY;
	m_Omission = OMISSION;
	
	m_Yaw = 0.0f;
	m_Pitch = 0.0f;

}

void CameraRPG::vectorUpdate() {
	vec3 temp_Front = m_Front * mat4::rotation(m_Yaw, AXISY);
	m_Right = vec3::normalize(vec3::cross(temp_Front, m_WorldUp));
	m_Up = vec3::normalize(vec3::cross(m_Right, temp_Front));
}

CameraRPG::CameraRPG(vec3 Target, vec3 Offset) {
	init();
	m_Target = Target;
	m_Offset = Offset;
}

CameraRPG::CameraRPG(GLfloat TargetX, GLfloat TargetY, GLfloat TargetZ, GLfloat OffsetX, GLfloat OffsetY, GLfloat OffsetZ) {
	init();
	m_Target = vec3(TargetX, TargetY, TargetZ);
	m_Offset = vec3(OffsetX, OffsetY, OffsetZ);
}

vec3 CameraRPG::getCameraPos() {
	return m_Target + ((m_Offset + vec3::normalize(m_Offset) * m_Distance) * mat4::rotation(m_Pitch, AXISX) * mat4::rotation(m_Yaw, AXISY)) + m_Move;
}

vec3 CameraRPG::getTargetPos() {
	return m_Target + m_Move;
}

void CameraRPG::processKeyboard(Window * window, GLfloat deltaTime) {

	GLfloat velocity = m_Speed * deltaTime;

	if (window->isKeyPressed(GLFW_KEY_W)) {
		m_Move += m_Front * mat4::rotation(m_Yaw, AXISY) * velocity;
	}
	if(window->isKeyPressed(GLFW_KEY_S)) {
		m_Move -= m_Front * mat4::rotation(m_Yaw, AXISY) * velocity;
	}
	if(window->isKeyPressed(GLFW_KEY_A)) {
		m_Move -= m_Right * velocity;
	}
	if(window->isKeyPressed(GLFW_KEY_D)) {
		m_Move += m_Right * velocity;
	}
	if (window->isKeyPressed(GLFW_KEY_Q)) {
		m_Yaw += velocity * m_Sensitivity;
	}
	if (window->isKeyPressed(GLFW_KEY_E)) {
		m_Yaw -= velocity * m_Sensitivity;
	}
	if (window->isKeyPressed(GLFW_KEY_Z)) {
		m_Pitch += velocity * m_Sensitivity;
	}
	if (window->isKeyPressed(GLFW_KEY_C)) {
		m_Pitch -= velocity * m_Sensitivity;
	}

	if (m_Pitch > 89.9f)
		m_Pitch = 89.9f;
	if (m_Pitch < -44.9f)
		m_Pitch = -44.9f;
}

void CameraRPG::processMouseMovenment(GLfloat xoffset, GLfloat yoffset, GLfloat deltaTime) {
	
	GLfloat velocity = m_Speed * deltaTime;
	
	if (xoffset < -m_Omission) {
		m_Move += m_Right * velocity;
	}
	if (xoffset > m_Omission) {
		m_Move -= m_Right * velocity;
	}
	if (yoffset < -m_Omission) {
		m_Move -= m_Up * velocity;
	}
	if (yoffset > m_Omission) {
		m_Move += m_Up * velocity;
	}

	if (m_Pitch > 89.9f)
		m_Pitch = 89.9f;
	if (m_Pitch < -44.9f)
		m_Pitch = -44.9f;
}

void CameraRPG::processMouseRotate(GLfloat xoffset, GLfloat yoffset, GLfloat deltaTime) {

	GLfloat velocity = m_Speed * deltaTime * m_Sensitivity * m_Sensitivity;

	if (xoffset < -m_Omission) {
		m_Yaw += velocity;
	}
	if (xoffset > m_Omission) {
		m_Yaw -= velocity;
	}
	if (yoffset < -m_Omission) {
		m_Pitch += velocity;
	}
	if (yoffset > m_Omission) {
		m_Pitch -= velocity;
	}
}

void CameraRPG::processMouseScroll(GLfloat yoffest, GLfloat deltaTime) {
	
	
}

void CameraRPG::update(Window * window, GLfloat & prePosX, GLfloat & prePosY, GLfloat deltaTime, bool & isFirst) {

	//键盘处理
	processKeyboard(window, deltaTime);

	//鼠标拖动，旋转处理
	if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) || window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
		double nowPosX, nowPosY;
		GLfloat gl_nowPosX, gl_nowPosY;
		window->getMousePosition(nowPosX, nowPosY);
		gl_nowPosX = (GLfloat)nowPosX;
		gl_nowPosY = (GLfloat)nowPosY;
		GLfloat xoffet = gl_nowPosX - prePosX;
		GLfloat yoffet = gl_nowPosY - prePosY;
		if (isFirst) {
			xoffet = 0;
			yoffet = 0;
			isFirst = false;
		}
		prePosX = gl_nowPosX;
		prePosY = gl_nowPosY;
		if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			processMouseRotate(xoffet, yoffet, deltaTime);
		}
		if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			processMouseMovenment(xoffet, yoffet, deltaTime);
		}
	}

	window->getAsepct(m_Distance);

	vectorUpdate();
}

mat4 CameraRPG::getViewMatrix() {
	//pitch和yaw有先后顺序
	return CameraRPG::lookAt(m_Target + ((m_Offset + vec3::normalize(m_Offset) * m_Distance) * mat4::rotation(m_Pitch, AXISX) * mat4::rotation(m_Yaw, AXISY)) + m_Move, m_Target + m_Move, m_Up);
}


mat4 CameraRPG::lookAt(const vec3 & cameraPos, const vec3 & cameraTarget, const vec3 & cameraUp) {

	vec3 Direction = vec3::normalize(cameraPos - cameraTarget);
	vec3 Right = vec3::normalize(vec3::cross(cameraUp, Direction));
	vec3 Up = vec3::cross(Direction, Right);

	mat4 ans = mat4(1);

	ans.elements[4 * 0 + 0] = Right.x;
	ans.elements[4 * 1 + 0] = Right.y;
	ans.elements[4 * 2 + 0] = Right.z;

	ans.elements[4 * 0 + 1] = Up.x;
	ans.elements[4 * 1 + 1] = Up.y;
	ans.elements[4 * 2 + 1] = Up.z;

	ans.elements[4 * 0 + 2] = Direction.x;
	ans.elements[4 * 1 + 2] = Direction.y;
	ans.elements[4 * 2 + 2] = Direction.z;

	vec3 dot = Right * cameraPos;
	ans.elements[4 * 3 + 0] = -(dot.x + dot.y + dot.z);
	dot = Up * cameraPos;
	ans.elements[4 * 3 + 1] = -(dot.x + dot.y + dot.z);
	dot = Direction * cameraPos;
	ans.elements[4 * 3 + 2] = -(dot.x + dot.y + dot.z);

	return ans;
}


