#pragma once
#include "../GLWindow/GLWindow.h"  // 使用GLWindow ： 基于win32封装的窗口应用类库

class TextureLoader;
class ScreenShot;

class MainScene : public GLWindow
{
public:
	MainScene();
	~MainScene();

	// 初始化
	BOOL initGL(GLvoid) override;

	// 显示模式
	void ViewMode() override;

	// 绘制场景
	BOOL DrawGL(GLvoid) override;

	// 更新窗口消息
	BOOL UpdateGL(GLvoid) override;

	// opengl窗口销毁前的处理
	GLvoid DestroyGL(GLvoid) override;

private:
	TextureLoader *m_texLoader;  // 纹理加载工具
	ScreenShot *m_screenShot;	 // 屏幕截图工具
};