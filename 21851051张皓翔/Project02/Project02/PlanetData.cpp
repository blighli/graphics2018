#include "PlanetData.h"


PlanetData::PlanetData() {

}

PlanetData::PlanetData(int _daypersecond, float _rotationt, float _revolutiont, float _sund, float _inita, bool _isclockwise = true) {
	dayPerSecond = _daypersecond;
	rotationT = _rotationt;
	revolutionT = _revolutiont;
	sunD = _sund;
	initialAngle = _inita;
	PI = (float)glm::radians(180.0);
	lastTime = 0.0;

	rotation = 0;
	revolution = initialAngle;

	isClockWise = _isclockwise;

	position.z = sunD * sin(glm::radians(initialAngle));
	position.x = sunD * cos(glm::radians(initialAngle));
	position.y = 0;
	rotateMatrix = glm::mat4(1);
}

void PlanetData::UpdateData(GLfloat deltaTime) {
	
	rotateMatrix = glm::mat4(1);

	rotation = isClockWise ? (rotation - 360.0 / rotationT * dayPerSecond * deltaTime)
		: (rotation + 360.0 / rotationT * dayPerSecond * deltaTime);
	if (rotation > 360)
		rotation -= 360;
	if (rotation < 0)
		rotation += 360;

	revolution += 360.0 / revolutionT * dayPerSecond * (float)deltaTime;
	if (revolution > 360)
		revolution -= 360;
	if (revolution < 0)
		revolution += 360;

	position.z = sunD * sin(glm::radians(revolution));
	position.x = sunD * cos(glm::radians(revolution));
	position.y = 0;

	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotation), glm::vec3(0, 1, 0));
}

PlanetData::~PlanetData() {

}