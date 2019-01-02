#include "vec4.h"

vec4::vec4():x(0), y(0), z(0), w(0) {
}

vec4::vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {
}

vec4 vec4::add(const vec4 & v4) {
	x += v4.x;
	y += v4.y;
	z += v4.z;
	w += v4.w;
	return *this;
}

vec4 vec4::subtract(const vec4 & v4) {
	x -= v4.x;
	y -= v4.x;
	z -= v4.z;
	w -= v4.w;
	return *this;
}

vec4 vec4::multiply(const vec4 & v4) {
	x *= v4.x;
	y *= v4.y;
	z *= v4.z;
	w *= v4.w;
	return *this;
}

vec4 vec4::divide(const vec4 & v4) {
	x /= v4.x;
	y /= v4.y;
	z /= v4.z;
	w /= v4.w;
	return *this;
}

vec4 operator+(vec4 left, const vec4 & right) {
	return left.add(right);
}

vec4 operator-(vec4 left, const vec4 & right) {
	return left.subtract(right);
}

vec4 operator*(vec4 left, const vec4 & right) {
	return left.multiply(right);
}

vec4 operator/(vec4 left, const vec4 & right) {
	return left.divide(right);
}

vec4 vec4::operator+=(const vec4 & v4) {
	return this->add(v4);
}

vec4 vec4::operator-=(const vec4 & v4) {
	return this->subtract(v4);
}

vec4 vec4::operator*=(const vec4 & v4) {
	return this->multiply(v4);
}

vec4 vec4::operator/=(const vec4 & v4) {
	return this->divide(v4);
}

bool vec4::operator==(const vec4 & v4) {
	if (x != v4.x || y != v4.y || z != v4.z)
		return false;
	return true;
}

bool vec4::operator!=(const vec4 & v4) {
	if (x != v4.x || y != v4.y || z != v4.z)
		return true;
	return false;
}

std::ostream & operator << (std::ostream & out, const vec4 & v4) {
	out << "vec4 = (" << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.w <<")\n";
	return out;
}

vec4 vec4::LineInterpolation(const vec4 & left, const vec4 & right, float a) {
	vec4 result;
	float b = 1 - a;
	result.x = left.x * b + right.x * a;
	result.y = left.y * b + right.y * a;
	result.z = left.z * b + right.z * a;
	result.w = left.w * b + right.w * a;
	return result;
}
