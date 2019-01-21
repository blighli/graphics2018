#pragma once
#include "linmath.h"

class Camera
{
private:
	mat4x4 view, project;
protected:
	vec4 eye, forward, up;
public:
	void lookForward(vec3 eye, vec3 forward, vec3 up);
	void translate(vec3 delta);
	void yaw(float angle);
	//”“ ÷∂®‘Ú
	void pitch(float angle);
	void roll(float angle);
	void moveUp(float delta);
	void moveDown(float delta);
	void moveForward(float delta);
	void moveBack(float delta);
	void moveLeft(float delta);
	void moveRight(float delta);
	pMat4x4 getViewMat() { return view; };
	pMat4x4 getProjectMat() { return project; };
	Camera();
	~Camera();
};

