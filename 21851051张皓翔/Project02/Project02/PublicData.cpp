#pragma once

#include "PublicData.h"

GLfloat lastTime = 0;
GLfloat deltaTime = 0.1;
GLuint planetProgram = 0;
GLuint starProgram = 0;
SphereGenerator planetEntities[10];

ShaderInfo planetShaders[] = {
   {GL_VERTEX_SHADER,"PlanetVertexShader.vert",0},
   {GL_FRAGMENT_SHADER,"PlanetFragmentShader.frag",0},
	{GL_NONE,"xxx",0}
};

ShaderInfo starShaders[] = {
	{GL_VERTEX_SHADER , "starVertexShader.vert",0 },
	{GL_FRAGMENT_SHADER, "starFragmentShader.frag", 0},
	{GL_NONE, "xxx", 0}
};
