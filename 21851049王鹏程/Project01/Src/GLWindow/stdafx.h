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

#include <windows.h>
#include <tchar.h>
#include <assert.h>

#include "GL/glew.h" // 在glut之前包含glew
#include "GL/wglew.h"
#include "GL/glut.h" 
#include "GL/freeglut.h"

#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"glew32s.lib")    // glew库