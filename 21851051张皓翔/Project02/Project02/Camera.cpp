#include "Camera.h"



Camera::Camera(float sensivitity = 1.0, float depth = 1.0)
{
	MAX_PITCH_ANGLE = 89;

	viewUp = glm::vec3(0.0, 1.0, 0.0);
	forward = glm::normalize(glm::vec3(0.0, 0.0, -1.0));
	side = glm::vec3(1.0, 0.0, 0.0);
	position = glm::vec3(0.0, 80, 40);

	focusPlanet = -1;
	
	firstMouseMove = true;
	mouseSensitivity = sensivitity;
	moveSpeed = 30;
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
	if (focusPlanet != -1)
		updateSphericalCoord();
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

void Camera::updateSphericalCoord() {
	
	float gama = 90 + pitchAngle;
	float theta = yawAngle;
	
	position.x = planetEntities[focusPlanet].coreData.position.x + aimD * sin(glm::radians(gama)) * sin(glm::radians(theta));
	position.y = planetEntities[focusPlanet].coreData.position.y + aimD * cos(glm::radians(gama));
	position.z = planetEntities[focusPlanet].coreData.position.z + aimD * sin(glm::radians(gama)) * cos(glm::radians(theta));

	//printf("Camposition: (%f, %f, %f)\n", position.x, position.y, position.z);
	//printf("PlanetPosit: (%f, %f, %f)\n", planetEntities[focusPlanet].coreData.position.x,
	//	planetEntities[focusPlanet].coreData.position.y, planetEntities[focusPlanet].coreData.position.z);
}

void Camera::FocusPlanet(int planet) {	//ÉãÏñ»ú¸úËæÄ³ÐÇÇò
	focusPlanet = planet;
	aimD = planetEntities[planet].radius * 5;
	std::cout << aimD << std::endl;
	float distance = glm::length(planetEntities[planet].coreData.position - position) + aimD;
	glm::vec3 planetPos = planetEntities[planet].coreData.position;
	glm::mat4 camTrans = glm::mat4(1);
	glm::vec3 aimVec = planetPos - position;
	/*glm::vec3 transvec = (planetentities[planet].coredata.position - position) -
		glm::normalize(planetentities[planet].coredata.position - position) * aimd;*/
	glm::vec3 transVec = aimVec - forward * aimD;
	camTrans = glm::translate(camTrans, transVec);
	position = camTrans * glm::vec4(position,1.0);
	/*float theta, gama;
	float dY;
	
	glm::vec3 planetPos = planetEntities[planet].coreData.position;
	dY = glm::length(glm::vec2(planetPos.z - position.z, planetPos.x - position.x));
	gama = acosf(position.y / aimD) * (180 / glm::radians(180.0));

	if (position.z > planetEntities[planet].coreData.position.z) {
		if (position.x > planetEntities[planet].coreData.position.x) {
			theta = asinf((position.z - planetPos.z) / dY) * (180 / glm::radians(180.0));
		}
		else {
			theta = -asinf((position.z - planetPos.z) / dY) * (180 / glm::radians(180.0));
		}
	}
	else {
		if (position.x > planetEntities[planet].coreData.position.x) {
			theta = asinf((position.z - planetPos.z) / dY) * (180 / glm::radians(180.0));
		}
		else {
			theta = -asinf((position.z - planetPos.z) / dY) * (180 / glm::radians(180.0));
		}
	}*/
	
	/*printf("%f %f\n", gama, theta);
	pitchAngle = 90.0 - gama;
	yawAngle = theta;
	if (pitchAngle > MAX_PITCH_ANGLE)
		pitchAngle = MAX_PITCH_ANGLE;
	if (pitchAngle < -MAX_PITCH_ANGLE)
		pitchAngle = -MAX_PITCH_ANGLE;
	if (yawAngle > 360)
		yawAngle -= 360;
	if (yawAngle < 0)
		yawAngle += 360;
	*/
}


