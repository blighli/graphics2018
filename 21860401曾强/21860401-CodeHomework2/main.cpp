#include <iostream>
#include <math.h>
#include <functional>
#include <algorithm>
#include <map>

#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader_s.h"
#include "stb_image.h"
#include "Camera.h"

using namespace std;

unsigned int loadTexture(char const * path);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//当前帧与上一帧的时间差
float deltaTime = 0.0f;
//上一帧的时间
float lastFrame = 0.0f;

//鼠标最后的X,Y坐标
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//构建shader程序
	//构建顶点shader
	Shader earthMoonShader("3.3.shader_vs.cpp", "3.3.shader_fs.cpp");
	Shader sunShader("3.3.light_vs.cpp", "3.3.light_fs.cpp");

	//太阳为光源
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f)
	};

	earthMoonShader.use();
	earthMoonShader.setInt("material.diffuse", 0);
	earthMoonShader.setInt("material.specular", 1);
	earthMoonShader.setFloat("material.shininess", 0.5 * 128.0f);

	//散发白光
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	// Directional light
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);

	//太阳为点光源
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform3f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].linear"), 0.7f);
	glUniform1f(glGetUniformLocation(earthMoonShader.Program, "pointLights[0].quadratic"), 1.8f);

	//开启鼠标捕捉
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//设置鼠标回调函数
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	Model sunModel("src/sun.obj");
	Model earthModel("src/earth.obj");
	Model moonModel("src/moon.obj");

	GLfloat earthRotate = 0.0f;
	GLfloat moonRotate = 0.0f;

	GLfloat earthRevolute = 0.0f;
	GLfloat moonRevolute = 0.0f;

	glEnable(GL_DEPTH_TEST);

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		//清除颜色缓冲和深度缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sunShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		sunShader.setMat4("projection", projection);
		sunShader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0);
		//缩放
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		//自传
		model = glm::rotate(model, (float)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
		sunShader.setMat4("model", model);
		sunShader.setMat4("view", view);
		sunModel.Draw(sunShader);

		//earth和moon受太阳光源影响，shader不同
		earthMoonShader.use();
		earthMoonShader.setMat4("projection", projection);
		earthMoonShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(earthRevolute), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(earthRotate), glm::vec3(1.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0033f, 0.0033f, 0.0033f));
		//自传
		model = glm::rotate(model, (float)glfwGetTime() * 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		earthMoonShader.setMat4("model", model);
		earthModel.Draw(earthMoonShader);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(earthRevolute), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model,
			glm::vec3(5.0f + 1.8f * cos(glm::radians(moonRevolute)),
				0.0f,
				0.0f + 1.8f * sin(glm::radians(moonRevolute))));
		model = glm::rotate(model, glm::radians(moonRotate), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		//自传
		model = glm::rotate(model, (float)glfwGetTime() * 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		earthMoonShader.setMat4("model", model);
		moonModel.Draw(earthMoonShader);

		earthRotate += 0.0001f;
		moonRotate += 0.00015f;

		earthRevolute += 2.5f / 500;
		moonRevolute += 4.5f / 500;

		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

//是否为鼠标第一次进入
bool firstMouse = true;
//接受鼠标的操作
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

//滚轮回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	} else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
