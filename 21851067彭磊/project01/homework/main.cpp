#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mat_Vec.h"
#include "shader.h"
#include "mywindow.h"
#include "stb_image.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "object.h"

using namespace std;
float toRadians(float degrees)
{
	return degrees * M_PI / 180.0f;
}
float pitch = 0.0;
float Yaw = -90.0;
int main()
{
	Window window("homework", 1980, 1050);
	

	Shader shader2("basic.vert", "basic.frag");

	Object cube("dragon.obj");
	VertexArray vao;
	IndexBuffer ibo(&(cube.indices[0].x), cube.indices.size() *3);

	vao.addBuffer(new Buffer(&cube.vertices[0].Position.x, cube.vertices.size()*sizeof(Vertex), 3), 0, sizeof(Vertex),(void*)offsetof(Vertex, Position));      //把顶点位置数据传入vao， 在索引0处
	vao.addBuffer(new Buffer(&cube.vertices[0].Position.x, cube.vertices.size() * sizeof(Vertex), 3), 1, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	vec3 cameraPos(0.0f, 0.0f, 3.0f);
	vec3 cameraFront(0.0f, 0.0f, -1.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	cameraFront = normalize(cameraFront);
	

	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间

	
	float y1 = 0.0;
	double previousTime = glfwGetTime();
	int frameCount = 0;
	while (!window.closed())
	{

		window.clear();
		

		float curFrame = glfwGetTime();
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;
		cameraFront = window.getFront();

		
		float cameraSpeed = 5.5f * deltaTime;
		if (window.isKeyPressed(GLFW_KEY_W))
		{
			cameraPos += scalarMultiply(cameraSpeed, cameraFront);
		}
		if (window.isKeyPressed(GLFW_KEY_S))
		{
			cameraPos -= scalarMultiply(cameraSpeed, cameraFront);
		}
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			cameraPos -= scalarMultiply(cameraSpeed, normalize(cross(cameraFront, cameraUp)));
		}
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			cameraPos += scalarMultiply(cameraSpeed, normalize(cross(cameraFront, cameraUp)));
		}
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getWindow(), true);
		}
		if (window.isKeyPressed(GLFW_KEY_SPACE))
		{
			cameraPos.y += 0.009;
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			cameraPos.y -= 0.009;
		}
		mat4 model =  mat4::scale(vec3(0.2f, 0.2f, 0.2f)) /** mat4::rotation(glfwGetTime(), normalize(vec3(1.0,1.0,0.0)))*/;
		mat4 view = mat4::lookat(cameraPos, cameraPos + cameraFront, cameraUp);
		mat4 projection = mat4::perspective(toRadians(window.getFov()), (float)window.getWidth() / (float)window.getHeight(), 1.0f, 100.0f);
		shader2.enble();
		shader2.setUniform3f("objectColor", vec3(1.0f, 0.5f, 0.3f));
		shader2.setUniform3f("lightColor", vec3(1.0f, 1.0f, 1.0f));
		shader2.setUniform3f("viewPos", cameraPos);
		shader2.setUniform3f("lightPos", vec3(0.0f, 0.0f, -2.0f));
		shader2.setUniformMat4("projection_matrix", projection);
		shader2.setUniformMat4("view_matrix", view);
		shader2.setUniformMat4("model_matrix", model);
		
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(),GL_UNSIGNED_SHORT, 0);
		
		window.update();

	}

	glfwTerminate();
	return 0;
}
