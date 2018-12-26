#include "Camera.h"
#include<iostream>


Camera::Camera(float sensivitity = 1.0)
{
	MAX_PITCH_ANGLE = 89;

	viewUp = glm::vec3(0.0, 1.0, 0.0);
	forward = glm::normalize(glm::vec3(0.0, 0.0, -1.0));
	side = glm::vec3(1.0, 0.0, 0.0);
	position = glm::vec3(0.0, 0.0, 1.8);

	
	
	firstMouseMove = true;
	mouseSensitivity = sensivitity;
	moveSpeed = 2;
}



Camera::~Camera()
{
}

void Camera::handleMouseMove(float xPos, float yPos)
{
	if (firstMouseMove) {
		lastMousePosition.x = xPos;
		lastMousePosition.y = yPos;
		firstMouseMove = false;
	}

	GLfloat xOffset = lastMousePosition.x - xPos;
	GLfloat yOffset = lastMousePosition.y - yPos;

	lastMousePosition.x = xPos;
	lastMousePosition.y = yPos;

	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	
	pitchAngle += yOffset;
	yawAngle += xOffset;

	if (pitchAngle > MAX_PITCH_ANGLE)
		pitchAngle = MAX_PITCH_ANGLE;
	if (pitchAngle < -MAX_PITCH_ANGLE)
		pitchAngle = -MAX_PITCH_ANGLE;
	if (yawAngle > 360)
		yawAngle -= 360;
	if (yawAngle < 0)
		yawAngle += 360;
	updateVector();
}

void Camera::handleKeyPress(int key, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	switch (key)
	{
	case GLFW_KEY_W:
		position += forward * velocity;
		break;
	case GLFW_KEY_S:
		position -= forward * velocity;
		break;
	case GLFW_KEY_A:
		position -= side * velocity;
		break;
	case GLFW_KEY_D:
		position += side * velocity;
		break;
	default:
		break;
	}
	//printf("( %f , %f , %f )\n", position.x, position.y, position.z);
}

void Camera::updateVector()
{
	glm::vec3 newForward;
	newForward.x = -sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	newForward.y = sin(glm::radians(pitchAngle));
	newForward.z = -cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	forward = glm::normalize(newForward);

	glm::vec3 newSide;
	newSide.x = cos(glm::radians(yawAngle));
	newSide.y = 0.0;
	newSide.z = -sin(glm::radians(yawAngle));
	side = glm::normalize(newSide);
}


