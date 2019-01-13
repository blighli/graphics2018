#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Shader.h"
#include "Sphere.h"
using namespace std;

GLFWwindow* window;
unsigned int screenWidth = 800;
unsigned int screenHeight = 600;
// 计时器相关
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
// 观察
const float ZOOM = 45.0f;
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 position = glm::vec3(0.0f,8.0f,3.0f);
float radius = 10.0;
float u = 0, v = 30;
float sensitivity = 50.0f;
float rSensitivity = 0.5f;
// 太阳系变量
glm::vec3 sunPosition = glm::vec3(0.0f);
float sunSize   = 1;
float earthSize = 0.5;
float moonSize  = 0.2;
float sunToEarth = 3.5;
float earthToMoon = 1.2;
float v_earth_sun  = 0.1;
float v_moon_earth = 1.2;
float v_earth = 1.5;
float v_moon  = 1.2;

int initialize();
int initializeGLFW();
int initializeGLAD();
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);
glm::mat4 myperspective(float fov, float W_H_rate, float n, float f);
#define pi 3.1415926
void calculatPosition();

int main()
{
    if(!initialize())
        return -1;

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Shader shader("../src/shader/object.vs", "../src/shader/object.fs");
    shader.use();
    shader.setInt("material.texture_diffuse", 0);
    Shader lightShader("../src/shader/object.vs", "../src/shader/light.fs");
    lightShader.use();
    lightShader.setInt("material.texture_diffuse", 0);

    Sphere sph;

    unsigned int earthTexture  = loadTexture("../src/tex/earthmap1k.jpg");
    unsigned int moonTexture   = loadTexture("../src/tex/moonmap4k.jpg");
    unsigned int sunTexture    = loadTexture("../src/tex/sunmap.jpg");

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 生成观察矩阵和投影矩阵
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(position, sunPosition, up);
        glm::mat4 projection = myperspective(ZOOM, (float)screenWidth / screenHeight, 0.1f, 100.0f);
        glm::mat4 normalMat = glm::mat4(1.0f);
        // 太阳
        lightShader.use();
        model = glm::rotate(model, (float)pi/2, glm::vec3(1,0,0));
        model = glm::scale(model, glm::vec3(1.0)*sunSize);
        lightShader.setMat4("model", model);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTexture);
        sph.draw();
        // 地球和太阳
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        // 光照
        shader.setVec3("ambientLight", glm::vec3(1.0f)*0.3f);
        shader.setVec3("pointLights[0].position", sunPosition);
        shader.setVec3("pointLights[0].light",    glm::vec3(1.0f));
        shader.setFloat("pointLights[0].constant",  0.7f);
        shader.setFloat("pointLights[0].linear",    0.09f);
        shader.setFloat("pointLights[0].quadratic", 0.032f);
        // 地球
        float currentTime = glfwGetTime();
        glm::vec3 earthPosition = glm::vec3(cos(currentTime*v_earth_sun),0.0,sin(currentTime*v_earth_sun))*sunToEarth;
        model = glm::mat4(1.0f);
        model = glm::translate(model, earthPosition);
        model = glm::rotate(model, (float)glfwGetTime()*v_earth, glm::vec3(0,1,0));
        model = glm::rotate(model, (float)pi/2, glm::vec3(1,0,0));
        model = glm::scale(model, glm::vec3(1.0)*earthSize);
        normalMat = glm::transpose(glm::inverse(model));
        shader.setMat4("model", model);
        shader.setMat4("normalMat", normalMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTexture);
        sph.draw();
        // 月球
        glm::vec3 moonPosition = glm::vec3(cos(currentTime*v_moon_earth),0.0,sin(currentTime*v_moon_earth))*earthToMoon;
        model = glm::mat4(1.0f);
        model = glm::translate(model, earthPosition+moonPosition);
        model = glm::rotate(model, (float)glfwGetTime()*v_moon, glm::vec3(0,1,0));
        model = glm::rotate(model, (float)pi/2, glm::vec3(1,0,0));
        model = glm::scale(model, glm::vec3(1.0)*moonSize);
        normalMat = glm::transpose(glm::inverse(model));
        shader.setMat4("model", model);
        shader.setMat4("normalMat", normalMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, moonTexture);
        sph.draw();
        // 应用程序采用着双缓冲模式，一张在前面显示，一张在后面慢慢加载
        // Swap交换缓冲，完成立刻刷新
        glfwSwapBuffers(window);
    }

    // 释放glfw的资源
    glfwTerminate();

    return 0;
}

int initialize(){
    // 初始化GLFW
    if(!initializeGLFW())
        return 0;
    // 初始化GLAD
    if(!initializeGLAD())
        return 0;
    return 1;
}

int initializeGLFW(){
    // 初始GLFW，设置版本号为3.3，使用核心模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 创建一个窗口，将窗口的上下文应用到当前的主上下文
    window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return 0;
    }   
    glfwMakeContextCurrent(window);
    return 1;
}

int initializeGLAD(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return 0;
    }
    return 1;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // 获得渲染时间，保证速度相同
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    // 键盘移动
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        v -= sensitivity * deltaTime;
        if(v <= 0)
            v = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        v += sensitivity * deltaTime;
        if(v > 180)
            v = 179;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        u -= sensitivity * deltaTime;
        if(u < 0)
            u += 360;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        u += sensitivity * deltaTime;
        if(u > 360)
            u -= 360;
    }
    calculatPosition();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    screenWidth  = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    radius += (yoffset * rSensitivity);
    if(radius <= 2)
        radius = 2;
    if(radius > 30)
        radius = 30;
}

unsigned int loadTexture(const char *path){
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data){
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        if(nrComponents == 1){
            GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_ZERO};
            glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }else{
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

glm::mat4 myperspective(float fov, float W_H_rate, float n, float f){
    float radi = pi / 180.0 * fov;
    float cotV = 1.0 / tan(radi/2);
    float h_near = n / sqrtf((powf(cotV, 2) - powf(W_H_rate, 2)));
    float w_near = h_near * W_H_rate;
    glm::mat4 projection = glm::mat4(0.0f);
    projection[0][0] = n / w_near;
    projection[1][1] = n / h_near;
    projection[2][2] = -1 * (f + n) / (f - n);
    projection[3][2] = -2 * f * n / (f - n);
    projection[2][3] = -1;
    return projection;
}

void calculatPosition(){
    float tem = radius * sin(glm::radians(v));
    position.x = tem * sin(glm::radians(u));
    position.y = radius * cos(glm::radians(v));
    position.z = tem * cos(glm::radians(u));
}