#pragma once

#include<iostream>
#include<vector>
#include<glut/freeglut.h>
#include<glext/glext.h>
#include<glut/glut.h>
#include <stdlib.h> 
#include <time.h>  

using namespace std;



const int SKYBOX_NUM = 7;

#define MAP_W 32
#define MAP_SCANL 16

class Skybox {
private:
	GLuint skytextureNum[SKYBOX_NUM];
	vector<string> skypath;
	GLuint treetextureNum[SKYBOX_NUM];
	vector<string> treepath;
	//设定整个地图的大小
	GLint width;	//与图片大小相符
	GLint height;	//与图片大小相符

	GLbyte*		g_imageData;		//地形高度信息
	float		g_terrain[MAP_W*MAP_W][3];
	GLuint		g_index[MAP_W*MAP_W * 2];
	float		g_texcoord[MAP_W*MAP_W][2];
	

	
public:
	Skybox();
	~Skybox();

	//赋纹理
	void loadTexImages();

	//画天空盒
	void drawSkyBox();

	//画地形
	void InitTerrain();
	void drawLand();

	//得到特定点的地形高度
	float getHeight(float x,float z);

	//画树木
	void drawTrees(float treex[],float treez[],int num,float n[],int treenum[]);

	//移动天空盒
	void moveSkyBox(GLint x,GLint y,GLint z);

	//读bmp
	GLbyte *gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight);

	//读tga
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	int getTreepathSize();


};

