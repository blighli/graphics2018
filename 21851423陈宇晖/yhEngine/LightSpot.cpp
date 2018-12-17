#include "LightSpot.h"



LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	UpdateDirection();
}


LightSpot::~LightSpot()
{
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}