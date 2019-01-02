//
//  main.cpp
//  OpenGLProject2
//
//  Created by 王昊阳 on 2018/12/26.
//  Copyright © 2018 王昊阳. All rights reserved.
//

#include <iostream>
#include <glut/glut.h>
#include <math.h>

GLuint g1,g2,g3;

GLfloat sun[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat earth[] = {0.05f, 0.05f, 0.75f, 1.0f};
GLfloat moon[] = {0.85f, 0.85f, 0.85f};

GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat diffuseLignt[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightPos[] = {-0.5f, 0.0f, 0.0f, 1.0f};

int power_of_two(int n)
{
    if (n <= 0)
        return 0;
    return (n & (n - 1)) == 0;
}

GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID=0, texture_ID = 0;
    
    // 打开文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
        return 0;
    
    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, 54, SEEK_SET);
    
    // 计算每行像素所占字节数，并根据此数据计算总像素字节数
    {
        GLint line_bytes = width * 3;
        while( line_bytes % 4 != 0 )
            ++line_bytes;
        total_bytes = line_bytes * height;
    }
    
    // 根据总像素字节数分配内存
    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }
    
    // 读取像素数据
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
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
        if( !power_of_two(width)
           || !power_of_two(height)
           || width > max
           || height > max )
        {
            const GLint new_width = 256;
            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            
            // 计算每行需要的字节数和总字节数
            new_line_bytes = new_width * 3;
            while( new_line_bytes % 4 != 0 )
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            
            // 分配内存
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if( new_pixels == 0 )
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
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    
    // 绑定新的纹理，载入纹理并设置纹理参数
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    GLint lastTextureID=last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
    free(pixels);
    return texture_ID;
}

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
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
            GLfloat y = ctheta * srho;
            GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            
            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();
        
        t -= dt;
    }
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLignt);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_TEXTURE_2D);
    
    g1 = load_texture("sun.bmp");
    g2 = load_texture("earth.bmp");
    g3 = load_texture("moon.bmp");
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    
    glTranslatef(-0.5, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, g1);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun);
    gltDrawSphere(0.25, 30, 30);
    //glutSolidSphere(0.25, 30, 30);
    
    glTranslatef(1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, g2);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, earth);
    gltDrawSphere(0.15, 30, 30);
    //glutSolidSphere(0.15, 30, 30);
    
    glTranslatef(-0.2, -0.3, 0.0);
    glBindTexture(GL_TEXTURE_2D, g3);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, moon);
    gltDrawSphere(0.05, 30, 30);
    //glutSolidSphere(0.05, 30, 30);

    glutSwapBuffers();
    //glFlush();
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (140, 160);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

