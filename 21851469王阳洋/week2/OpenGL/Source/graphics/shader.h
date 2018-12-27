#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include "../maths/maths_func.h"
#include "../utilities/fileutils.h"

class Shader {
private:
	GLuint m_ShaderID;
	const char * m_VertPath, *m_FragPath;

public:
	//传入着色器的文件路径
	Shader(const char * vertexPath, const char * fragmentPath);
	GLuint load();
	void enable() const;
	void disable() const;
	GLuint getID();

	GLint getUniformLocation(const GLchar * name);
	void setUniform1f(const GLchar * name, float value);
	void setUniform1i(const GLchar * name, int value);
	void setUniform2f(const GLchar * name, const vec2 & v);
	void setUniform3f(const GLchar * name, const vec3 & v);
	void setUniform4f(const GLchar * name, const vec4 & v);
	void setUniformMat4(const GLchar * name, const mat4 & matrix);

};

#endif // !_SHADER_H_
