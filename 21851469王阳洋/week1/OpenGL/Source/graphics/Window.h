#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../maths/maths_func.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Window {
public:
	Window(const char * title, const int width, const int height);
	~Window();
	bool init();
	void update();
	void clear() const;
	bool closed() const;
	bool isKeyPressed(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;
	void getMousePosition(double & x, double & y) const;
	void getMouseScroll(double & yoffet);
	void getAsepct(double & aspect) const;

private:
	int m_Width;
	int m_Height;
	const char * m_Title;
	GLFWwindow * m_Window;
	bool m_Closed;
	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double m_x, m_y;
	double m_aspect;
	double m_yoffet;

private:
	friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	friend static void window_size_callback(GLFWwindow * window, int width, int height);
	friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow *Window, double xoffset, double yoffet);
};

#endif