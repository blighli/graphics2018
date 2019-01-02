#pragma once
/*
 * BitMap : 提供BitMap操作
 *          1) 屏幕截屏为 BitMap
 *		    2) 加载 BitMap
 */

#include "../../GLWindow/stdafx.h"

class GLWindow;

#define BMP_Header_Length 54

class TextureLoader 
{
public:
	TextureLoader ();
	~TextureLoader ();

	// 加载位图函数
	GLuint LoadBitMapTexture(const char* file);

private:
	GLint m_width;
	GLint m_height;
};