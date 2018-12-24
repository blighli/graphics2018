#include "window.h"
#include "vector.h"
#include "shader.h"
#include "Camera.h"

float WINDOWS_WIDTH = 1280.0f, WINDOWS_HEIGHT = 720.0f;
float deltaTime = 0, lastFrame = 0;
float lastX = WINDOWS_WIDTH / 2.0f, lastY = WINDOWS_HEIGHT / 2.0f;
Camera camera;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main() {

	Window window = Window("Game", WINDOWS_WIDTH, WINDOWS_HEIGHT);

	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	Shader shader("basic.vert", "basic.frag");
	shader.enable();


	glEnable(GL_DEPTH_TEST);
	while (!window.closed()) {
		window.clear();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		double xpos, ypos;

		window.getCursorPosition(xpos, ypos);
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			camera.ProcessMouseMovementXY(xoffset, yoffset);
		}

		mat4 projection = mat4::perspective(45.0f, (float)WINDOWS_WIDTH / (float)WINDOWS_HEIGHT, 0.1f, 100.0f);
		mat4 model = mat4::scale(vec3(0.5, 0.5, 0.5));
		mat4 view = camera.getViewMatrix();

		shader.setUniformMat4("projection_matrix", projection);
		shader.setUniformMat4("model_matrix", model);
		shader.setUniformMat4("view_matrix", view);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		window.update();
	}
	return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	Window *win = (Window *)glfwGetWindowUserPointer(window);
	camera.ProcessMouseScroll(yoffset);
}