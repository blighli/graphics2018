#pragma once
#include <glm/glm.hpp>

class Camera {


public:

	// constructor
	Camera();

	// Sets the camera to the initial position
	void startPosition();

	void translate(float x, float y, float z);

	void rotate(float angx, float angy, float angz);

	glm::vec3 center;
	glm::vec3 eye;
	glm::vec3 up;
	glm::vec3 angle;

};