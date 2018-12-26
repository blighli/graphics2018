#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "fileutils.h"
#include "Mat_Vec.h"
class Shader
{
private:
	GLuint m_ShaderID;
	const char *m_VertPath, *m_FragPath;
public:
	Shader(const char *vertexPath, const char * fragmentPath);
	~Shader();
	
	void setUniform1f(const GLchar *name, float value);
	void setUniform1i(const GLchar *name, int value);
	void setUniform2f(const GLchar *name, const vec2 &v);
	void setUniform3f(const GLchar *name, const vec3 &v);
	void setUniform4f(const GLchar *name, const vec4 &v);
	void setUniformMat4(const GLchar *name, const mat4 &mat);
	void enble() const;
	GLuint getID() const;
	void disable() const;
private:
	GLuint load();
	GLuint getUniformLocation(const GLchar *name);
};
