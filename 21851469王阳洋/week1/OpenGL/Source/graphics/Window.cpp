#include "Window.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
void window_size_callback(GLFWwindow * window, int width, int height);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *Window, double xoffset, double yoffet);

Window::Window(const char * title, const int width, const int height) {
	m_Title = title;
	m_Width = width;
	m_Height = height;
	m_aspect = 2.0f;

	if (!init()) {
		glfwTerminate();
	}

	memset(m_Keys, false, sizeof(m_Keys));
	memset(m_MouseButtons, false, sizeof(m_MouseButtons));
}

Window::~Window() {
	glfwTerminate();
}

bool Window::init() {

	if (!glfwInit()) {
		std::cout << "GLFW Initial FAIL" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window) {
		std::cout << "Create Window FAIL" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window,this);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetWindowSizeCallback(m_Window, window_size_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);
	

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW FAIL" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::update() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::closed() const {
	return glfwWindowShouldClose(m_Window);
}

bool Window::isKeyPressed(unsigned int keycode) const {
	if (keycode >= MAX_KEYS) {
		return false;
	}
	return m_Keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const {
	if (button >= MAX_BUTTONS) {
		return false;
	}
	return m_MouseButtons[button];
}

void Window::getMousePosition(double & x, double & y) const {
	x = m_x;
	y = m_y;
}

void Window::getAsepct(double & aspect) const {
	aspect = m_aspect;
}

void Window::getMouseScroll(double & yoffet) {
	yoffet = m_yoffet;
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Keys[key] = (action != GLFW_RELEASE);
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = (action != GLFW_RELEASE);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->m_x = xpos;
	win->m_y = ypos;
}

void window_size_callback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	if (win->m_aspect >= -30.0f && win->m_aspect <= 45.0f) {
		win->m_aspect -= yoffset;
	}
	if(win->m_aspect < -30.0f){
		win->m_aspect = -30.0f;
	}
	if (win->m_aspect > 45.0f) {
		win->m_aspect = 45.0f;
	}

	win->m_yoffet = yoffset;
}
