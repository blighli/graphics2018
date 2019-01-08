#pragma once

#ifndef _MAT4_H_
#define _MAT4_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include "vec4.h"
#include "vec3.h"

struct mat4{
	union {
		float elements[4 * 4];
		vec4 columns[4];
	};

	mat4();
	mat4(const float a);


	mat4 & multiply(const mat4 & m4);
	friend mat4 operator * (const  mat4 & left, mat4 right);
	friend vec3 operator*(const vec3 & left, mat4 right);
	mat4 & operator *= (const mat4 & m4);

	static mat4 identity();
	static mat4 transposed(const mat4 & m);
	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);
	static mat4 translation(const vec3 &translation);
	static mat4 rotation(float angle, const vec3 &axis);
	static mat4 scale(const vec3 &scale);
	
	static float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}
	
};




#endif // !_MAT4_H_