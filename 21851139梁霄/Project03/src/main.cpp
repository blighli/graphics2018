#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "CameraModel.h"
using namespace std;

GLFWwindow* window;
unsigned int screenWidth = 800;
unsigned int screenHeight = 600;
// 计时器相关
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
// 创建摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
CameraModel cameramodel;
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;
// 光源位置
glm::vec3 pointLightPositions[] = {
    glm::vec3( 5.0f,  0.0f,  0.0f),
    glm::vec3(-5.0f,  0.0f,  0.0f),
    glm::vec3( 0.0f,  5.0f,  0.0f),
    glm::vec3( 0.0f, -5.0f,  0.0f),
    glm::vec3( 0.0f,  0.0f,  5.0f),
    glm::vec3( 0.0f,  0.0f, -5.0f)
};
// 观察状态
bool spotlight = true;
bool viewState = true; // true 自由漫游 false 以模型为中心
bool pressState1 = false;
bool pressState2 = false;
// 模型状态
float scale = 0.1f;
float scaleV = 0.08f;

int initialize();
int initializeGLFW();
int initializeGLAD();
void makeCube(unsigned int VAO);
void makeLight(unsigned int VAO);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

int main()
{
    if(!initialize())
        return -1;

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Shader colorShader("../src/shader/2.color.vs", "../src/shader/2.color.fs");
    Shader lampShader("../src/shader/1.lamp.vs", "../src/shader/1.lamp.fs");

    unsigned int VAOLight;
    glGenVertexArrays(1, &VAOLight);
    makeLight(VAOLight);
    Model nanosuit = Model("../src/model/nanosuit/nanosuit.obj");

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // 生成观察矩阵和投影矩阵
        glm::mat4 model, view, projection;
        if(viewState)
        {
            model = glm::mat4(1.0f);
            view = camera.GetViewMatrix();
            projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / screenHeight, 0.1f, 100.0f);
        }else
        {
            model = glm::mat4(1.0f);
            view = cameramodel.GetViewMatrix();
            projection = glm::perspective(glm::radians(cameramodel.Zoom), (float)screenWidth / screenHeight, 0.1f, 100.0f);
        }

        // 绘制物体
        colorShader.use();
        // 片段着色器所需的参数
        if(viewState)
            colorShader.setVec3("viewPos", camera.Position);
        else
            colorShader.setVec3("viewPos", cameramodel.Position);
        // dir light
        colorShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        colorShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        colorShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        colorShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light
        for(int i=0; i<6; i++)
        {
            string lightname = "pointLights[" + to_string(i) + "]";
            colorShader.setVec3(lightname+".position", pointLightPositions[i]);
            colorShader.setVec3(lightname+".ambient", 0.05f, 0.05f, 0.05f);
            colorShader.setVec3(lightname+".diffuse", 0.8f, 0.8f, 0.8f);
            colorShader.setVec3(lightname+".specular", 1.0f, 1.0f, 1.0f);
            colorShader.setFloat(lightname+".constant", 1.0f);
            colorShader.setFloat(lightname+".linear", 0.09);
            colorShader.setFloat(lightname+".quadratic", 0.032);           
        }
        // spotLight
        if(spotlight)
        {
            colorShader.setVec3("spotLight.position", camera.Position);
            colorShader.setVec3("spotLight.direction", camera.Front);
            colorShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            colorShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            colorShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            colorShader.setFloat("spotLight.constant", 0.5f);
            colorShader.setFloat("spotLight.linear", 0.09);
            colorShader.setFloat("spotLight.quadratic", 0.032);
            colorShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            colorShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        }else
        {
            colorShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            colorShader.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
            colorShader.setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
        }
        // 顶点着色器需要的参数
        model = glm::translate(model, glm::vec3(0.0f,-10.0f,0.0f)*scale);
        model = glm::scale(model, glm::vec3(1.f)*scale);
        colorShader.setMat4("model", model);
        colorShader.setMat4("view", view);
        colorShader.setMat4("projection", projection);
        glm::mat4 normalMat = glm::transpose(glm::inverse(model)); // 法线矩阵
        colorShader.setMat4("normalMat", normalMat);
        colorShader.setFloat("material.shininess", 32.0f);
        nanosuit.Draw(colorShader);

        // 绘制光源
        lampShader.use();
        // 顶点着色器需要的参数
        lampShader.setMat4("view", view);
        lampShader.setMat4("projection", projection);
        for(unsigned int i = 0; i < 6; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.setMat4("model", model);
            glBindVertexArray(VAOLight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void makeCube(unsigned int VAO){
    glBindVertexArray(VAO);
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void makeLight(unsigned int VAO){
    makeCube(VAO);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // 获得渲染时间，保证速度相同
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    // 键盘移动
    if(viewState)
    {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }else
    {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameramodel.ProcessKeyboard(FORWARD, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameramodel.ProcessKeyboard(BACKWARD, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameramodel.ProcessKeyboard(LEFT, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameramodel.ProcessKeyboard(RIGHT, deltaTime);
    }
    // 开关手电筒
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if(!pressState1)
            spotlight = (spotlight)?false:true;
        pressState1 = true;
    }else
    {
        pressState1 = false;
    }
    // 转变观察方式
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if(!pressState2)
            viewState = (viewState)?false:true;
        pressState2 = true;
    }else
    {
        pressState2 = false;
    }
    // 模型放大缩小
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        scale += scaleV * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        scale -= scaleV * deltaTime;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // y的坐标是上面小，下面大
    lastX = xpos;
    lastY = ypos;
    if(viewState)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if(viewState)
        camera.ProcessMouseScroll(yoffset);
    else
        cameramodel.ProcessMouseScroll(yoffset);
}