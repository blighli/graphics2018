#pragma once
#include <glm/glm.hpp>

class LightPoint
{
public:

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction;

	float constant;
	float linear;
	float quadratic;

	LightPoint();
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

	
	
};

