#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

#include <iostream>
#include <cmath>

#include "Shapes.h"

GLFWcursor* roateCursor;
bool isPressing = false;
double lastPosition[2];
double deltaPosition[2] = { 0.0f, 0.0f };
double offsetScroll[2] = { 0.0f, 0.0f };
mat4x4 GlobleMVP[3];
GLFWwindow* window;
Shader* shader;
Shape* shapes[2];
mat4x4 mat4x4Identity = { {1.0f,0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f,1.0f} };
const float maxLrbtnf[6] = { -10.0, 10.0, -10.0, 10.0, -10.0, 10.0 };
const float minLrbtnf[6] = { -3.0, 3.0, -3.0, 3.0, -3.0, 3.0 };
const double minDeltaRoate = 10;
//旋转速度 1.0为正常速度
float roateSpeed = 1.0F;
float lrbtnf[6] = { -4.0, 4.0, -4.0, 4.0, -4.0, 4.0 };

void initGLFW();
void initOpenGL();
void setCameraOrtho();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
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
			deltaPosition[0] = 0.0f;
			deltaPosition[1] = 0.0f;
		}
	}
}
static void cursorPos_callback(GLFWwindow* window, double x, double y) {
	if (isPressing) {
		double deltaX = x - lastPosition[0];
		double deltaY = y - lastPosition[1];
		if (std::abs(deltaX) >= minDeltaRoate) {
			deltaPosition[0] = deltaX;
			lastPosition[0] = x;
		}
		if (std::abs(deltaY) >= minDeltaRoate) {
			deltaPosition[1] = deltaY;
			lastPosition[1] = y;
		}
	}
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	//根据滑轮缩放摄像机的宽度与高度
	lrbtnf[0] -= yoffset;
	lrbtnf[1] += yoffset;
	lrbtnf[2] -= yoffset;
	lrbtnf[3] += yoffset;
}

int main()
{
	initGLFW();
	initOpenGL();
	for (int i = 0; i < 3; i++) {
		mat4x4_identity(GlobleMVP[i]);
	}
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setCameraOrtho();
		//水平方向绕x轴转
		mat4x4_rotate_X(GlobleMVP[0], GlobleMVP[0], deltaPosition[1] / height * 3.14 * roateSpeed);
		//垂直方向绕y轴转
		mat4x4_rotate_Y(GlobleMVP[0], GlobleMVP[0], deltaPosition[0] / width * 3.14 * roateSpeed);

		for (int i = 0; i < 2; i++) {
			shapes[i]->mvp(GlobleMVP[0], GlobleMVP[1], GlobleMVP[2]);
			shapes[i]->draw();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	delete shader;
	delete shapes[0];
	delete shapes[1];
	exit(EXIT_SUCCESS);
	return 0;
}
void setCameraOrtho() {
	for (int i = 0; i < 6; i++) {
		if (std::abs(lrbtnf[i]) > std::abs(maxLrbtnf[i])) {
			lrbtnf[i] = maxLrbtnf[i];
		}
		else if (std::abs(lrbtnf[i]) < std::abs(minLrbtnf[i])) {
			lrbtnf[i] = minLrbtnf[i];
		}
	}
	mat4x4_ortho(GlobleMVP[2], lrbtnf[0], lrbtnf[1], lrbtnf[2], lrbtnf[3], lrbtnf[4], lrbtnf[5]);
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
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
}
void initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	shader = new Shader();
	shapes[0] = new Coordinate();
	shapes[1] = new Cube();
	for (int i = 0; i < 2; i++) {
		shapes[i]->init(shader);
	}
}