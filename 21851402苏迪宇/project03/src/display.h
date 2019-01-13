#pragma once
#include <string>
#include "SDL.h"
using namespace std;


class Display {
public:
	Display(int width, int height, const string& title);
	virtual ~Display();
	void swapBuffers();
	void clear(float r, float g, float b, float a);
	bool m_isClosed;
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};