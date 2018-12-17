#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

#include "../maths/maths_func.h"

struct Model{
	std::vector <vec3> m_vertexes;
	std::vector <vec3> m_normals;
	std::vector<vec2> m_textures;
	std::vector<vec3u> m_vertexIndices;
	std::vector<vec3u> m_normalIndices;
	std::vector<vec3u> m_textureIndices;
};
#endif // !_MODEL_H_

