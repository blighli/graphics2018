#include "window.h"
#include "Vector.h"
#include "shader.h"
#include "vertexArray.h"
#include "indexBuffer.h"
#include "Model.h"
#include "Camera.h"

float WINDOWS_WIDTH = 1280.0f, WINDOWS_HEIGHT = 720.0f;
float deltaTime = 0, lastFrame = 0;
float lastX = WINDOWS_WIDTH / 2.0f, lastY = WINDOWS_HEIGHT / 2.0f;
Camera camera;

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
int main() {

	Window window = Window("Game", WINDOWS_WIDTH, WINDOWS_HEIGHT);

	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	Model myModel("source/model/dragon.obj");

	//光照
	vec3 lightPos(1.2f, 1.0f, 2.0f);

	Shader shader("source/shaders/light.vert", "source/shaders/light.frag");
	shader.enable();

	glEnable(GL_DEPTH_TEST);
	while (!window.closed()) {
		window.clear();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//处理鼠标事件
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		double xpos, ypos;

		window.getCursorPosition(xpos, ypos);
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;

		lastX = xpos;
		lastY = ypos;

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			camera.ProcessMouseMovement(xoffset, yoffset);
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			camera.ProcessMouseMovementXY(xoffset, yoffset);
		}

		mat4 projection = mat4::perspective(45.0f, (float)WINDOWS_WIDTH / (float)WINDOWS_HEIGHT, 0.1f, 100.0f);
		mat4 model = mat4::scale(vec3(0.08, 0.08, 0.08)) * mat4::translation(vec3(0, -0.5, 0));
		mat4 view = camera.getViewMatrix();

		shader.setUniformMat4("projection_matrix", projection);
		shader.setUniformMat4("model_matrix", model);
		shader.setUniformMat4("view_matrix", view);
		shader.setUniform3f("lightColor", vec3(1.0f, 1.0f, 1.0f));
		shader.setUniform3f("lightPos", lightPos);
		shader.setUniform3f("objectColor", vec3(1.0f, 0.5f, 0.31f));

		//渲染sun
		myModel.render();

		window.update();
	}
	return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	Window *win = (Window *)glfwGetWindowUserPointer(window);
	camera.ProcessMouseScroll(yoffset);
}