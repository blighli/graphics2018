//
//  main.cpp
//  project02
//
//  Created by weipingw on 2019/1/1.
//  Copyright © 2019年 weipingw. All rights reserved.
//

#define PI 3.1415926

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>

GLuint sun,earth,moon;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量

/*函数power_of_two
 *判断一个整数是不是2的整数次幂
 */
int power_of_two(int n)
{
    if (n <= 0)
        return 0;
    return (n & (n - 1)) == 0;
}

/* 函数load_texture
 * 读取一个BMP文件作为纹理
 * 如果失败，返回0，如果成功，返回纹理编号
 */
GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID = 0, texture_ID = 0;
    
    // 打开文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if (pFile == 0)
        return 0;
    
    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);
    
    // 计算每行像素所占字节数，并根据此数据计算总像素字节数
    {
        GLint line_bytes = width * 3;
        while (line_bytes % 4 != 0)
            ++line_bytes;
        total_bytes = line_bytes * height;
    }
    
    // 根据总像素字节数分配内存
    pixels = (GLubyte*)malloc(total_bytes);
    if (pixels == 0)
    {
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
    
    // 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
    // 若图像宽高超过了OpenGL规定的最大值，也缩放
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if (!power_of_two(width)
            || !power_of_two(height)
            || width > max
            || height > max)
        {
            const GLint new_width = 256;
            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            
            // 计算每行需要的字节数和总字节数
            new_line_bytes = new_width * 3;
            while (new_line_bytes % 4 != 0)
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            
            // 分配内存
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if (new_pixels == 0)
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }
            
            // 进行像素缩放
            gluScaleImage(GL_RGB,
                          width, height, GL_UNSIGNED_BYTE, pixels,
                          new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
            
            // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }
    
    // 分配一个新的纹理编号
    glGenTextures(1, &texture_ID);
    if (texture_ID == 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    
    // 绑定新的纹理，载入纹理并设置纹理参数
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    GLint lastTextureID = last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
    free(pixels);
    return texture_ID;
}

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(PI) / (GLfloat)iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(PI) / (GLfloat)iSlices;
    GLfloat ds = 1.0f / (GLfloat)iSlices;
    GLfloat dt = 1.0f / (GLfloat)iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;
    
    for (i = 0; i < iStacks; i++)
    {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));
        
        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for (j = 0; j <= iSlices; j++)
        {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));
            
            GLfloat x = stheta * srho;
            GLfloat y = crho;
            GLfloat z = ctheta * srho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            
            x = stheta * srhodrho;
            y = crhodrho;
            z = ctheta * srhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();
        
        t -= dt;
    }
}

void Initial()
{
    
    GLfloat light0_diffuse[] = { 1.0f,0.5f,0.0f,1.0f };//light0中漫反射光分量
    
    GLfloat light0_position[] = { 10.0f,20.0f,-150.0f,1.0f };//light0的坐标位置
    
    GLfloat light0_direction[] = { 0.0f,0.0f,-1.0f };//light0的聚光灯方向角
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);//light0在太阳中心
    
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
    
    glEnable(GL_DEPTH_TEST);// 启用深度测试
    
    glEnable(GL_LIGHTING);// 启用光源
    
    glEnable(GL_LIGHT0);
    
    glEnable(GL_TEXTURE_2D);//启用2D材质模式
    
    glFrontFace(GL_CCW);// 指定逆时针绕法表示多边形正面
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//背景
    
}

void ChangeSize(int w, int h)
{
    
    if (h == 0)h = 1;
    
    glViewport(0, 0, w, h);// 设置视区尺寸
    
    glMatrixMode(GL_PROJECTION);//指定当前操作投影矩阵堆栈
    
    glLoadIdentity();//重置投影矩阵
    
    gluPerspective(35.0, (float)w / (float)h, 1.0, 500.0);//指定透视投影的观察空间
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
}

void Display(void)
{
    
    static float angle1 = 0.0f, angle2 = 0.0f, angle3 = 0.0f;//angle1太阳自转角度，angle2地球绕太阳旋转角度，angle3月亮绕地球旋转的角度

    GLfloat sun_emission[] = { 1.0f,1.0f,1.0f,1.0f };//太阳漫反射光照
    
    GLfloat earth_emission[] = { 0.0f,0.0f,0.0f,1.0f };//地球漫反射光照

    GLfloat moon_emission[] = { 0.0f,0.0f,0.0f,1.0f };//月亮漫反射光照

    GLfloat sun_ambient[] = { 0.0f, 1.0f, 1.0f, 1.0f };//太阳环境光照
    
    GLfloat earth_moon_ambient[] = { 0.4f, 0.4f, 0.8f, 1.0f };//地球月亮环境光照

    GLfloat light1_position[] = { 0.0f,0.0f,-150.0f,1.0f };
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲区
    
    glMatrixMode(GL_MODELVIEW);//指定当前操作模型视图矩阵堆栈
    
    glLoadIdentity();//重置模型视图矩阵
    
    glTranslatef(0.0f, 0.0f, -150.0f);//将图形沿z轴负向移动150.0f
    
    glRotatef(angle1, 0, 1, 0);
    
    glBindTexture(GL_TEXTURE_2D, sun);
    
    glEnable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_emission);
    
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
    
    gltDrawSphere(10.0f, 30, 30);//绘制太阳
    
    glDisable(GL_LIGHT1);
    
    
    
    glPushMatrix();//保存当前的矩阵视图模型
    
    glBindTexture(GL_TEXTURE_2D, earth);
    
    glRotatef(angle2, 0.0f, 10.0f, 1.0f);//旋转一定角度
    
    //glTranslatef(40.0f, 0.0f, 0.0f);//绕x轴正向移动40.0f
    glTranslatef(45.0f, 0.0f, 0.0f);
    
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_emission);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_moon_ambient);
    
    gltDrawSphere(4.0f, 20, 20);//绘制地球
    
    
    glBindTexture(GL_TEXTURE_2D, moon);
    
    glRotatef(angle3, 0.0f, 1.0f, 0.0f);
    
    glTranslatef(10.0f, 0.0f, 0.0f);//绕x轴方向移动15.0f
    
    glMaterialfv(GL_FRONT, GL_EMISSION, moon_emission);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_moon_ambient);
    
    gltDrawSphere(1.0f, 20, 20);//绘制月亮
    
    
    
    glPopMatrix();//恢复矩阵视图模型
    
    angle1 += 4.0f;//增加旋转步长，产生动画效果
    
    if (angle1 == 360.0f)
        
        angle1 = 0.0f;
    
    angle2 += 1.0f;
    
    if (angle2 == 360.0f)
        
        angle2 = 0.0f;
    
    angle3 += 10.0f;
    if (angle3 == 360.0f)
        
        angle3 = 0.0f;
    
    glutSwapBuffers();
    
}

void TimerFunc(int x)
{
    
    glutPostRedisplay();
    
    glutTimerFunc(100, TimerFunc, 1);
    
}

int main(int argc, char* argv[])
{
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(960, 640);
    
    glutInitWindowPosition(400, 200);
    
    glutCreateWindow("myOpenGLProject2");
    
    glutReshapeFunc(ChangeSize);
    
    glutDisplayFunc(Display);
    
    glutTimerFunc(500, TimerFunc, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);    // 启用纹理
    sun = load_texture("/Users/ping/xcode_projects/project02/project02/sun.bmp");  //加载纹理
    earth = load_texture("/Users/ping/xcode_projects/project02/project02/earth.bmp");
    moon = load_texture("/Users/ping/xcode_projects/project02/project02/moon.bmp");
    
    Initial();
    
    glutMainLoop();
    
    return 0;
    
}
