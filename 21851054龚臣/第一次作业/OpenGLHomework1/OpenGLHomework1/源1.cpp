
//#include<GL\glew.h>
#include <GLFW/glfw3.h>
#include<glad\glad.h>
#include<vmath.h>
#include <iostream>

#pragma comment(lib,"OpenGL32.lib")

using namespace std;
using namespace vmath;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * vec4(aPos,1.0);\n"
"}\0";



const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);



int main()
{

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);


    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, -0.5f, 
        -0.5f, 0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f, 

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 

        -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f, 

        -0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, -0.5f, 
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    while (!glfwWindowShouldClose(window))
    {
		//glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4 view;
        mat4 projection;

		//透视投影
		projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.0f);

		view = lookat(cameraPos, cameraFront + cameraPos, cameraUp);

		glUseProgram(shaderProgram);

		GLint viewPosition = glGetUniformLocation(shaderProgram, "view");
		GLint projectionPosition = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(viewPosition, 1, GL_FALSE,&view[0][0]);
		glUniformMatrix4fv(projectionPosition, 1, GL_FALSE, &projection[0][0]);

        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 36);
		//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

//鼠标滑动的时候X轴模仿yaw Y轴模仿pitch 获得front向量的三个方向
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoff = (float)xpos - lastX;
	float yoff = (float)ypos - lastY;
	lastX = (float)xpos;
	lastY = (float)ypos;

	float sensitive = 0.1f;
	xoff *= sensitive;
	yoff *= sensitive;

	yaw += xoff;
	pitch += yoff;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	vec3 front;
	front[0] = cos(radians(yaw)) * cos(radians(pitch));
	front[1] = sin(radians(pitch));
	front[2] = sin(radians(yaw)) * cos(radians(pitch));
	cameraFront = normalize(front);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

