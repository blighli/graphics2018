#include "vec2.h"


vec2::vec2() :x(0), y(0) {
}

vec2::vec2(float _x, float _y) :x(_x), y(_y) {
}

vec2 vec2::add(const vec2 & v2) {
	x += v2.x;
	y += v2.y;
	return *this;
}

vec2 vec2::subtract(const vec2 & v2){
	x -= v2.x;
	y -= v2.x;
	return *this;
}

vec2 vec2::multiply(const vec2 & v2) {
	x *= v2.x;
	y *= v2.y;
	return *this;
}

vec2 vec2::divide(const vec2 & v2) {
	x /= v2.x;
	y /= v2.y;
	return *this;
}

vec2 operator+(vec2 left, const vec2 & right) {
	return left.add(right);
}

vec2 operator-(vec2 left, const vec2 & right) {
	return left.subtract(right);
}

vec2 operator*(vec2 left, const vec2 & right) {
	return left.multiply(right);
}

vec2 operator/(vec2 left, const vec2 & right) {
	return left.divide(right);
}

vec2 vec2::operator+=(const vec2 & v2) {
	return this->add(v2);
}

vec2 vec2::operator-=(const vec2 & v2) {
	return this->subtract(v2);
}

vec2 vec2::operator*=(const vec2 & v2) {
	return this->multiply(v2);
}

vec2 vec2::operator/=(const vec2 & v2) {
	return this->divide(v2);
}

bool vec2::operator==(const vec2 & v2) {
	if (x != v2.x || y != v2.y)
		return false;
	return true;
}

bool vec2::operator!=(const vec2 & v2) {
	if (x != v2.x || y != v2.y)
		return true;
	return false;
}

std::ostream & operator << (std::ostream & out, const vec2 & v2) {
	out << "vec2 = (" << v2.x << ", " << v2.y << ")\n";
	return out;
}