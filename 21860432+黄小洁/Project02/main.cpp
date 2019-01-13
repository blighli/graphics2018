#include <camera.h>
#include <shader.h>
#include <sphere.h>
#include <stb_image.h>
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

using namespace std;


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
// timing
float deltaTime = 0.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadjpg(char const *path) {
    unsigned int jpgID;
    glGenTextures(1, &jpgID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(path, &width, &height, &nrComponents, STBI_rgb_alpha);
    if (image) {

        if (nrComponents == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else if (nrComponents == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glBindTexture(GL_TEXTURE_2D, jpgID);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image);
    } else {

        cout << "jpg failed to load at path: " << path << endl;
        stbi_image_free(image);
    }

    return jpgID;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Planet", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    Shader sunShader("/Users/hxj/graphics2018/21860432+黄小洁/Project02/sunshader.vs",
                     "/Users/hxj/graphics2018/21860432+黄小洁/Project02/sunshader.fs");
    Shader earthShader("/Users/hxj/graphics2018/21860432+黄小洁/Project02/earthshader.vs",
                       "/Users/hxj/graphics2018/21860432+黄小洁/Project02/earthshader.fs");
    Shader moonShader("/Users/hxj/graphics2018/21860432+黄小洁/Project02/moonshader.vs",
                      "/Users/hxj/graphics2018/21860432+黄小洁/Project02/moonshader.fs");

    Sphere mySphere(180, 90);

    //太阳
    unsigned int sunVBO, sunVAO;
    glGenVertexArrays(1, &sunVAO);
    glGenBuffers(1, &sunVBO);

    glBindVertexArray(sunVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, mySphere.vertNum * 5 * sizeof(float), mySphere.verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //地球和月亮
    unsigned int earthVBO, earthVAO;
    glGenVertexArrays(1, &earthVAO);
    glGenBuffers(1, &earthVBO);

    glBindBuffer(GL_ARRAY_BUFFER, earthVBO);
    glBufferData(GL_ARRAY_BUFFER, mySphere.vertNum * 5 * sizeof(float), mySphere.verts, GL_STATIC_DRAW);

    glBindVertexArray(earthVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //加纹理
    unsigned int sunTexture = loadjpg("/Users/hxj/graphics2018/21860432+黄小洁/Project02/sun.jpg");
    unsigned int earthDiffuse = loadjpg("/Users/hxj/graphics2018/21860432+黄小洁/Project02/earth.jpg");
    unsigned int moonDiffuse = loadjpg("/Users/hxj/graphics2018/21860432+黄小洁/Project02/moon.jpg");

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        double programTime = (float) glfwGetTime();

        //earth
        earthShader.use();
        earthShader.setVec3("light.position", lightPos);
        earthShader.setVec3("viewPos", camera.Position);

        earthShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        earthShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);

        glm::mat4 earthProjection = glm::perspective(glm::radians(camera.Zoom),
                                                     (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 earthView = camera.GetViewMatrix();
        earthShader.setMat4("projection", earthProjection);
        earthShader.setMat4("view", earthView);

        // world transformation   glm变换矩阵：代表把当前矩阵与这个变换矩阵相乘
        glm::mat4 earthModel;
        glm::vec3 earthPosition = glm::vec3(4.0 * sin(0.2 * programTime + 1), 0.0f, 4.0 * cos(0.2 * programTime + 1));
        earthModel = glm::translate(earthModel, earthPosition);
        earthModel = glm::rotate(earthModel, (float) (programTime * 0.5), glm::vec3(0.0f, 0.5f, 0.1f));
        earthModel = glm::scale(earthModel, glm::vec3(0.5, 0.5, 0.5));
        earthShader.setMat4("model", earthModel);

        // bind diffuse map
        earthShader.setInt("diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthDiffuse);

        // render the cube
        glBindVertexArray(earthVAO);
        glDrawArrays(GL_TRIANGLES, 0, int(mySphere.vertNum));

        //moon
        moonShader.use();
        moonShader.setVec3("light.position", lightPos);
        moonShader.setVec3("viewPos", camera.Position);

        moonShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        moonShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);

        glm::mat4 moonProjection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT,
                                                    0.1f, 10.0f);
        glm::mat4 moonView = camera.GetViewMatrix();
        moonShader.setMat4("projection", moonProjection);
        moonShader.setMat4("view", moonView);

        // world transformation   glm变换矩阵：代表把当前矩阵与这个变换矩阵相乘
        glm::mat4 moonModel;
        glm::vec3 moonPosition = glm::vec3(1.0 * sin(0.1 * programTime) + earthPosition.x,
                                           0.2 * sin(0.1 * programTime) + earthPosition.y,
                                           1.0 * cos(0.1 * programTime) + earthPosition.z);
        moonModel = glm::translate(moonModel, moonPosition);
        moonModel = glm::rotate(moonModel, (float) (programTime * 0.3), glm::vec3(0.5f, 0.5f, 0.0f));
        moonModel = glm::scale(moonModel, glm::vec3(0.2, 0.2, 0.2));
        moonShader.setMat4("model", moonModel);

        // bind diffuse map
        moonShader.setInt("diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, moonDiffuse);

        // render the cube
        glBindVertexArray(earthVAO);
        glDrawArrays(GL_TRIANGLES, 0, int(mySphere.vertNum));

        //太阳
        sunShader.use();
        sunShader.setInt("sun", 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTexture);

        glm::mat4 sunView;
        sunView = camera.GetViewMatrix();
        glm::mat4 sunProjection;
        sunProjection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                         100.0f);
        sunShader.setMat4("view", sunView);
        sunShader.setMat4("projection", sunProjection);

        glm::mat4 sunModel;
        glm::vec3 sunPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        sunModel = glm::translate(sunModel, sunPosition);
        sunShader.setMat4("model", sunModel);

        glBindVertexArray(sunVAO);
        glDrawArrays(GL_TRIANGLES, 0, int(mySphere.vertNum));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &sunVAO);
    glDeleteBuffers(1, &sunVBO);

    glfwTerminate();
    return 0;
}
