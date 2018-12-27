#include "ScreenShot.h"
#include "../../GLWindow/GLWindow.h"
#include "../../System/System.h"
#include <string>

ScreenShot::ScreenShot()
{

}

ScreenShot::~ScreenShot()
{

}

void ScreenShot::GrabScreen(GLWindow* pWnd)
{
	FILE* pDummyFile;    // 用于保存bmp数据的文件指针
	FILE* pWritingFile;  // 用于读取
	GLubyte* pPixelData; // 像素数据
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	// 计算像素数据的实际长度
	i = pWnd->GetWidth() * 3; // 每一行的像素数据长度

	while (i % 4 != 0) {
		++i; // 补充数据，直到 i 是4的倍数
	}

	PixelDataLength = i * pWnd->GetHeight();
	// 分配内存和打开文件
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0) {
		exit(0);  // 分配失败
	}

	pDummyFile = fopen("bitmap/dummy.bmp", "rb");

	if (pDummyFile == 0) {
		exit(0);
	}

	std::string file_name = std::string("screenshot/grab_screen ");
	std::string sys_time = apanoo::System::GetInstance()->GetSystemTime();

	std::string full_file_name = file_name + sys_time + std::string(".bmp");   // 截屏文件增加系统时间戳

	pWritingFile = fopen(full_file_name.c_str(), "wb");
	if (pWritingFile == 0) {
		exit(0);
	}

	// 读取像素
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, pWnd->GetWidth(), pWnd->GetHeight(),
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把 dummy.bmp 的文件头复制为新文件的文件头
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);

	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = pWnd->GetWidth();
	j = pWnd->GetHeight();
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}
