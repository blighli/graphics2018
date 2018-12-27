/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2014 07 20
*  ps     : 基于win32 API封装
*			支持win32标准控件完全自绘
*			支持opengl
*  参考    : MFC实现机制
*  use     : 方便编写windows下图形应用及插件
*/

#include "GLWindow.h"

GLWindow::GLWindow()
{
	m_hRc = 0;
	::ZeroMemory(m_keys, sizeof(m_keys)); // 清空键盘缓存
}

GLWindow::~GLWindow()
{

}

// 创建opengl窗口
BOOL GLWindow::CreateGlWnd(const char* title, int x, int y, int width, int height)
{
	m_width = width;
	m_height = height;

	RECT windowRect = { 0, 0, width, height };
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;   // 预留做全屏
	DWORD windowExStyle = WS_EX_APPWINDOW;     // 扩展样式

	// 全屏处理 - 预留
	
	// 窗口样式
	windowStyle = WS_POPUP;
	windowExStyle |= WS_EX_TOPMOST;

	::AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExStyle); // 调整窗口

	CreateEx(0, "OpenGL", title, WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL);

	if (!(m_hDc = GetDC(m_hWnd)))  // 获取DC
	{
		DestroyGL();		  // 销毁
		return FALSE;		  // 不能获取DC
	}

	m_timerFrame = 1000;      // 初始化
	

	GLuint PixelFormat;
	static PIXELFORMATDESCRIPTOR pdf = {
		sizeof(PIXELFORMATDESCRIPTOR),  // 结构体大小
		1,					  // 版本号
		PFD_DRAW_TO_WINDOW |  // 支持窗口
		PFD_SUPPORT_OPENGL |  // 支持opengl
		PFD_DOUBLEBUFFER,     // 支持双缓冲
		PFD_TYPE_RGBA,        // 申请RGBA格式
		32,					  // 色彩深度
		0, 0, 0, 0, 0, 0,     // 忽略的色彩位
		0,					  // 无alpha缓存
		0,					  // 无shift Bit
		0,					  // 无累加缓存
		0, 0, 0, 0,			  // 忽略聚集位
		24,					  // 16位Z-缓存
		8,					  // 无蒙版缓存
		0,					  // 无辅助缓存
		PFD_MAIN_PLANE,		  // 主绘图层
		0,					  // Reserved
		0, 0, 0				  // 忽略层遮罩
	};
	if (!(PixelFormat = ChoosePixelFormat(m_hDc, &pdf)))  // 寻找相应像素格式
	{
		DestroyGL();  // 销毁
		// printf("1====error choose====");
		return FALSE;
	}
	if (!SetPixelFormat(m_hDc, PixelFormat, &pdf))
	{
		DestroyGL();
		// printf("1====error choose====");
		return FALSE;
		// 不能设置像素格式
	}

	HGLRC tempContext;
	if (!(tempContext = wglCreateContext(m_hDc)))
	{
		DestroyGL();
		// printf("2====error create context====");
		return FALSE;      // 不能获得着色描述表
	}
	if (!wglMakeCurrent(m_hDc, tempContext))  // 开启低版本opengl
	{
		DestroyGL();
		// printf("3========");
		return FALSE;      // 不能激活当前opengl渲染描述表
	}

	if (GLEW_OK != glewInit())
	{
		DestroyGL();
		return FALSE;      // glew初始化失败
	}

	// 开启 opengl 4.3 支持
	GLint attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  4,  // 主版本4
		WGL_CONTEXT_MINOR_VERSION_ARB,  3,					// 次版本号3
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,//要求返回兼容模式环境,如果不指定或指定为WGL_CONTEXT_CORE_PROFILE_BIT_ARB会返回只包含核心功能的环境
		0 };

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hRc = wglCreateContextAttribsARB(m_hDc, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		int result = wglMakeCurrent(m_hDc, m_hRc); // 设置opengl 4.3
		if (result != 1)
		{
			return FALSE;
		}
	}
	else
	{    // 不支持opengl4.X 还原为opengl 2.1
		m_hRc = tempContext;
	}
	RECT rect;		 // 客户区大小
	::GetClientRect(m_hWnd, &rect);
	ResizeGLScene(rect.right - rect.left, rect.bottom - rect.top);  // 设置GL屏幕 (注意，这里只使用客户区计算)

	if (!initGL())   // 初始化opengl
	{
		DestroyGL();
		return FALSE;
	}

	// 设定计时器 每秒刷新60次
	SetTimer(m_hWnd, m_timerFrame, 1000 / 60, NULL);

	return TRUE;
}

HRESULT GLWindow::OnClose(WPARAM wParam, LPARAM lParam)
{
	return DestroyWindow();
}

LRESULT GLWindow::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	DestroyGL();     // 退出程序前销毁opengl
	PostQuitMessage(0);
	return 0;
}

GLvoid GLWindow::ResizeGLScene(GLsizei width, GLsizei height)
{
	if (0 == height)
	{
		height = 1;  // 防止被0除
	}
	m_width = width;
	m_height = height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);  
	ViewMode();      // 设置显示模式
}

BOOL GLWindow::initGL(GLvoid)
{
	return TRUE;
}

BOOL GLWindow::DrawGL(GLvoid)
{
	return TRUE;
}

BOOL GLWindow::UpdateGL(GLvoid)
{
	return TRUE;
}

GLvoid GLWindow::DestroyGL(GLvoid)
{
	// 注销计时器
	::KillTimer(m_hWnd, m_timerFrame);

	if (m_hRc)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			// 释放DC或RC失败
		}
		if (!wglDeleteContext(m_hRc))
		{
			// 释放RC失败
		}
		m_hRc = NULL;
	}
	if (m_hDc && !ReleaseDC(m_hWnd, m_hDc))
	{
		// 释放DC失败
		m_hDc = NULL;
	}
	if (m_hWnd && !DestroyWindow())
	{
		// 释放窗口句柄失败
		m_hWnd = NULL;
	}
}

void GLWindow::ViewMode()
{

}

GLsizei GLWindow::GetWidth()
{
	return m_width;
}

GLsizei GLWindow::GetHeight()
{
	return m_height;
}

BOOL GLWindow::keyDown(int key)
{
	return m_keys[key] == TRUE ? TRUE : FALSE;
}

HRESULT GLWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 0 && wParam < 256)
	{
		m_keys[wParam] = TRUE;
	}
	return 0;
}

HRESULT GLWindow::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 0 && wParam < 256)
	{
		m_keys[wParam] = FALSE;
	}
	return 0;
}

HRESULT GLWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

HRESULT GLWindow::OnTimer(WPARAM wParam, LPARAM lParam)
{
	UpdateGL();  // 消息处理:键盘等
	return ::InvalidateRect(m_hWnd, NULL, FALSE); // 使窗口失效
}

HRESULT GLWindow::OnPaint(WPARAM wParam, LPARAM lParam)
{
	DrawGL();						// 绘制opengl场景
	SwapBuffers(m_hDc);				// 交换缓存
	::ValidateRect(m_hWnd, NULL);   // 使窗口有效
	return TRUE;
}


