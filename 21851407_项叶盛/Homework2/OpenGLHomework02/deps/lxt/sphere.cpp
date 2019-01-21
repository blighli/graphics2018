#include "sphere.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

const float PI = 3.1415926f;

Sphere::Sphere(float radius, float resolution) {
	int splits = PI / asin(resolution / (2 * radius));
	int layers = splits / 4 - 1;
	int totalLayers = 2 * layers + 1;
	float theta = 2 * PI / splits;

	vec3** points = new vec3*[totalLayers];
	for (int i = 0; i < totalLayers; i++) {
		points[i] = new vec3[splits];
	}
	pointCount = (totalLayers + 2) * (splits + 1);

	vec3 top(0, radius, 0);
	vec3 bottom(0, -radius, 0);

	for (int i = 0; i < layers; i++) {
		float y = radius * cos((i + 1) * theta);
		float r = radius * sin((i + 1) * theta);
		for (int j = 0; j < splits; j++) {
			float lambda = j * theta;
			vec3 p;
			p.y = y;
			p.x = r * cos(lambda);
			p.z = -r * sin(lambda);
			points[i][j] = p;
		}
	}

	for (int j = 0; j < splits; j++) {
		float lambda = j * theta;
		vec3 p;
		p.y = 0;
		p.x = radius * cos(lambda);
		p.z = -radius * sin(lambda);
		points[layers][j] = p;
	}

	for (int i = 0; i < layers; i++) {
		float y = - radius * sin((i + 1) * theta);
		float r = radius * cos((i + 1) * theta);
		for (int j = 0; j < splits; j++) {
			float lambda = j * theta;
			vec3 p;
			p.y = y;
			p.x = r * cos(lambda);
			p.z = -r * sin(lambda);
			points[layers + 1 + i][j] = p;
		}
	}

	this->points = new float[pointCount * 5];
	vector<ivec3> indices;
	for (int i = 0; i < totalLayers + 2; i++) {
		if (i == 0) {
			for (int j = 0; j < splits + 1; j++) {
				this->points[(i * (splits + 1) + j) * 5] = top.x;
				this->points[(i * (splits + 1) + j) * 5 + 1] = top.y;
				this->points[(i * (splits + 1) + j) * 5 + 2] = top.z;
				this->points[(i * (splits + 1) + j) * 5 + 3] = j * 1.0f / splits;
				this->points[(i * (splits + 1) + j) * 5 + 4] = (totalLayers - i - 1) * 1.0f / (totalLayers - 1);
			}
		} else {
			for (int j = 0; j < splits + 1; j++) {
				if (i == totalLayers + 1) {
					this->points[(i * (splits + 1) + j) * 5] = bottom.x;
					this->points[(i * (splits + 1) + j) * 5 + 1] = bottom.y;
					this->points[(i * (splits + 1) + j) * 5 + 2] = bottom.z;
				} else {
					if (j == splits) {
						this->points[(i * (splits + 1) + j) * 5] = points[i - 1][0].x;
						this->points[(i * (splits + 1) + j) * 5 + 1] = points[i - 1][0].y;
						this->points[(i * (splits + 1) + j) * 5 + 2] = points[i - 1][0].z;
					} else {
						this->points[(i * (splits + 1) + j) * 5] = points[i - 1][j].x;
						this->points[(i * (splits + 1) + j) * 5 + 1] = points[i - 1][j].y;
						this->points[(i * (splits + 1) + j) * 5 + 2] = points[i - 1][j].z;
					}
				}
				this->points[(i * (splits + 1) + j) * 5 + 3] = j * 1.0f / splits;
				this->points[(i * (splits + 1) + j) * 5 + 4] = (totalLayers - i - 1) * 1.0f / (totalLayers - 1);
				if (j < splits) {
					indices.push_back(ivec3(i * (splits + 1) + j, (i - 1) * (splits + 1) + j, (i - 1) * (splits + 1) + j + 1));
					indices.push_back(ivec3(i * (splits + 1) + j, (i - 1) * (splits + 1) + j + 1, i * (splits + 1) + j + 1));
				}
			}
		}
	}

	this->indices = new unsigned int[indices.size() * 3];
	for (int i = 0; i < indices.size(); i++) {
		this->indices[i * 3] = indices[i].x;
		this->indices[i * 3 + 1] = indices[i].y;
		this->indices[i * 3 + 2] = indices[i].z;
	}
	indiceSize = indices.size() * 3 * sizeof(unsigned int);

	for (int i = 0; i < totalLayers; i++) {
		delete[] points[i];
	}
	delete[] points;
}

Sphere::~Sphere() {
	delete[] points;
	delete[] indices;
}
