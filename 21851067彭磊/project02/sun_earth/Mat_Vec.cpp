#pragma once
#include"Mat_Vec.h"
#include <iostream>

static bool haslookat = false;
/*二维向量各操作*/
float vec2::getX() const
{
	return x;
}
float vec2::getY() const
{
	return y;
}
vec2 vec2::add(const vec2 &v2)
{
	this->x += v2.x;
	this->y += v2.y;
	return *this;
}
vec2 vec2::subtract(const vec2 &v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	return *this;
}
vec2  vec2::multiply(const vec2 &v2)
{
	this->x *= v2.x;
	this->y *= v2.y;
	return *this;
}
vec2  vec2::divide(const vec2 &v2)
{
	this->x /= v2.x;
	this->y /= v2.y;
	return *this;
}
vec2 operator+(vec2 left, const vec2 &right)
{
	return left.add(right);
}
vec2 operator-(vec2 left, const vec2 &right)
{
	return left.subtract(right);
}
vec2 operator*(vec2 left, const vec2 &right)
{
	return left.multiply(right);
}
vec2 operator/(vec2 left, const vec2 &right)
{
	return left.divide(right);
}
vec2 operator+=(vec2 &left, const vec2 &right)
{
	return left.add(right);
}
vec2 operator-=(vec2 &left, const vec2 &right)
{
	return left.subtract(right);
}
vec2 operator*=(vec2 &left, const vec2 &right)
{
	return left.multiply(right);
}
vec2 operator/=(vec2 &left, const vec2 &right)
{
	return left.divide(right);
}
bool operator==(const vec2 &left, const vec2 &right)
{
	if (left.x != right.x || left.y != right.y)
		return false;
	else
	{
		return true;
	}
}
bool operator !=(const vec2 &left, const vec2 &right)
{
	if (left == right)
		return false;
	else
	{
		return true;
	}
}
ostream &operator<<(ostream &os, const vec2 &ve)
{
	os << ve.x << " " << ve.y;
	return os;
}



/*三维向量各操作*/
float vec3::getX() const
{
	return x;
}
float vec3::getY() const
{
	return y;
}
float vec3::getZ() const
{
	return z;
}
vec3 vec3::add(const vec3 &v2)
{
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;
	return *this;
}
vec3 vec3::subtract(const vec3 &v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	return *this;
}
vec3  vec3::multiply(const vec3 &v2)
{
	this->x *= v2.x;
	this->y *= v2.y;
	this->z *= v2.z;
	return *this;
}
vec3  vec3::divide(const vec3 &v2)
{
	this->x /= v2.x;
	this->y /= v2.y;
	this->z /= v2.z;
	return *this;
}

vec3 cross(const vec3 &v1, const vec3 &v2)
{
	vec3 temp;
	temp.x = v1.y * v2.z - v1.z * v2.y;
	temp.y = v1.z * v2.x - v1.x * v2.z;
	temp.z = v1.x * v2.y - v1.y * v2.x;
	return temp;
}
vec3 normalize(const vec3 & v)
{
	vec3 temp;
	float model = sqrt(v.x*v.x + v.y*v.y + v.z *v.z);
	temp.x = v.x / model;
	temp.y = v.y / model;
	temp.z = v.z / model;
	return temp;
}
vec3 scalarMultiply(float a, const vec3 &v)
{
	vec3 temp;
	temp.x = a * v.x;
	temp.y = a * v.y;
	temp.z = a * v.z;
	return temp;
}
vec3 operator+(vec3 left, const vec3 &right)
{
	return left.add(right);
}
vec3 operator-(vec3 left, const vec3 &right)
{
	return left.subtract(right);
}
vec3 operator*(vec3 left, const vec3 &right)
{
	return left.multiply(right);
}
vec3 operator/(vec3 left, const vec3 &right)
{
	return left.divide(right);
}
vec3 operator+=(vec3 &left, const vec3 &right)
{
	return left.add(right);
}
vec3 operator-=(vec3 &left, const vec3 &right)
{
	return left.subtract(right);
}
vec3 operator*=(vec3 &left, const vec3 &right)
{
	return left.multiply(right);
}
vec3 operator/=(vec3 &left, const vec3 &right)
{
	return left.divide(right);
}
bool operator==(const vec3 &left, const vec3 &right)
{
	if (left.x != right.x || left.y != right.y || left.z != right.z)
		return false;
	else
	{
		return true;
	}
}
bool operator !=(const vec3 &left, const vec3 &right)
{
	if (left == right)
		return false;
	else
	{
		return true;
	}
}
ostream &operator<<(ostream &os, const vec3 &ve)
{
	os << ve.x << " " << ve.y << " " << ve.z;
	return os;
}
float vec3::model() const
{
	return this->x*this->x + this->y*this->y + this->z *this->z;
}
/*四维向量操作*/
float vec4::getX() const
{
	return x;
}
float vec4::getY() const
{
	return y;
}
float vec4::getZ() const
{
	return z;
}
float vec4::getW() const
{
	return w;
}
vec4 vec4::add(const vec4 &v2)
{
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;
	this->w += v2.w;
	return *this;
}
vec4 vec4::subtract(const vec4 &v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	this->w -= v2.w;
	return *this;
}
vec4  vec4::multiply(const vec4 &v2)
{
	this->x *= v2.x;
	this->y *= v2.y;
	this->z *= v2.z;
	this->w *= v2.w;
	return *this;
}
vec4  vec4::divide(const vec4 &v2)
{
	this->x /= v2.x;
	this->y /= v2.y;
	this->z /= v2.z;
	this->w /= v2.w;
	return *this;
}
vec4 operator+(vec4 left, const vec4 &right)
{
	return left.add(right);
}
vec4 operator-(vec4 left, const vec4 &right)
{
	return left.subtract(right);
}
vec4 operator*(vec4 left, const vec4 &right)
{
	return left.multiply(right);
}
vec4 operator/(vec4 left, const vec4 &right)
{
	return left.divide(right);
}
vec4 operator+=(vec4 &left, const vec4 &right)
{
	return left.add(right);
}
vec4 operator-=(vec4 &left, const vec4 &right)
{
	return left.subtract(right);
}
vec4 operator*=(vec4 &left, const vec4 &right)
{
	return left.multiply(right);
}
vec4 operator/=(vec4 &left, const vec4 &right)
{
	return left.divide(right);
}
bool operator==(const vec4 &left, const vec4 &right)
{
	if (left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w)
		return false;
	else
	{
		return true;
	}
}
bool operator !=(const vec4 &left, const vec4 &right)
{
	if (left == right)
		return false;
	else
	{
		return true;
	}
}
ostream &operator<<(ostream &os, const vec4 &ve)
{
	os << ve.x << " " << ve.y << " " << ve.z << " " << ve.w;
	return os;
}
/*矩阵操作*/

mat4::mat4(float ele)
{
	columns[0] = vec4(ele, 0, 0, 0);
	columns[1] = vec4(0, ele, 0, 0);
	columns[2] = vec4(0, 0, ele, 0);
	columns[3] = vec4(0, 0, 0, ele);;
}
mat4 mat4::unitMat()
{
	columns[0] = vec4(1, 0, 0, 0);
	columns[1] = vec4(0, 1, 0, 0);
	columns[2] = vec4(0, 0, 1, 0);
	columns[3] = vec4(0, 0, 0, 1);
	return *this;
}
mat4 mat4::multiply(const mat4 &rig)
{
	mat4 result;
	int nu = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vec4 right(rig.element[j], rig.element[j + 4], rig.element[j + 8], rig.element[j + 12]);//取出变换矩阵行元素
			vec4 res = columns[i] * right;                                                          //向量乘
			result.element[nu] = res.getX() + res.getY() + res.getZ() + res.getW();                                     //得到结果矩阵对应元素
			nu++;
		}
	}
	*this = result;
	return *this;
}
mat4 operator*(const mat4 &left, mat4 right)
{
	return right.multiply(left);
}
mat4 operator*= (mat4 &left, mat4 right)
{
	return left = right.multiply(left);
}
mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 temp;
	temp.columns[0] = vec4(2 / (right - left), 0, 0, 0);
	temp.columns[1] = vec4(0, 2 / (top - bottom), 0, 0);
	temp.columns[2] = vec4(0, 0, -2 / (far - near), 0);
	temp.columns[3] = vec4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
	return temp;
}
mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 temp;
	float r_fov = fov;
	temp.columns[0] = vec4(1 / (aspectRatio*tan(r_fov / 2)), 0, 0, 0);
	temp.columns[1] = vec4(0, 1 / tan(r_fov / 2), 0, 0);
	temp.columns[2] = vec4(0, 0, -(far + near) / (far - near), -1);
	temp.columns[3] = vec4(0, 0, -(2 * far*near) / (far - near), 0);
	return temp;
}
mat4 mat4::translation(const vec3 &translation)
{
	mat4 temp;
	temp.unitMat();
	temp.columns[3] = vec4(translation.getX(), translation.getY(), translation.getZ(), 1);

	return temp;
}
mat4 mat4::rotation(float angle, const vec3 &axis)
{
	vec3 temp1 = normalize(axis);
	mat4 temp;
	float x = temp1.getX(), y = temp1.getY(), z = temp1.getZ();
	float r_angle = angle;
	float s = sin(r_angle), c = cos(r_angle);
	temp.columns[0] = vec4(x*x*(1 - c) + c, x*y*(1 - c) + z * s, x*z*(1 - c) - y * s, 0);
	temp.columns[1] = vec4(x*y*(1 - c) - z * s, y*y*(1 - c) + c, y*z*(1 - c) + x * s, 0);
	temp.columns[2] = vec4(x*z*(1 - c) + y * s, y*z*(1 - c) - x * s, z*z*(1 - c) + c, 0);
	temp.columns[3] = vec4(0, 0, 0, 1);
	return temp;
}


mat4 mat4::scale(const vec3 &scale)
{
	mat4 temp;
	temp.columns[0] = vec4(scale.getX(), 0, 0, 0);
	temp.columns[1] = vec4(0, scale.getY(), 0, 0);
	temp.columns[2] = vec4(0, 0, scale.getZ(), 0);
	temp.columns[3] = vec4(0, 0, 0, 1);
	return temp;
}
mat4 mat4::unitMat(float a)
{
	columns[0] = vec4(a, 0, 0, 0);
	columns[1] = vec4(0, a, 0, 0);
	columns[2] = vec4(0, 0, a, 0);
	columns[3] = vec4(0, 0, 0, a);
	return *this;
}

mat4 mat4::lookat(const vec3 &cameraPosition, const vec3 &targetPosition, const vec3 & up)
{
	vec3 cameraDirection = normalize(cameraPosition - targetPosition );
	
	vec3 cameraRight = normalize(cross(up , cameraDirection ));
	vec3 cameraUp = cross(cameraDirection,cameraRight );
	mat4 left, right;

	left.columns[0] = vec4(cameraRight.getX(), cameraUp.getX(), cameraDirection.getX(), 0);
	left.columns[1] = vec4(cameraRight.getY(), cameraUp.getY(), cameraDirection.getY(), 0);
	left.columns[2] = vec4(cameraRight.getZ(), cameraUp.getZ(), cameraDirection.getZ(), 0);
	left.columns[3] = vec4(0, 0, 0, 1);
	right = translation(vec3(-1 * cameraPosition.getX(), -1*cameraPosition.getY(), -1 * cameraPosition.getZ()));
	mat4 result= left * right;
	

	return result;

}
mat4 mat4::tothree()
{
	columns[0].w = 0;
	columns[1].w = 0;
	columns[2].w = 0;

	columns[3] = vec4(0, 0, 0, 1);
	return *this;
}
