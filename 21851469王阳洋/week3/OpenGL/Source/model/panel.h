#pragma once

#include "../graphics/buffer/vertexarray.h"
#include "../maths/maths_func.h"

class Panel {
private:
	VertexArray m_vao;

	vec3 position[4] = {
		vec3(50,0,50),
		vec3(50,0,-50),
		vec3(-50,0,50),
		vec3(-50,0,-50)
	};

	vec3 normal[4] = {
		vec3(0, 1, 0),
		vec3(0, 1, 0),
		vec3(0, 1, 0),
		vec3(0, 1, 0)
	};

public:
	Panel() {
		m_vao.addBuffer(new Buffer(&position[0].x, 4 * 3, 3), 0);
		m_vao.addBuffer(new Buffer(&normal[0].x, 4*3, 3), 1);
	}

	void render() {
		m_vao.bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_vao.unbind();
	}
};