#pragma once

#include "mywindow.h"
#include <iostream>
using namespace std;

bool firstMouse = true;
void window_resize(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
Window::Window(const char * title, int width, int height) {
	m_Title = title;
	m_Width = width;
	m_Height = height;
	if (!init())
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++)
		m_Keys[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtons[i] = false;
}

Window::~Window() {
	glfwTerminate();
}

bool Window::closed() const {
	return glfwWindowShouldClose(m_Window);
}

void Window::update() {
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Window::isKeyPressed(unsigned int keycode) const {
	if (keycode >= MAX_KEYS)
		return false;
	return m_Keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const {
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtons[button];
}

void Window::getMousePosition(double &x, double &y) const {
	x = m_X;
	y = m_Y;
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::init()
{
	if (!glfwInit())
		return false;
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);

	if (glewInit() != GLEW_OK) {
		cout << "GLEW fail" << endl;
		return false;
	}
	cout << "OpenGL " << glGetString(GL_VERSION) << endl;
	return true;
}

void window_resize(GLFWwindow *window, int width, int height) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Width = width;
	win->m_Height = height;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	if (action != GLFW_RELEASE)
	{
		win->m_Keys[key] = 1;
	}
	else
	{
		win->m_Keys[key] = 0;
	}


	/*cout << "keyboard " << '"' << key << '"' << " Pressed!" << endl;*/
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	if (action != GLFW_RELEASE)
	{
		win->m_MouseButtons[button] = 1;
	}
	else
	{
		win->m_MouseButtons[button] = 0;
	}
	cout << "mouse " << '"' << button << '"' << " Pressed!" << endl;
}
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		win->m_X = xpos;
		win->m_Y = ypos;
		firstMouse = false;
	}
	/*cout << "x: " << xpos << " y: " << ypos << endl;*/
	float xoffset = xpos - win->m_X;
	float yoffset =  win->m_Y - ypos  ; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	win->m_X = xpos;
	win->m_Y = ypos;
	
	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	win->m_Yaw += xoffset;
	win->m_Picth += yoffset;
	
	if (win->m_Picth > 89.0f)
		win->m_Picth = 89.0f;
	if (win->m_Picth < -89.0f)
		win->m_Picth = -89.0f;

	float x = cos(toRadians(win->m_Yaw)) * cos(toRadians(win->m_Picth));
	float y = sin(toRadians(win->m_Picth));
	float z = sin(toRadians(win->m_Yaw)) * cos(toRadians(win->m_Picth));
	vec3 front(x, y, z);
	win->m_Front = normalize(front);
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->m_XOffset = xoffset;
	win->m_YOffset = yoffset;
	if (win->m_Fov >= 1.0f && win->m_Fov <= 45.0f)
		win->m_Fov -= yoffset;
	if (win->m_Fov <= 1.0f)
		win->m_Fov = 1.0f;
	if (win->m_Fov >= 45.0f)
		win->m_Fov = 45.0f;
}