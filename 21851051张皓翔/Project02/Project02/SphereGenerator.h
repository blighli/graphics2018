#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "PlanetData.h"
#include "glm/glm.hpp"
class SphereGenerator
{
public:
	SphereGenerator();
	SphereGenerator(float radius,int stepnum);
	~SphereGenerator();
	std::vector<GLfloat> vertexVector;
	GLfloat *vertexArray;
	GLuint vertexNum;
	PlanetData coreData;
	GLfloat radius;
	void PrintVertexInfo();
private:
	
	int stepNum;							//纬线条数
	float stepRzx;							//两经度之间的间角 (Radians)
	float stepY;							//两纬度之间的间角 (Radians)

	float stepS;							//纹理坐标纬度间值
	float stepT;							//纹理坐标经度间值

	void SynthesisArray();
};

