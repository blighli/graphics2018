cmake_minimum_required(VERSION 3.13)
project(Project02)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件
# head include camera.h sphere.h shader.h stb_image.h
set(HEAD_H /usr/local/Cellar/head)
set(GLAD_H /usr/local/Cellar/glad/include/glad)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GLM_H /usr/local/Cellar/glm/0.9.9.3/include/glm)
set(KHR_H /usr/local/Cellar/glad/include/KHR)
include_directories(${GLAD_H} ${HEAD_H} ${GLFW_H} ${GLM_H} ${KHR_H})

# 添加目标链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLFW_LINK})

set(SOURCE_FILES glad.c main.cpp stb_image.cpp)
add_executable(Project02 ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(Project02 "-framework OpenGL")
endif()
