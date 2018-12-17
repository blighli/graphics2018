#pragma once

#ifndef _CAMERA_RPG_H_
#define _CAMERA_RPG_H_

#include "../maths/maths_func.h"
#include "Window.h"

const GLfloat SPEED = 10.0f;
const GLfloat SENSITIVTY = 5.0f;	//敏感度
const GLfloat OMISSION = 2.0f;		//过滤鼠标抖动
const vec3 AXISX = vec3(1.0f, 0.0f, 0.0f);
const vec3 AXISY = vec3(0.0f, 1.0f, 0.0f);

class CameraRPG {
private:
	vec3 m_Move;	//相机移动向量
	vec3 m_Target;	//相机焦点
	vec3 m_Offset;	//相机和目标之间偏移
	vec3 m_Front;	//相机面向
	vec3 m_Zoom;	//相机放大方向
	vec3 m_Up;		//相机上向量
	vec3 m_Right;	//相机右向量
	vec3 m_WorldUp;	//世界上向量

	GLfloat m_Speed;
	GLfloat m_Sensitivity;
	GLfloat m_Yaw;
	GLfloat m_Pitch;
	GLfloat m_Omission;
	double m_Distance;

	void init();
	void vectorUpdate();

public:
	
	CameraRPG(vec3 Target, vec3 Offset);
	CameraRPG(GLfloat TargetX, GLfloat TargetY, GLfloat TargetZ, GLfloat OffsetX, GLfloat OffsetY, GLfloat OffsetZ);
	vec3 getCameraPos();
	vec3 getTargetPos();
	mat4 getViewMatrix();
	void processKeyboard(Window * window, GLfloat deltaTime);
	void processMouseMovenment(GLfloat xoffset, GLfloat yoffset, GLfloat deltaTime);
	void processMouseRotate(GLfloat xoffset, GLfloat yoffset, GLfloat deltaTime);
	void processMouseScroll(GLfloat yoffest, GLfloat deltaTime);
	void update(Window * window, GLfloat & prePosX, GLfloat & prePosY, GLfloat deltaTime, bool & isFirst);
	static mat4 lookAt(const vec3 & cameraPos, const vec3 & cameraTarget, const vec3 & cameraUp);
};

#endif // !_CAMERA_RPG_H_
