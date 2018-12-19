#include "Camera.h"


void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

}

void Camera::ProcessMouseMovementXY(float xoffset, float yoffset) {
	Position.x += -xoffset * Speed;
	Position.y += yoffset * Speed;
}

void Camera::ProcessMouseScroll(float _yoffset) {
	Position += _yoffset * Sensitivity * Front;
}



mat4 Camera::getViewMatrix() {
	mat4 view(1.0f);
	mat4 rotatPitch = mat4::rotation(Pitch, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotatYaw = mat4::rotation(Yaw, vec3(0.0f, 1.0f, 0.0f));
	mat4 trans = mat4::translation(vec3(-Position.x, -Position.y, -Position.z));

	view = view * rotatPitch * rotatYaw * trans;

	return view;
}