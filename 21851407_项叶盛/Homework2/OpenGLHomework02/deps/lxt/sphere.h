#pragma once

class Sphere {
public:
	Sphere(float radius, float resolution);
	~Sphere();
	float* points;
	int pointCount;
	unsigned int* indices;
	int indiceSize;
};