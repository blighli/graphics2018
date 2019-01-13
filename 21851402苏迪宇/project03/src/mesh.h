#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	glm::vec3* GetPos() { return &pos; }

private:
	glm::vec3 pos;
};

enum MeshBufferPositions
{
	POSITION_VB,
	NUM_BUFFERS
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);

	void Draw();

	virtual ~Mesh();
protected:
private:
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};