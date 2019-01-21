#include <vgl.h>

#include <iostream>
#include <cmath>

#include "ModelLoader.h"
#include "Shapes.h"
#include "Texture.h"
#include "Camera.h"

GLFWcursor* roateCursor;
bool isPressing = false;
bool isYaw = false;
bool isPitch = false;
double lastPosition[2];
double offsetScroll[2] = { 0.0f, 0.0f };

GLFWwindow* window;
Shader* shader;
Shader* lightShader;
Camera camera;
const int NUM_OF_SHAPE = 4;
Shape* shapes[NUM_OF_SHAPE];
const double minDeltaRoate = 5;
const double maxDeltaRoate = 10;
//旋转速度 1.0为正常速度
float roateSpeed = 1.0F;
float lrbtnf[6] = { -4.0, 4.0, -4.0, 4.0, -4.0, 4.0 };

void initGLFW();
void initOpenGL();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W)
		if (action == GLFW_PRESS)
			camera.moveUp(0.5);
		else if (action == GLFW_REPEAT)
			camera.moveUp(0.2);
	if (key == GLFW_KEY_S)
		if (action == GLFW_PRESS)
			camera.moveDown(0.5);
		else if (action == GLFW_REPEAT)
			camera.moveDown(0.2);
	if (key == GLFW_KEY_A)
		if (action == GLFW_PRESS)
			camera.moveLeft(0.5);
		else if (action == GLFW_REPEAT)
			camera.moveLeft(0.2);
	if (key == GLFW_KEY_D)
		if (action == GLFW_PRESS)
			camera.moveRight(0.5);
		else if (action == GLFW_REPEAT)
			camera.moveRight(0.2);

}
static void mouseBtn_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1) {
		if (action == GLFW_PRESS) {
			glfwSetCursor(window, roateCursor);
			isPressing = true;
			glfwGetCursorPos(window, &lastPosition[0], &lastPosition[1]);
		}
		else if (action == GLFW_RELEASE) {
			glfwSetCursor(window, NULL);
			isPressing = false;
			isYaw = false;
			isPitch = false;
		}
	}
}
static void cursorPos_callback(GLFWwindow* window, double x, double y) {
	if (isPressing) {
		double deltaX = x - lastPosition[0];
		double deltaY = y - lastPosition[1];
		if (std::abs(deltaX) >= minDeltaRoate && !isPitch) {
			isYaw = true;
			lastPosition[0] = x;
			camera.yaw(deltaX * 0.002);
		}
		if (std::abs(deltaY) >= minDeltaRoate && !isYaw) {
			isPitch = true;
			lastPosition[1] = y;
			camera.pitch(deltaY * 0.002);
		}
	}
}
const float outerLrbtnf[6] = { -10.0, 10.0, -10.0, 10.0, -20.0, 20.0 };
const float innerLrbtnf[6] = { -0.5, 0.5, -0.5, 0.5, -0.5, 0.5 };
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {	
	camera.moveForward(yoffset);
}

int main()
{
	initGLFW();
	initOpenGL();
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < NUM_OF_SHAPE; i++) {
			shapes[i]->prepare();
			shader->setMVP(shapes[i]->getModel(), camera.getViewMat(), camera.getProjectMat());
			shapes[i]->draw();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	for (int i = 0; i < NUM_OF_SHAPE; i++) {
		delete shapes[i];
	}
	delete shader;
	delete lightShader;
	exit(EXIT_SUCCESS);
	return 0;
}

void initGLFW()
{
	if (GLFW_FALSE == glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	int width = 720, height = 720;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(width, height, "OpenGLHomework01", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseBtn_callback);
	glfwSetCursorPosCallback(window, cursorPos_callback);
	glfwSetScrollCallback(window, scroll_callback);
	roateCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwMakeContextCurrent(window);
	gl3wInit();
	//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
}
void initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	lightShader = new LightShader();
	shader = new Shader();
	shapes[0] = new Sun();
	shapes[1] = new Mercury();
	shapes[2] = new Venus();
	shapes[3] = new Earth();
	for (int i = 0; i < NUM_OF_SHAPE; i++) {
		shapes[i]->init(lightShader);
	}
}