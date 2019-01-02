#pragma once

#ifndef _VEC4_H_
#define _VEC4_H_

#include <iostream>

struct vec4 {
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(float _x, float _y, float _z, float _w);

	vec4 add(const vec4 & v4);
	vec4 subtract(const vec4 & v4);
	vec4 multiply(const vec4 & v4);
	vec4 divide(const vec4 & v4);

	friend vec4 operator+(vec4 left, const vec4 & right);
	friend vec4 operator-(vec4 left, const vec4 & right);
	friend vec4 operator*(vec4 left, const vec4 & right);
	friend vec4 operator/(vec4 left, const vec4 & right);

	vec4 operator+=(const vec4 & v4);
	vec4 operator-=(const vec4 & v4);
	vec4 operator*=(const vec4 & v4);
	vec4 operator/=(const vec4 & v4);
	bool operator==(const vec4 & v4);
	bool operator!=(const vec4 & v4);

	friend std::ostream & operator << (std::ostream & out, const vec4 & v4);

	static vec4 LineInterpolation(const vec4 & left, const vec4 & right ,float a);
};

#endif