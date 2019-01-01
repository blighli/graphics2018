#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~Camera();

	glm::vec3 Position;	//相机位置
	glm::vec3 Forward;	//相机方向
	glm::vec3 Right;	//相机右轴
	glm::vec3 Up;		//相机上轴
	glm::vec3 WorldUp;	//世界上轴

	float Pitch;		//俯角
	float Yaw;			//水平转角
	float speedZ = 0;	//Z轴平移速度
	float speedY = 0;	//Y轴平移速度
	float speedX = 0;	//X轴平移速度

	/*获得当前位置的view矩阵*/
	glm::mat4 GetViewMatrix();

	/*根据deltaXY移动相机*/
	void ProcessMouseMovement(float deltaX, float deltaY);

	/*更新相机位置*/
	void UpdateCameraPos();

	/*Z轴移动*/
	void MoveZ(float z);

	/*X轴移动*/
	void MoveX(float x);
	
	/*X轴移动*/
	void MoveY(float y);

private:
	/*更新相机坐标向量*/
	void UpdateCameraVectors();
};