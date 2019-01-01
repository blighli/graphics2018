#include "Texture.h"

BOOL BuildTexture(const char *szPathName, GLuint &texid)					
{
	HDC			hdcTemp;										
	HBITMAP		hbmpTemp;											
	IPicture	*pPicture;										
	OLECHAR		wszPath[MAX_PATH + 1];								
	char		szPath[MAX_PATH + 1];								
	long		lWidth;												
	long		lHeight;											
	long		lWidthPixels;											
	long		lHeightPixels;									
	GLint		glMaxTexDim;										


	GetCurrentDirectory(MAX_PATH, szPath);						
	strcat(szPath, "\\");									
	strcat(szPath, szPathName);										


	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		
	HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

	if (FAILED(hr))												
	{

		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	hdcTemp = CreateCompatibleDC(GetDC(0));							
	if (!hdcTemp)														
	{
		pPicture->Release();										
		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);				

	pPicture->get_Width(&lWidth);								
	lWidthPixels = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);									
	lHeightPixels = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

	if (lWidthPixels <= glMaxTexDim)							
		lWidthPixels = 1 << (int)floor((log((double)lWidthPixels) / log(2.0f)) + 0.5f);
	else															
		lWidthPixels = glMaxTexDim;

	if (lHeightPixels <= glMaxTexDim)								
		lHeightPixels = 1 << (int)floor((log((double)lHeightPixels) / log(2.0f)) + 0.5f);
	else															
		lHeightPixels = glMaxTexDim;


	BITMAPINFO	bi = { 0 };											
	DWORD		*pBits = 0;										

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);			
	bi.bmiHeader.biBitCount = 32;							
	bi.bmiHeader.biWidth = lWidthPixels;				
	bi.bmiHeader.biHeight = lHeightPixels;				
	bi.bmiHeader.biCompression = BI_RGB;		
	bi.bmiHeader.biPlanes = 1;							


	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);

	if (!hbmpTemp)											
	{
		DeleteDC(hdcTemp);										
		pPicture->Release();									

		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											
	}

	SelectObject(hdcTemp, hbmpTemp);							

	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

	for (long i = 0; i < lWidthPixels * lHeightPixels; i++)				
	{
		BYTE* pPixel = (BYTE*)(&pBits[i]);						
		BYTE  temp = pPixel[0];								
		pPixel[0] = pPixel[2];								
		pPixel[2] = temp;											
		pPixel[3] = 255;											
	}

	glGenTextures(1, &texid);										

	glBindTexture(GL_TEXTURE_2D, texid);							
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   


	glTexImage2D(GL_TEXTURE_2D, 0, 3, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	DeleteObject(hbmpTemp);												
	DeleteDC(hdcTemp);												

	pPicture->Release();										

	return TRUE;														
}

BOOL BuildTexture(const char *filename, TextureTga *texture)					
{
	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };			
	GLubyte		TGAcompare[12];											
	GLubyte		header[6];												
	GLuint		bytesPerPixel;											
	GLuint		imageSize;												
	GLuint		temp;												
	GLuint		type = GL_RGBA;									

	FILE *file = fopen(filename, "rb");								

	if (file == NULL)											
	{

		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											
	}

	if (fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare)
		|| memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0			
		|| fread(header, 1, sizeof(header), file) != sizeof(header))		
	{
		fclose(file);												
		return FALSE;													
	}

	texture->width = header[1] * 256 + header[0];						
	texture->height = header[3] * 256 + header[2];						

	if (texture->width <= 0										
		|| texture->height <= 0									
		|| (header[4] != 24 && header[4] != 32))					
	{
		fclose(file);												
		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												
	}

	texture->bpp = header[4];									
	bytesPerPixel = texture->bpp / 8;								
	imageSize = texture->width*texture->height*bytesPerPixel;		

	texture->imageData = (GLubyte *)malloc(imageSize);				

	if (texture->imageData == NULL 										
		|| fread(texture->imageData, 1, imageSize, file) != imageSize)	
	{
		if (texture->imageData != NULL)									
		{
			free(texture->imageData);									
		}
		fclose(file);												
		MessageBox(HWND_DESKTOP, "Õº∆¨µº»Î ß∞‹!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											
	}

	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)				
	{																	
		temp = texture->imageData[i];									
		texture->imageData[i] = texture->imageData[i + 2];			
		texture->imageData[i + 2] = temp;							
	}

	fclose(file);													


	glGenTextures(1, &texture->texID);							

	glBindTexture(GL_TEXTURE_2D, texture->texID);					
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	if (texture->bpp == 24)											
	{
		type = GL_RGB;												
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture->width, texture->height, 0, type, GL_UNSIGNED_BYTE, texture->imageData);

	return TRUE;													
}