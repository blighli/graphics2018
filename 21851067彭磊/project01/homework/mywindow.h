#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"Mat_Vec.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

class Window {
private:
	int m_Width, m_Height;
	const char *m_Title;
	GLFWwindow *m_Window;
	bool m_Closed;
	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double m_X, m_Y;
	double m_XOffset, m_YOffset;
	double m_Fov = 45.0f;
	float m_Picth = 0.0f;
	float m_Yaw = -90.0f;
	float m_LastX, m_LastY;
	vec3 m_Front = vec3(0.0f, 0.0f, -1.0f);
public:
	Window(const char *title, int width, int height);
	~Window();
	bool closed() const;
	void update();
	void clear() const;
	inline int getWidth() const { return m_Width; };
	inline int getHeight() const { return m_Height; };
	inline double getCursorX() const { return m_X; }
	inline double getCursorY() const { return m_Y; }
	inline double getScrollX() const { return m_XOffset; }
	inline double getScrollY() const { return m_YOffset; }
	inline double getFov() const { return m_Fov; }
	inline vec3 getFront() const { return m_Front; }
	inline GLFWwindow * getWindow() const { return m_Window; }
	bool isKeyPressed(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;
	void getMousePosition(double &x, double &y) const;
private:
	bool init();
	friend static void  window_resize(GLFWwindow *window, int width, int height);
	friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};