#pragma once
#ifndef GL_TEXTURE_LOADER
#define GL_TEXTURE_LOADER
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>												
#include <gl\gl.h>		
typedef struct												
{
	GLubyte	*imageData;										
	GLuint	bpp;											
	GLuint	width;											
	GLuint	height;											
	GLuint	texID;										
} TextureTga;


BOOL BuildTexture(const char *szPathName, GLuint &texid);

BOOL BuildTexture(const char *filename, TextureTga *texture);

#endif