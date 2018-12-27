#pragma once

#include "../../GLWindow/stdafx.h"

#define BMP_Header_Length 54

class GLWindow;

class ScreenShot
{
public:
	ScreenShot();
	~ScreenShot();

	void GrabScreen(GLWindow* pWnd);
};