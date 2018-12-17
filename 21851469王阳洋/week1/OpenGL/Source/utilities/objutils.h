#pragma once

#ifndef _OBJUTILS_H_
#define _OBJUTILS_H_

#include "../model/model.h"

class ObjUtils {
public:
	static Model readObj(const char * objpath);
};

#endif