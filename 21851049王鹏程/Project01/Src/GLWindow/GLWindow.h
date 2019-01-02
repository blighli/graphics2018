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

#pragma once
#include "QWnd.h"

class GLWindow : public QWnd
{
public:
	GLWindow();
	~GLWindow();

	BOOL CreateGlWnd(const char* title, int x, int y, int width, int height);

	HRESULT OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);

	// 改变opengl窗口大小
	GLvoid ResizeGLScene(GLsizei width, GLsizei height);

	// 提供子类对opengl的初始化操作
	virtual BOOL initGL(GLvoid);

	// 提供子类opengl绘制函数
	virtual BOOL DrawGL(GLvoid);

	virtual BOOL UpdateGL(GLvoid);

	// 提供子类对opengl销毁时的处理
	virtual GLvoid DestroyGL(GLvoid);

	virtual void ViewMode();

	GLsizei GetWidth();
	GLsizei GetHeight();

	BOOL keyDown(int key);  // 暂时保留keyUp的封装

	virtual HRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSize(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnPaint(WPARAM wParam, LPARAM lParam);

private:
	HGLRC m_hRc;		 // 窗口着色描述表句柄
	HDC   m_hDc;		 // opengl渲染描述句柄
	BOOL  m_keys[256];   // 保存键盘按键数组
	GLuint m_timerFrame; // 绘图计时器
	GLsizei m_width;
	GLsizei m_height;
};