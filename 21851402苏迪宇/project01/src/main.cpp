#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
using namespace std;


int main(int argc, char* args[]) {
	Display display(800, 600, "hello world");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5,0)),
		Vertex(glm::vec3(0,0.5,0)),
		Vertex(glm::vec3(0.5,-0.5,0))
			};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader(".\\res\\basicShader");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -3), 70.0f, 800.f / 600.f, 0.01f, 1000.f);

	float counter = 0.0;

	while (!display.m_isClosed) {
		display.clear(.3f, .4f, .5f, 1.f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.pos.x = sinCounter;
		transform.pos.z = cosCounter;
		transform.rot.x = counter * 1;
		transform.rot.y = counter * 1;
		transform.rot.z = counter * 1;

		shader.Bind();
		shader.Update(transform, camera);
		mesh.Draw();
		display.swapBuffers();

		counter += 0.01f;
	}

	return 0;
}