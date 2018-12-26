#include "TextureLoader.h"
#include "../../GLWindow/GLWindow.h"

TextureLoader::TextureLoader()
{
	
}

TextureLoader::~TextureLoader()
{

}

/* 
* 检查一个整数是否为 2 的整数次方，如果是，返回 1，否则返回 0
*/
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return(n & (n - 1)) == 0;
}

/*
 * 加载bitmap 返回分配的纹理ID
 */
GLuint TextureLoader::LoadBitMapTexture(const char* file)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0; // 保存像素数据
	GLuint texture_ID = 0;
	GLint last_texture_ID;
	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file, "rb");
	if (pFile == 0) {
		return 0; 
	}
		
	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);  // 找到头部信息中的宽高信息处
	fread(&width, 4, 1, pFile);      // 读取宽
	fread(&height, 4, 1, pFile);	 // 读取高
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3; // 宽度不是4的倍数时进行放大至4倍
		while (line_bytes % 4 != 0) {
			++line_bytes;
		}
		total_bytes = line_bytes * height;
	}
	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0) {
		fclose(pFile);
		return 0;
	}
	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);   

		// 以下四种情况需要放缩纹理
		if (!power_of_two(width)       // 1.宽不是2整数次方
			|| !power_of_two(height)   // 2.高不是2整数次方
			|| width > max			   // 3.宽越界
			|| height > max)           // 4.高越界
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长256的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;
			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0) {
				++new_line_bytes;
			}
			new_total_bytes = new_line_bytes * new_height;
			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0) {
				free(pixels);
				fclose(pFile);
				return 0;
			}
			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
			// 释放原来的像素数据，把 pixels 指向新的像素数据，并重新设置 width和 height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}
	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	free(pixels);  // 释放内存
	return texture_ID;
}

