#include "vec3u.h"

vec3u::vec3u() {
	for (int i = 0; i < 3; i++) {
		index[i] = 0;
	}
}

vec3u::vec3u(unsigned short i1, unsigned short i2, unsigned short i3) {
	index[0] = i1;
	index[1] = i2;
	index[2] = i3;
}

std::ostream & operator << (std::ostream & os, const vec3u & v3u) {
	os << "index1 = " << v3u.index[0] << " index2 = " << v3u.index[1] 
		<<	" index3 = " << v3u.index[2] << std::endl;
	return os;
}
	