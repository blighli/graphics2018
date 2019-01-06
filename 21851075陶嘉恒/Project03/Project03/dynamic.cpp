#include "dynamic.h"

DynamicTexture::DynamicTexture()
{
	for (int i = 0; i < FIRE_NUM; i++) {
		firetextureNum[i] = i;
	}
	
	string fire1 = "img/fire/51_064_00000.tga";
	string fire2 = "img/fire/51_064_00001.tga";
	string fire3 = "img/fire/51_064_00002.tga";
	string fire4 = "img/fire/51_064_00003.tga";
	string fire5 = "img/fire/51_064_00004.tga";
	string fire6 = "img/fire/51_064_00005.tga";
	string fire7 = "img/fire/51_064_00006.tga";
	string fire8 = "img/fire/51_064_00007.tga";

	firepath.push_back(fire1);
	firepath.push_back(fire2);
	firepath.push_back(fire3);
	firepath.push_back(fire4);
	firepath.push_back(fire5);
	firepath.push_back(fire6);
	firepath.push_back(fire7);
	firepath.push_back(fire8);
	
}

DynamicTexture::~DynamicTexture()
{
}

void DynamicTexture::loadTexImages() {
	glGenTextures(FIRE_NUM, firetextureNum);

	for (int i = 0; i < firepath.size(); i++) {		//火焰
		GLbyte *pBits = NULL;
		int nWidth, nHeight, nComponents;
		GLenum eFormat;
		const char *p = firepath[i].c_str();
		//pBits = gltReadBMPBits(p, &nWidth, &nHeight);
		pBits = gltReadTGABits(p, &nWidth, &nHeight, &nComponents, &eFormat);
		if (pBits == NULL)
			return;
		glBindTexture(GL_TEXTURE_2D, firetextureNum[i]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nComponents, nWidth, nHeight, eFormat, GL_UNSIGNED_BYTE, pBits);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, nWidth, nHeight, GL_RGB, GL_UNSIGNED_BYTE, pBits);
		free(pBits);
	}
}

void DynamicTexture::drawFire(int k,float n[]) {
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, firetextureNum[k]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5 * n[0], -1.0f, -5.0f *  n[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5 * n[0], -1.0f, 5.0f * n[1]);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5 * n[0], 10, 5.0f *  n[1]);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5 * n[0], 10, -5.0f *  n[1]);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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


GLbyte* DynamicTexture:: gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight)
{
	FILE*	pFile;
	RGBQUAD *pColorTable;//颜色表指针
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;
	GLbyte *pBits = NULL;					// Bitmaps bits
	BITMAPFILEHEADER	bitmapHeader;
	BITMAPINFOHEADER bitinfomapHeader;
	// Attempt to open the file
	errno_t err;
	err = fopen_s(&pFile,szFileName, "r");
	if (err != 0) {
		cout << "文件读取失败";
		return NULL;
	}

	// File is Open. Read in bitmap header information
	fread(&bitmapHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	if (bitmapHeader.bfType != 0x4D42)
	{
		free(&bitmapHeader);
		fclose(pFile);
		return NULL;
	}

	fread(&bitinfomapHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	long bmpWidth = bitinfomapHeader.biWidth;
	long bmpHeight = bitinfomapHeader.biHeight;
	
	WORD biBitCount;
	// Read in bitmap information structure
	lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
	bmpWidth = bitinfomapHeader.biWidth;
	bmpHeight = bitinfomapHeader.biHeight;
	biBitCount = bitinfomapHeader.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	*nWidth = bmpWidth; *nHeight = bmpHeight;
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256
	GLuint imageSize = bitinfomapHeader.biSizeImage;
	if (biBitCount == 8)
	{

		//申请颜色表所需要的空间，读颜色表进内存

		pColorTable = new RGBQUAD[256];

		fread(pColorTable, sizeof(RGBQUAD), 256, pFile);

	}

	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char *pBmpBuf;
	pBmpBuf = new unsigned char[lineByte * bmpHeight];

	/*if (fread(pBmpBuf, 1, lineByte * bmpHeight, pFile) != 1) {
		free(pBmpBuf);
		printf("%s图像信息赋值错误\n", szFileName);
		return NULL;

	}*/
	fread(pBmpBuf, 1, lineByte * bmpHeight, pFile);
	if (pBmpBuf != NULL) {
		for (int imageIdx = 0; imageIdx < imageSize; imageIdx += 3)
		{
			unsigned char tempRGB = pBmpBuf[imageIdx];
			pBmpBuf[imageIdx] = pBmpBuf[imageIdx + 2];
			pBmpBuf[imageIdx + 2] = tempRGB;
		}
	}

	fclose(pFile);//关闭文件
	return (GLbyte*)pBmpBuf;
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

GLbyte *DynamicTexture::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
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
	fopen_s(&pFile, szFileName, "r");
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
