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

#include <vector>

using namespace std;
float toRadians(float degrees)
{
	return degrees * M_PI / 180.0f;
}
vector<vec3> points;
int main()
{
	Window window("game", 800, 600);
	float skyboxVertices[] = {
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
	vector<std::string> faces1
	{
		"skybox2//right.jpg",
			"skybox2//left.jpg",
			"skybox2//up.jpg",
			"skybox2//down.jpg",
			"skybox2//back.jpg",
			"skybox2//front.jpg"
	};


	GLuint textureID1;
	glGenTextures(1, &textureID1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID1);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces1.size(); i++)
	{
		unsigned char *data = stbi_load(faces1[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces1[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	VertexArray skybox;
	Buffer *skyboxvbo = new Buffer(skyboxVertices, 36 * 3*sizeof(float), 3);
	skybox.addBuffer(skyboxvbo, 0, 3*sizeof(float), 0);
	Shader skyboxshader("skybox.vert", "skybox.frag");
	Shader earthshader("basic.vert", "basic.frag");
	
	
	GLuint m_TextureID;
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Object cube("sun2.obj");
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data1;
	data1 = stbi_load("sun.jpg", &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);  //图片载入到纹理对象上
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);
	


	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(Vertex), &cube.vertices[0].Position.x, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * 3*sizeof(unsigned short), &(cube.indices[0].x), GL_STATIC_DRAW);

	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);







	Object earth("newearth.obj");
	stbi_set_flip_vertically_on_load(true);
	GLuint m_TextureID1;
	glGenTextures(1, &m_TextureID1);
	glBindTexture(GL_TEXTURE_2D, m_TextureID1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	data1 = stbi_load("earth.jpg", &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);  //图片载入到纹理对象上
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	unsigned int VBO1, VAO1, EBO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);


	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(Vertex), &earth.vertices[0].Position.x, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, earth.indices.size() * 3 * sizeof(unsigned short), &(earth.indices[0].x), GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	vec3 cameraPos(0.0f, 0.0f, 3.0f);
	vec3 cameraFront(0.0f, 0.0f, -1.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	cameraFront = normalize(cameraFront);
	

	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间

	glEnable(GL_DEPTH_TEST);
	float factor = 1.0;
	bool day = true;
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
			cameraPos += scalarMultiply(cameraSpeed , vec3(0, 1, 0));
		}



		mat4 model, view, projection;
		projection = mat4::perspective(toRadians(window.getFov()), (float)window.getWidth() / (float)window.getHeight(), 1.0f, 100.0f);
		//绘制天空盒
		view = mat4::lookat(cameraPos, cameraPos + cameraFront, cameraUp)*mat4::scale(vec3(5.0f, 5.0f, 5.0f));
		view.tothree();
		glDepthMask(GL_FALSE);
		
		skyboxshader.enble();
		skyboxshader.setUniformMat4("view", view);
		skyboxshader.setUniformMat4("projection", projection);
		skyboxshader.setUniform1i("skybox1", 0);
	
		skyboxshader.setUniform1f("factor", factor);
		skybox.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID1);

		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
		

	

		//绘制太阳
		view = mat4::lookat(cameraPos, cameraPos + cameraFront, cameraUp);
		earthshader.enble();
		earthshader.setUniform1i("ourTexture", 0);
		earthshader.setUniformMat4("projection_matrix", projection);
		earthshader.setUniformMat4("view_matrix", view);
		earthshader.setUniform1f("increase", 1.7f);
		model.unitMat();
		
		earthshader.setUniformMat4("model_matrix", model);
		
	
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, cube.indices.size() * 3,GL_UNSIGNED_SHORT, 0);
		


		//绘制地球
		earthshader.enble();

		model = mat4::translation(vec3(sin(toRadians(glfwGetTime())*30.0f)*3.0f,0.0,cos(toRadians(glfwGetTime())*30.0f)*3.0f))* mat4::rotation(toRadians(glfwGetTime())*100.0f, normalize(vec3(0.0f, 1.0f, 0.0f))) * mat4::scale(vec3(0.1,0.1,0.1));
		earthshader.setUniformMat4("model_matrix", model);
		
		earthshader.setUniform1f("increase", 0.5f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID1);
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
		glDrawElements(GL_TRIANGLES, earth.indices.size() * 3, GL_UNSIGNED_SHORT, 0);
		
		window.update();
		
	}

	glfwTerminate();
	return 0;
}
