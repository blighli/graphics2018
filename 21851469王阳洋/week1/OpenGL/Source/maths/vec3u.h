#pragma once

#ifndef _VEC3_U_H_
#define _VEC3_U_H_

#include <iostream>

struct vec3u{
	unsigned short index[3];
	vec3u(unsigned short i1, unsigned short i2, unsigned short i3);
	vec3u();
	
	friend std::ostream & operator<<(std::ostream & os, const vec3u & v3u);
};



#endif // !_VEC3_U_H_
