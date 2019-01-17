#pragma once
#include <vgl.h>
#include "linmath.h"

class Shader {
public:
	Shader();
	virtual ~Shader();
	GLuint program, vertex_shader, fragment_shader;
	GLuint MVP_location[3];
	mat4x4 MVP[3];
	GLuint vpos_location;
	void setMVP(mat4x4 model, mat4x4 view, mat4x4 projection);
};
class LightShader : public Shader{
public:
	LightShader();
	virtual ~LightShader();
};