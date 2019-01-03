#pragma once

#ifndef _VEC2_H_
#define _VEC2_H_


#include <iostream>

struct vec2{
	float x;
	float y;

	vec2();
	vec2(float _x, float _y);

	vec2 add(const vec2 & v2);
	vec2 subtract(const vec2 & v2);
	vec2 multiply(const vec2 & v2);
	vec2 divide(const vec2 & v2);

	friend vec2 operator+(vec2 left, const vec2 & right);
	friend vec2 operator-(vec2 left, const vec2 & right);
	friend vec2 operator*(vec2 left, const vec2 & right);
	friend vec2 operator/(vec2 left, const vec2 & right);

	vec2 operator+=(const vec2 & v2);
	vec2 operator-=(const vec2 & v2);
	vec2 operator*=(const vec2 & v2);
	vec2 operator/=(const vec2 & v2);
	bool operator==(const vec2 & v2);
	bool operator!=(const vec2 & v2);

	friend std::ostream & operator << (std::ostream & out, const vec2 & v2);
};

#endif // !_VEC2_H_
