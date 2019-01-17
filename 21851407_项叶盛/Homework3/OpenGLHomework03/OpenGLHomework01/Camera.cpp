#include "Camera.h"



void Camera::lookForward(vec3 eye, vec3 forward, vec3 up)
{
	mat4x4_look_forward(view, eye, forward, up);
}

void Camera::translate(vec3 delta)
{
	vec3_add(eye, eye, delta);
	lookForward(eye, forward, up);
}

void Camera::yaw(float angle)
{
	mat4x4 R;
	mat4x4_identity(R);
	mat4x4_rotate(R, R, up[0], up[1], up[2], angle);
	mat4x4_mul_vec4(forward, R, forward);
	lookForward(eye, forward, up);
}

void Camera::pitch(float angle)
{
	vec3 right;
	vec3_mul_cross(right, forward, up);

	mat4x4 R;
	mat4x4_identity(R);
	mat4x4_rotate(R, R, right[0], right[1], right[2], angle);
	mat4x4_mul_vec4(forward, R, forward);
	mat4x4_mul_vec4(up, R, up);
	lookForward(eye, forward, up);
}

void Camera::roll(float angle)
{
	mat4x4 R;
	mat4x4_identity(R);
	mat4x4_rotate(R, R, forward[0], forward[1], forward[2], angle);
	mat4x4_mul_vec4(up, R, up);
	lookForward(eye, forward, up);
}

void Camera::moveUp(float delta)
{
	vec3 deltaVector;
	vec3_mul_inner(deltaVector, up, delta);
	vec3_add(eye, eye, deltaVector);
	lookForward(eye, forward, up);
}

void Camera::moveDown(float delta)
{
	moveUp(-delta);
}

void Camera::moveForward(float delta)
{
	vec3 deltaVector;
	vec3_mul_inner(deltaVector, forward, delta);
	vec3_add(eye, eye, deltaVector);
	lookForward(eye, forward, up);
}

void Camera::moveBack(float delta)
{
	moveForward(-delta);
}

void Camera::moveLeft(float delta)
{
	moveRight(-delta);
}

void Camera::moveRight(float delta)
{
	vec3 right;
	vec3_mul_cross(right, forward, up);
	vec3_mul_inner(right, right, delta);
	vec3_add(eye, eye, right);
	lookForward(eye, forward, up);
}


Camera::Camera()
	: eye{ 0.f, -20.f, -1.0f , 1.0f }
	, forward{ 0.f, 0.f, 1.f , 1.0f }
	, up{ 0.f, 1.f, 0.f , 1.0f }
{
	pitch(87.f/180.f*M_PI);
	mat4x4_identity(project);
	mat4x4_perspective(project, 120.f / 360.f, 1.f, 5.f, -5.f);
}

Camera::~Camera()
{
}
