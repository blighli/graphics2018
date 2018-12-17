#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	Forward = glm::normalize(target - position);
	WorldUp = glm::normalize(worldup);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Right, Forward);
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Pitch = glm::radians(pitch);
	Yaw = glm::radians(yaw);
	Position = position;
	WorldUp = glm::normalize(worldup);
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Right, Forward);

}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Right, Forward);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * 0.002f;
	Yaw -= deltaX * 0.002f;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos() {
	Position += Forward * speedZ * 0.2f + Right * speedX * 0.2f + Up * speedY * 0.2f;
}

void Camera::MoveZ(float z) {
	speedZ = z;
}

void Camera::MoveX(float x) {
	speedX = x;
}

void Camera::MoveY(float y) {
	speedY = y;
}