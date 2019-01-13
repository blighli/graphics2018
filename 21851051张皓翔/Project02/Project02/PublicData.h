#pragma once
#include "MyShaderLoader.h"
#include "SphereGenerator.h"

enum { sun = 0, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};
enum { vPosition = 0, textCoord,  normal};

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;
const int DAY_PER_SECOND = 1;


extern SphereGenerator planetEntities[];

extern GLfloat lastTime;
extern GLfloat deltaTime;
extern GLuint planetProgram;
extern GLuint starProgram;



extern ShaderInfo planetShaders[];
extern ShaderInfo starShaders[];

