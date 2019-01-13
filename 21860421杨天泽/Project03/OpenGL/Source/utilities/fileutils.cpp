#include "fileutils.h"

std::string FileUtils::read_file(const char * filepath) {

	FILE * pfile = fopen(filepath, "rt");

	//计算文件长度
	fseek(pfile, 0, SEEK_END);
	unsigned long length = ftell(pfile);

	char * data = new char[length + 1];
	memset(data, 0, length + 1);

	fseek(pfile, 0, SEEK_SET);
	fread(data, 1, length, pfile);
	fclose(pfile);

	std::string result(data);
	delete[] data;

	return result;
}