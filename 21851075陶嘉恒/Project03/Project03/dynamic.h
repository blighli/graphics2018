#pragma once
#include "skyboxes.h"



const int FIRE_NUM = 8;

class DynamicTexture 
{
public:
	DynamicTexture();
	~DynamicTexture();

	void drawFire(int k,float n[]);
	void loadTexImages();

	GLbyte *gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight);
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
private:
	GLuint firetextureNum[FIRE_NUM];
	vector<string> firepath;

};
