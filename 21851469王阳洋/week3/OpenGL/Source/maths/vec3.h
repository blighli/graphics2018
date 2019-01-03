#pragma once

#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>

struct vec3 {
	float x;
	float y;
	float z;

	vec3();
	vec3(float _x, float _y, float _z);

	//旋转需要正交化
	vec3(float _x, float _y, float _z, bool norm);

	vec3 add(const vec3 & v3);
	vec3 subtract(const vec3 & v3);
	vec3 multiply(const vec3 & v3);
	vec3 divide(const vec3 & v3);

	friend vec3 operator+(vec3 left, const vec3 & right);
	friend vec3 operator-(vec3 left, const vec3 & right);
	friend vec3 operator*(vec3 left, const vec3 & right);
	friend vec3 operator/(vec3 left, const vec3 & right);
	friend vec3 operator*(vec3 left, const float & value);

	vec3 operator+=(const vec3 & v3);
	vec3 operator-=(const vec3 & v3);
	vec3 operator*=(const vec3 & v3);
	vec3 operator/=(const vec3 & v3);
	bool operator==(const vec3 & v3);
	bool operator!=(const vec3 & v3);

	friend std::ostream & operator << (std::ostream & out, const vec3 & v3);

	static vec3 normalize(const vec3 & v3);
	static vec3 cross(const vec3 & left, const vec3 &right);
};

#endif 