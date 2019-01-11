#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

float toRadians(float degrees);
struct vec2
{
private:
	float x, y;

public:
	vec2() = default;
	vec2(float a, float b) : x(a), y(b) {}
	vec2 add(const vec2 &);
	vec2 subtract(const vec2 &);
	vec2 multiply(const vec2 &);
	vec2 divide(const vec2 &);
	friend vec2 operator+(vec2, const vec2 &);
	friend vec2 operator-(vec2, const vec2 &);
	friend vec2 operator*(vec2, const vec2 &);
	friend vec2 operator/(vec2, const vec2 &);
	friend vec2 operator+=(vec2 &, const vec2 &);
	friend vec2 operator-=(vec2 &, const vec2 &);
	friend vec2 operator*=(vec2 &, const vec2 &);
	friend vec2 operator/=(vec2 &, const vec2 &);
	friend bool operator==(const vec2 &, const vec2 &);
	friend bool operator!=(const vec2 &, const vec2 &);
	friend ostream &operator<<(ostream &os, const vec2 &ve);
	float getX() const;
	float getY() const;

};


struct vec3
{
public:
	float x, y, z;

	vec3() = default;
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3 add(const vec3 &);
	vec3 subtract(const vec3 &);
	vec3 multiply(const vec3 &);
	
	vec3 divide(const vec3 &);
	friend vec3 scalarMultiply(float, const vec3 &);
	friend vec3 cross(const vec3 &, const vec3 &);
	friend vec3 normalize(const vec3 &);
	friend vec3 operator+(vec3, const vec3 &);
	friend vec3 operator-(vec3, const vec3 &);
	friend vec3 operator*(vec3, const vec3 &);
	friend vec3 operator/(vec3, const vec3 &);
	friend vec3 operator+=(vec3 &, const vec3 &);
	friend vec3 operator-=(vec3 &, const vec3 &);
	friend vec3 operator*=(vec3 &, const vec3 &);
	friend vec3 operator/=(vec3 &, const vec3 &);
	friend bool operator==(const vec3 &, const vec3 &);
	friend bool operator!=(const vec3 &, const vec3 &);
	friend ostream &operator<<(ostream &os, const vec3 &ve);
	float getX() const;
	float getY() const;
	float getZ() const;
};

struct vec3u
{
private:
	unsigned short x, y, z;
public:
	vec3u(unsigned short a, unsigned short b, unsigned short c):x(a), y(b), z(c) {}
};

struct vec4
{
public:
	float x, y, z, w;

	
	vec4() = default;
	vec4(float a, float b, float c, float e) : x(a), y(b), z(c), w(e) {}
	vec4 add(const vec4 &);
	vec4 subtract(const vec4 &);
	vec4 multiply(const vec4 &);
	vec4 divide(const vec4 &);
	friend vec4 operator+(vec4, const vec4 &);
	friend vec4 operator-(vec4, const vec4 &);
	friend vec4 operator*(vec4, const vec4 &);
	friend vec4 operator/(vec4, const vec4 &);
	friend vec4 operator+=(vec4 &, const vec4 &);
	friend vec4 operator-=(vec4 &, const vec4 &);
	friend vec4 operator*=(vec4 &, const vec4 &);
	friend vec4 operator/=(vec4 &, const vec4 &);
	friend bool operator==(const vec4 &, const vec4 &);
	friend bool operator!=(const vec4 &, const vec4 &);
	friend ostream &operator<<(ostream &os, const vec4 &ve);
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
};



struct mat4
{

public:
	union
	{
		float element[4 * 4];
		vec4 columns[4];
	};
	mat4() = default;
	mat4(float);
	~mat4() {}
	mat4 unitMat();
	mat4 unitMat(float);
	mat4 multiply(const mat4 &);
	mat4 tothree();
	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);
	static mat4 translation(const vec3 &translation);
	static mat4 rotation(float angle, const vec3 &axis);
	static mat4 lookat(const vec3 &cameraPosition, vec3 const &targetPosition, const vec3 & up);
	static mat4 scale(const vec3 &scale);
	friend mat4 operator*(const mat4 &, mat4);
	friend mat4 operator*= (mat4 &, mat4);

};

