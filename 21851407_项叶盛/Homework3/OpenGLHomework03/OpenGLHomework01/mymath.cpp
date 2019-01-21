#include "linmath.h"

#define LINMATH_H_DEFINE_SVECI_I(n) \
Vec##n##i::Vec##n##i(int s[]){ for (int i = 0; i < n; i++) x[i] = s[i]; } \
Vec##n##i::~Vec##n##i() {}

LINMATH_H_DEFINE_SVECI_I(3)
LINMATH_H_DEFINE_SVECI_I(4)


#define LINMATH_H_DEFINE_SVEC_I(n) \
Vec##n::Vec##n(float s[]){ for (int i = 0; i < n; i++) x[i] = s[i]; } \
Vec##n::~Vec##n() {} \
float* Vec##n::data(){ return &x[0]; } 

LINMATH_H_DEFINE_SVEC_I(2)
LINMATH_H_DEFINE_SVEC_I(3)
LINMATH_H_DEFINE_SVEC_I(4)
