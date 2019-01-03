#pragma once

#include <vector>
#include <GL/glew.h>

#include "../maths/maths_func.h"
#include "../graphics/buffer/buffer.h"
#include "../graphics/buffer/indexbuffer.h"
#include "../graphics/buffer/vertexarray.h"

class Model {
private:
	std::vector<vec3> m_Verticies;
	std::vector<vec3> m_Normals;
	std::vector<vec3u> m_Indicies;
	std::vector<vec2> m_Textures;

	VertexArray * m_vao;
	IndexBuffer * m_ibo;

public:
	Model();
	Model(const char *filepath);
	~Model();
	void LoadModel(const char *filepath);
	void init();
	void render();
};