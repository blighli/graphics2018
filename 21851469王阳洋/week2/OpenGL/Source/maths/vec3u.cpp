#include "vec3u.h"

vec3u::vec3u() {
	x = y = z = 0;
}

vec3u::vec3u(unsigned short i1, unsigned short i2, unsigned short i3) {
	x = i1;
	y = i2;
	z = i3;
}

std::ostream & operator << (std::ostream & os, const vec3u & v3u) {
	os << "index1 = " << v3u.x << " index2 = " << v3u.y
		<< " index3 = " << v3u.z << std::endl;
	return os;
}
	