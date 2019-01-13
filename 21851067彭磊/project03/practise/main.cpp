
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mat_Vec.h"
#include "shader.h"
#include "mywindow.h"
#include "stb_image.h"
#include "buffer/texturebuffer.h"
#include "buffer/indexbuffer.h"
#include "buffer/buffer.h"
#include "buffer/vertexarray.h"
#include "object.h"
#include <vector>
#include <string>

using namespace std;
float skyboxVertices[36 * 3] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};



vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	vec3 cubePositions[] = {
	vec3(0.0f,  0.0f,  0.0f),
	vec3(2.0f,  5.0f, -15.0f),
	vec3(-1.5f, -2.2f, -2.5f),
	vec3(-3.8f, -2.0f, -12.3f),
	vec3(2.4f, -0.4f, -3.5f),
	vec3(-1.7f,  3.0f, -7.5f),
	vec3(1.3f, -2.0f, -2.5f),
	vec3(1.5f,  2.0f, -2.5f),
	vec3(1.5f,  0.2f, -1.5f),
	vec3(-1.3f,  1.0f, -1.5f)
	};

	/*三角形*/
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	vector<std::string> faces
	{
		"skybox//right.png",
			"skybox//left.png",
			"skybox//top.png",
			"skybox//bottom.png",
			"skybox//back.png",
			"skybox//front.png"
	};
	

	Window window("play", 800, 600);
	

	//天空盒纹理载入
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		

	Shader lightshader("cube.vert", "cube.frag");
	Shader lampshader("lightsource.vert", "lightsource.frag");
	Shader skyboxshader("skybox.vert", "skybox.frag");




	VertexArray cubevao, lampvao, skybox;
	Buffer *cubevbo = new Buffer(vertices, 36 * 8, 3);
	Buffer *cubevboN = new Buffer(vertices, 36 * 8, 3);
	Buffer *lampvbo = new Buffer(vertices, 36 * 8, 3);
	Texture *cubetexture1 = new Texture("container2.png", 2, 0);
	Texture *cubetexture2 = new Texture("container2_specular.png", 2, 1);
	//立方体数据灌入
	cubevao.addBuffer(cubevbo, 0, 8, 0);                                  //索引，步长，偏移量，顶点位置
	cubevao.addBuffer(cubevboN, 1, 8, 3);                                 //法向量
	cubevao.addTexture(cubetexture1, 2, 8, 6);                             //纹理
	cubevao.addTexture(cubetexture2, 2, 8, 6);
	//光源立方体数据灌入
	lampvao.addBuffer(lampvbo, 0, 8, 0);

	//天空盒数据灌入
	Buffer *skyboxvbo = new Buffer(skyboxVertices, 36 * 3, 3);           
	skybox.addBuffer(skyboxvbo, 0, 3, 0);

	

	glEnable(GL_DEPTH_TEST);
	vec3 cameraPos(0.0f, 0.0f, 3.0f);
	vec3 cameraFront(0.0f, 0.0f, 0.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);

	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间
	

	while (!window.closed())
	{

		window.clear();


		cameraFront = window.getFront();

		float curFrame = glfwGetTime();
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;



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
		if (window.isKeyPressed(GLFW_KEY_SPACE))
		{
			cameraPos += scalarMultiply (cameraSpeed, vec3(0, 1, 0));
		}

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getWindow(), true);
		}
		mat4 model, view, projection;
		
		//绘制天空盒
		view.unitMat();
		view = mat4::lookat(cameraPos, cameraPos + cameraFront, cameraUp)*mat4::scale(vec3(5.0f,5.0f,5.0f));
		view.tothree();
		projection = mat4::perspective(toRadians(window.getFov()), (float)window.getWidth() / (float)window.getHeight(), 1.0f, 100.0f);
		glDepthMask(GL_FALSE);
		skyboxshader.enble();
		skyboxshader.setUniformMat4("view", view);
		skyboxshader.setUniformMat4("projection", projection);
		skybox.bind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		skybox.unbind();
		glDepthMask(GL_TRUE);


		//绘制立方体，被光照物体
		//float yaxis = sin(glfwGetTime())*3.0f;    // 光源上下移动
		lightPos = cameraPos;
		lightshader.enble();
		model = mat4::scale(vec3(1.0f, 1.0f, 1.0f));
		view = mat4::lookat(cameraPos, cameraPos + cameraFront, cameraUp);
		vec3 lightColor(1.0f,1.0f,1.0f);
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		vec3 diffuseColor = lightColor * vec3(1.5f, 1.5f, 1.5f);
		vec3 ambientColor = lightColor * vec3(0.1f, 0.1f, 0.1f);
		
		lightshader.setUniform3f("viewPos", cameraPos);
		lightshader.setUniform1i("material.diffuse", 0);
		lightshader.setUniform1i("material.specular", 1);
		lightshader.setUniform1f("material.shininess", 32.0f);

		lightshader.setUniform3f("light.position", lightPos);
		lightshader.setUniform3f("light.direction", cameraFront);
		lightshader.setUniform1f("light.cutOff", cos(toRadians(5.5f)));
		lightshader.setUniform1f("light.outerCutOff", cos(toRadians(10.5f)));
		lightshader.setUniform3f("light.ambient", ambientColor);
		lightshader.setUniform3f("light.diffuse", diffuseColor);
		lightshader.setUniform3f("light.specular", vec3(1.0f, 1.0f, 1.0f));
		lightshader.setUniform1f("light.constant", 1.0f);
		lightshader.setUniform1f("light.linear", 0.09f);
		lightshader.setUniform1f("light.quadratic", 0.032f);
		lightshader.setUniformMat4("view", view);
		lightshader.setUniformMat4("projection", projection);
		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			model = mat4::translation(cubePositions[i])*mat4::rotation(toRadians(glfwGetTime()*300.0f), vec3(1.0,0.0,0.0));
			lightshader.setUniformMat4("model", model);
			cubevao.bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			cubevao.unbind();
		}
		


		

		//绘制光源
		lampshader.enble();
		model = mat4::translation(lightPos)*mat4::scale(vec3(0.2f, 0.2f, 0.2f));
		lampshader.setUniformMat4("view", view);
		lampshader.setUniformMat4("projection", projection);
		lampshader.setUniformMat4("model", model);
		lampvao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lampvao.unbind();
		window.update();
		
	}

	glfwTerminate();
	return 0;
}
