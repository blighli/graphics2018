#pragma once
#include<iostream>
#include <string>
using namespace std;
class FileUtils {
public:
	static std::string read_file(const char *filepath);
	static void write_file_w(const char *filepath, const char * content);
	static void write_file_a(const char *filepath, const char * content);
	static int booleanToInt(bool boo) { return boo ? true : false; }
	//static const char *stoc(string a) { const char* c_s = a.c_str();  return c_s; }

	//static string ctos(const char * a) { const char* c_s = a; string s(c_s); return s; }
};