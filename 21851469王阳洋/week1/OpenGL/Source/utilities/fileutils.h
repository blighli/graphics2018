#pragma once



#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <string>

class FileUtils{
public:
	static std::string read_file(const char * filepath);
};


#endif