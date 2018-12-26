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

/************************************************************************/
/* 应用程序基类                                                           */
/************************************************************************/
#pragma once
#include "stdafx.h"

class QWndApp
{
public:
	QWndApp();
	~QWndApp();

public:
	virtual BOOL InitInstance();   // 初始化 app
	virtual BOOL ExitInstance();   // 退出 app
	virtual void run();			   // 运行

protected:
	LPVOID m_pMainWnd;
};
