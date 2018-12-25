#include "vec3.h"

vec3::vec3() :x(0), y(0),z(0) {
}

vec3::vec3(float _x, float _y,float _z) : x(_x), y(_y),z(_z) {
}

vec3::vec3(float _x, float _y, float _z, bool norm) {
	float a;
	a = sqrt(x*x + y * y + z * z);
	this->x = _x / a;
	this->y = _y / a;
	this->z = _z / a;
}

vec3 vec3::add(const vec3 & v3) {
	x += v3.x;
	y += v3.y;
	z += v3.z;
	return *this;
}

vec3 vec3::subtract(const vec3 & v3) {
	x -= v3.x;
	y -= v3.y;
	z -= v3.z;
	return *this;
}

vec3 vec3::multiply(const vec3 & v3) {
	x *= v3.x;
	y *= v3.y;
	z *= v3.z;
	return *this;
}

vec3 vec3::divide(const vec3 & v3) {
	x /= v3.x;
	y /= v3.y;
	z /= v3.z;
	return *this;
}

vec3 operator+(vec3 left, const vec3 & right) {
	return left.add(right);
}

vec3 operator-(vec3 left, const vec3 & right) {
	return left.subtract(right);
}

vec3 operator*(vec3 left, const vec3 & right) {
	return left.multiply(right);
}

vec3 operator/(vec3 left, const vec3 & right) {
	return left.divide(right);
}

vec3 operator*(vec3 left, const float & value) {
	left.x *= value;
	left.y *= value;
	left.z *= value;
	return left;
}

vec3 vec3::operator+=(const vec3 & v3) {
	return this->add(v3);
}

vec3 vec3::operator-=(const vec3 & v3) {
	return this->subtract(v3);
}

vec3 vec3::operator*=(const vec3 & v3) {
	return this->multiply(v3);
}


vec3 vec3::operator/=(const vec3 & v3) {
	return this->divide(v3);
}

bool vec3::operator==(const vec3 & v3) {
	if (x != v3.x || y != v3.y || z != v3.z)
		return false;
	return true;
}

bool vec3::operator!=(const vec3 & v3) {
	if (x != v3.x || y != v3.y || z != v3.z)
		return true;
	return false;
}

std::ostream & operator << (std::ostream & out, const vec3 & v3) {
	out << "vec3 = (" << v3.x << ", " << v3.y << ", " << v3.z << ")\n";
	return out;
}

vec3 vec3::normalize(const vec3 & v3) {
	float a;
	a = sqrt(v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
	vec3 ans;
	ans.x = v3.x / a;
	ans.y = v3.y / a;
	ans.z = v3.z / a;
	return ans;	
}

vec3 vec3::cross(const vec3 & left, const vec3 &right) {
	return vec3(left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x);
}
