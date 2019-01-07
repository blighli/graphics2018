#pragma once
#include <glm/glm.hpp>
#include <vector>

class Model {

public:
	Model() {
		reset();
	}


	// Resets this model
	void reset() {
		scale = 1.0;

		ang.x = ang.y = ang.z = 1.0;
		pos.x = pos.y = pos.z = 0.0;
	}



	// Vertex vector
	std::vector< glm::vec3 > vertices;

	// Faces vector
	std::vector< std::vector< int > > faces;

	// Model Center 
	glm::vec3 center;

	// Model Scale
	float scale;

	// Used for model rotations
	glm::vec3 ang;

	// Used for model translations
	glm::vec3 pos;

	void setup(std::vector< glm::vec3 > &v, std::vector< std::vector< int >  > &f);

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);

	// Responsible for task 2 of this exercise
	// Writes a model out an .obj file
	void exportScheme();
private:
	// Calculates the mean vertex
	void calculateCenter();

	// Calculate the scale to be used 
	float calculateScale();
};