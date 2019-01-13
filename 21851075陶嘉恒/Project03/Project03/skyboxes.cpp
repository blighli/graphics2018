#include <glew/glew.h>
#include"skyboxes.h"
#include<stdio.h>
#include<windows.h>

Skybox::Skybox() {
	//texturenum = new int[SKYBOX_NUM];
	//texturedata = NULL;
	width = 256;		//纹理图片的宽
	height = 128;		//纹理图片的高
	/*for (int i = 0; i < SKYBOX_NUM; i++)
		skytextureNum[i] = i;*/
	//天空盒纹理
	string front = "img/skybox/1.bmp";
	string left = "img/skybox/2.bmp";
	string back = "img/skybox/3.bmp";
	string right = "img/skybox/4.bmp";
	string top = "img/skybox/5.bmp";
	string land = "img/skybox/land.bmp";
	string terrain = "img/skybox/Terrain1.bmp";
	skypath.push_back(front);
	skypath.push_back(left);
	skypath.push_back(back);
	skypath.push_back(right);
	skypath.push_back(top);
	skypath.push_back(land);
	//path.push_back(terrain);
	int w, h;
	g_imageData = gltReadBMPBits(terrain.c_str(), &w, &h);
	InitTerrain();

	//树木纹理
	string tree = "img/tree/tree.tga";
	string tree1 = "img/tree/tree1.tga";
	string tree2 = "img/tree/tree2.tga";
	string tree3 = "img/tree/tree3.tga";
	//string tree3 = "img/fire/fire_00001.tga";
	treepath.push_back(tree);
	treepath.push_back(tree1);
	treepath.push_back(tree2);
	treepath.push_back(tree3);
}

Skybox::~Skybox(){}

//初始化地形  将地形放大
void Skybox::InitTerrain()
{
	int index = 0;
	int Vertex;
	for (int z = 0; z < MAP_W; z++)
		for (int x = 0; x < MAP_W; x++)
		{
			Vertex = z * MAP_W + x;
			g_terrain[Vertex][0] = float(x)*MAP_SCANL;
			g_terrain[Vertex][1] = (float)(g_imageData[(z*MAP_W + x) * 3]/4);
			g_terrain[Vertex][2] = float(z)*MAP_SCANL;
			g_texcoord[Vertex][0] = (float)x;
			g_texcoord[Vertex][1] = (float)z;
			g_index[index++] = Vertex;
			g_index[index++] = Vertex + MAP_W;
		}
	glEnableClientState(GL_VERTEX_ARRAY);		//顶点数组
	glVertexPointer(3, GL_FLOAT, 0, g_terrain);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	//材质数组
	glTexCoordPointer(2, GL_FLOAT, 0, g_texcoord);
}

void setTextureFiltering(void)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

//画地形
void Skybox::drawLand() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, skytextureNum[5]);
	setTextureFiltering();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-MAP_W * MAP_SCANL / 2,0.0f, -MAP_W * MAP_SCANL/2);
	/*glBegin(GL_QUADS);	//	平地面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2 - 1, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2 + 1, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2 + 1, -1.0f, -width / 2 - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2 - 1, -1.0f, -width / 2 - 1);
	glEnd();*/
	for (int z = 0; z < MAP_W - 1; z++)		//凹凸地面
		glDrawElements(GL_TRIANGLE_STRIP, MAP_W*2, GL_UNSIGNED_INT, &g_index[z*MAP_W*2]);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//得到地形高度
float Skybox::getHeight(float x, float z) {
	float low = -MAP_SCANL * MAP_W / 2;
	float high = MAP_SCANL * MAP_W / 2;
	if (x >= low && z >= low && x<= high && z<= high) {
		float CameraX = (x+high) / MAP_SCANL;
		float CameraZ = (z+high) / MAP_SCANL;
		int Col0 = int(CameraX);
		int Row0 = int(CameraZ);
		int Col1 = Col0 + 1;
		int Row1 = Row0 + 1;
		if (Col1 > MAP_W)	Col1 = 0;
		if (Row1 > MAP_W)	Row1 = 0;
		float h00 = g_terrain[Col0 + Row0*MAP_W][1];
		float h01 = g_terrain[Col1 + Row0*MAP_W][1];
		float h11 = g_terrain[Col1 + Row1*MAP_W][1];
		float h10 = g_terrain[Col0 + Row1*MAP_W][1];
		float tx = CameraX - int(CameraX);
		float ty = CameraZ - int(CameraZ);
		float txty = tx * ty;
		return h00*(1.0f - ty - tx + txty)
			+ h01*(tx - txty)
			+ h11*txty
			+ h10*(ty - txty);
	}
	else {
		return 0.0f;
	}
}


void Skybox::drawTrees(float treex[], float treez[], int num,float n[], int treenum[]) {

	//srand((unsigned int)time(NULL));
	glEnable(GL_TEXTURE_2D);
	setTextureFiltering();
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	for (int i = 0; i < num; i++) {
		
		float h = getHeight(treex[i], treez[i]) + 5.0f;
		glBindTexture(GL_TEXTURE_2D, treetextureNum[treenum[i]]);
		//glBindTexture(GL_TEXTURE_2D, treetextureNum[k]);
		
		glPushMatrix();
		glTranslatef(treex[i], h, treez[i]);
		glBegin(GL_QUADS);
		//可以看出 glVertex3f里面 1 -2  得到的向量与源.cpp中n1垂直   3-4 得到的向量与源.cpp中n1垂直
		//这样树木就能随着你的视点转动而改变自身位置，使树木面片永远与视点所看向的方向垂直，即面片永远正对着视点
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f * n[0], -5.0f , -5.0f* n[1]);	//	1
		glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f * n[0], -5.0f , 5.0f* n[1]);		// 2
		glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f * n[0], 5.0f , 5.0f* n[1]);		// 3
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f * n[0], 5.0f , -5.0f* n[1]);		// 4
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	//
}

void Skybox::loadTexImages() {
	glGenTextures(SKYBOX_NUM, skytextureNum);
	
	//读取图片信息,绑定纹理
	for (int i = 0; i < skypath.size(); i++) {		//天空盒纹理
		GLbyte *pBits = NULL;
		int nWidth, nHeight, nComponents;
		GLenum eFormat;
		const char *p = skypath[i].c_str();
		pBits = gltReadBMPBits(p, &nWidth, &nHeight);
		if (pBits == NULL)
			return;
		nComponents = GL_RGB;
		eFormat = GL_RGB;
		glBindTexture(GL_TEXTURE_2D, skytextureNum[i]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nComponents, nWidth, nHeight, eFormat, GL_UNSIGNED_BYTE, pBits);

		free(pBits);
	}
	glGenTextures(SKYBOX_NUM, treetextureNum);
	for (int i = 0; i < treepath.size(); i++) {		//树木等透明纹理
		GLbyte *pBits = NULL;
		int nWidth, nHeight, nComponents;
		GLenum eFormat;
		const char *p = treepath[i].c_str();
		pBits = gltReadTGABits(p, &nWidth, &nHeight, &nComponents, &eFormat);
		if (pBits == NULL)
			return;
		glBindTexture(GL_TEXTURE_2D, treetextureNum[i]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nComponents, nWidth, nHeight, eFormat, GL_UNSIGNED_BYTE, pBits);
		free(pBits);
	}
}


void Skybox::drawSkyBox() {
	
	glEnable(GL_TEXTURE_2D);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//绘制天空盒
	//front
	glBindTexture(GL_TEXTURE_2D, skytextureNum[0]);
	
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, width / 2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2 - 1, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2 + 1, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2 + 1, height, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2 - 1, height, 0.0f);
	glEnd();
	glLoadIdentity();
	glPopMatrix();

	//left
	glBindTexture(GL_TEXTURE_2D, skytextureNum[1]);
	
	glPushMatrix();
	glTranslatef(width / 2, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -width / 2 - 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, height, -width / 2 - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, height, width / 2 + 1);
	glEnd();
	glLoadIdentity();
	glPopMatrix();

	//back
	glBindTexture(GL_TEXTURE_2D, skytextureNum[2]);
	
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -width / 2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width / 2 + 1, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width / 2 - 1, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width / 2 - 1, height, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width / 2 + 1, height, 0.0f);
	glEnd();
	glLoadIdentity();
	glPopMatrix();

	//right
	glBindTexture(GL_TEXTURE_2D, skytextureNum[3]);
	
	glPushMatrix();
	glTranslatef(-width / 2, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, -width / 2 - 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, height, width / 2 + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, height, -width / 2 - 1);
	glEnd();
	glLoadIdentity();
	glPopMatrix();

	//top
	glBindTexture(GL_TEXTURE_2D, skytextureNum[4]);
	
	glPushMatrix();
	glTranslatef(0.0f, width / 2, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2 - 1, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2 + 1, -1.0f, width / 2 + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2 + 1, -1.0f, -width / 2 - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2 - 1, -1.0f, -width / 2 - 1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void Skybox::moveSkyBox(GLint x,GLint y, GLint z) {
	glPushMatrix();
	glTranslatef(x, -height/2, z);
	drawSkyBox();
	glPopMatrix();
	drawLand();
}

int Skybox::getTreepathSize() {
	return treepath.size();
}




/*************************************************/
#pragma pack(1)
struct RGB {
	GLbyte blue;
	GLbyte green;
	GLbyte red;
	GLbyte alpha;
};

struct BMPInfoHeader {
	GLuint	size;
	GLuint	width;
	GLuint	height;
	GLushort  planes;
	GLushort  bits;
	GLuint	compression;
	GLuint	imageSize;
	GLuint	xScale;
	GLuint	yScale;
	GLuint	colors;
	GLuint	importantColors;
};

struct BMPHeader {
	GLushort	type;
	GLuint	size;
	GLushort	unused;
	GLushort	unused2;
	GLuint	offset;
};

struct BMPInfo {
	BMPInfoHeader		header;
	RGB				colors[1];
};
#pragma pack(8)


GLbyte* Skybox::gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight)
{
	FILE*	pFile;
	BMPInfo *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;
	GLbyte *pBits = NULL;					// Bitmaps bits
	BMPHeader	bitmapHeader;

	// Attempt to open the file
	fopen_s(&pFile,szFileName, "r");
	if (pFile == NULL)
		return NULL;

	// File is Open. Read in bitmap header information
	fread(&bitmapHeader, sizeof(BMPHeader), 1, pFile);

	// Read in bitmap information structure
	lInfoSize = bitmapHeader.offset - sizeof(BMPHeader);
	pBitmapInfo = (BMPInfo *)malloc(sizeof(GLbyte)*lInfoSize);
	if (fread(pBitmapInfo, lInfoSize, 1, pFile) != 1)
	{
		free(pBitmapInfo);
		fclose(pFile);
		return false;
	}

	// Save the size and dimensions of the bitmap
	*nWidth = pBitmapInfo->header.width;
	*nHeight = pBitmapInfo->header.height;
	lBitSize = pBitmapInfo->header.imageSize;

	// If the size isn't specified, calculate it anyway	
	if (pBitmapInfo->header.bits != 24)
	{
		free(pBitmapInfo);
		return false;
	}

	if (lBitSize == 0)
		lBitSize = (*nWidth *
			pBitmapInfo->header.bits + 7) / 8 *
		abs(*nHeight);
	GLuint imageSize = pBitmapInfo->header.imageSize;
	// Allocate space for the actual bitmap
	free(pBitmapInfo);
	pBits = (GLbyte*)malloc(sizeof(GLbyte)*lBitSize);

	// Read in the bitmap bits, check for corruption
	if (fread(pBits, lBitSize, 1, pFile) != 1)
	{
		free(pBits);
		printf("%s图像信息赋值错误\n", szFileName);
		pBits = NULL;
	}
	//fread(pBits, lBitSize, 1, pFile);
	// Close the bitmap file now that we have all the data we need
	fclose(pFile);
	if (pBits != NULL) {
		for (int imageIdx = 0; imageIdx < imageSize; imageIdx += 3)
		{
			unsigned char tempRGB = pBits[imageIdx];
			pBits[imageIdx] = pBits[imageIdx + 2];
			pBits[imageIdx + 2] = tempRGB;
		}
	}
	return pBits;
}

/***************************************************/
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
//#pragma pack(8)

GLbyte *Skybox::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	fopen_s(&pFile,szFileName, "r");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	/***********************************************************************/
	/*if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}*/
	fread(pBits, lImageSize, 1, pFile);

	// Set OpenGL format expected
	switch (sDepth)
	{
#ifndef OPENGL_ES
	case 3:     // Most likely case
		*eFormat = GL_BGR; //define in glew.h;
		*iComponents = GL_RGB;
		break;
#endif
	case 4:
		*eFormat = GL_BGRA; //define in glew.h;
		*iComponents = GL_RGBA;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
					// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!
#ifdef OPENGL_ES
		for (int i = 0; i < lImageSize; i += 3)
		{
			GLbyte temp = pBits[i];
			pBits[i] = pBits[i + 2];
			pBits[i + 2] = temp;
		}
#endif
		break;
	}



	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}


