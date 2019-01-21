//
//  main.cpp
//  Project02
//
//  Created by wxaaaa on 2018/12/29.
//  Copyright © 2019 wxaaaa. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
//#include <GL/glaux.h>


#define imageWidth 64
#define imageHeight 64
#define BMP_Header_Length 54

static int width = 1200, height = 600;
static int pX = 100, pY=100;
static GLubyte image[imageHeight][imageWidth][4];
static GLuint earth;
static GLuint sun;
static GLuint moon;

static int year = 0, day = 0, month = 0, angle = 0;

GLuint load_texture(const char* file_name);

int LoadTexture()
{
    // 产生和绑定纹理
    earth = load_texture("earth.bmp");
    
    // 产生和绑定纹理
    glGenTextures(1, &sun);
    glBindTexture(GL_TEXTURE_2D, sun);
    
    //    AUX_RGBImageRec *TexImage2 = auxDIBImageLoad("mt.bmp");
    //    if (NULL == TexImage2) return false;       // 如果失败，返回false
    //    glTexImage2D(GL_TEXTURE_2D, 0, 3, TexImage2->sizeX, TexImage2->sizeY,
    //                 0, GL_RGB, GL_UNSIGNED_BYTE, TexImage2->data);
    
    // 设置纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // 产生和绑定纹理
    glGenTextures(1, &moon);
    glBindTexture(GL_TEXTURE_2D, moon);
    
    // 设置纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}


void makeImage(void){
    int i, j, c;
    
    for (i = 0; i < imageHeight; i++){
        for (j = 0; j < imageWidth; j++){
            c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            image[i][j][0] = (GLubyte)c;
            image[i][j][1] = (GLubyte)c;
            image[i][j][2] = (GLubyte)c;
            image[i][j][3] = (GLubyte)225;
        }
    }
}

void init(void)
{
    // 定纹理的颜色与物体的原来颜色的混合方式
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    // 添加纹理映射支持
    glEnable(GL_TEXTURE_2D);
    
    if (!LoadTexture())
    {
        exit(0);
    }
    
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 0.0, 0.0, 0.5 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };
    
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
}

void display(void)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glBindTexture(GL_TEXTURE_2D, texName);
    // 纹理映射开关，为阴影贴图的投影设置视觉平面，表示opengl的纹理坐标
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    glPushMatrix();
    
    glBindTexture(GL_TEXTURE_2D, sun);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(1.0, 40, 32);
    //glutWireSphere(1.0, 20, 16);   // draw sun
    
    glPushMatrix();
    
    glRotatef ((GLfloat) month, 0.0, 1.0, 0.0);
    glTranslatef (2.0, 0.0, 0.0);
    
    glPushMatrix();
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    
    glBindTexture(GL_TEXTURE_2D, earth);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.2, 20, 16);
//    glutWireSphere(0.2, 10, 8);    // draw earth
    glPopMatrix();
    
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    
    glBindTexture(GL_TEXTURE_2D, moon);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(0.1, 20, 16);
    //glutWireSphere(0.1, 10, 8);     // draw moon
    
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'd':
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case 'D':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        case 'm':
            month = (month + 5) % 360;
            glutPostRedisplay();
            break;
        case 'M':
            month = (month + 5) % 360;
            glutPostRedisplay();
            break;
        case 's':
            angle = (angle + 8) % 360;
            glutPostRedisplay();
            break;
        case 'S':
            angle = (angle - 8 + 360) % 360;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (pX, pY);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

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
    
    GLint last_texture_ID;//上一次绑定的纹理编号
    GLuint texture_ID = 0;//纹理编号
    
    // 打开参数中传入的纹理文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if (pFile == 0)
        return 0;
    
    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);//int32 8位4个字节
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
    
    // 在旧版本的OpenGL中
    // 如果图象的宽度和高度不是的整数次方，则需要进行缩放
    // 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
    // 另外，无论是旧版本还是新版本，
    // 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);//获取支持的最大纹理
        
        //如果长宽有一个不是整数次方，或有一个大于支持的最大纹理，就重新设置长宽重新算一遍
        if (!power_of_two(width) || !power_of_two(height) || width > max || height > max)
        {
            //设定一些用于中间计算的新的值，这些值会在稍后被替代
            
            const GLint new_width = 256;
            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            
            // 计算每行需要的字节数和总字节数
            new_line_bytes = new_width * 3;
            while (new_line_bytes % 4 != 0)
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            
            // 重新分配内存
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if (new_pixels == 0)
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }
            
            // 进行像素缩放
            gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, pixels,
                          new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
            
            // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
            free(pixels);
            
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }
    
    // 分配一个新的纹理编号，并不是分配编号1，而是分配1个新的编号到textureID....
    glGenTextures(1, &texture_ID);
    
    if (texture_ID == 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    
    // 绑定新的纹理，载入纹理并设置纹理参数
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID); //第一个参数，表示你要得到什么状态的值,第二个参数即输出这个值
    
    glBindTexture(GL_TEXTURE_2D, texture_ID);//状态机，选定当前的纹理状态，以后的操作都是基于这个纹理
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //模型比纹理小了怎么办
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //模型比纹理大了怎么办
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //x坐标越界怎么办，GL_CLAMP表示超过的1.0的都按1.0那点的坐标绘制，GL_REPEAT表示不足重复补充直至达到那个值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //y坐标越界怎么办，重复
    GLfloat fColor[4] = { 1.0f,0.0f,0.0f,0.0f };
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, fColor);
    
    //载入pixels数组中的图像为当前的纹理状态
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    
    //glBindTexture(GL_TEXTURE_2D, last_texture_ID);
    
    // 之前为pixels分配的内存可在使用glTexImage2D以后释放
    // 因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中）
    free(pixels);
    //该ID可以唯一标识一纹理
    return texture_ID;
}
