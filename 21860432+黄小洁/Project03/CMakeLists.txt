cmake_minimum_required(VERSION 3.13)
project(Project03)

set(CMAKE_CXX_STANDARD 14)
# 添加头文件
set(HEAD_H /usr/local/Cellar/head)
set(GLAD_H /usr/local/Cellar/glad/include/glad)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GLM_H /usr/local/Cellar/glm/0.9.9.3/include/glm)
set(KHR_H /usr/local/Cellar/glad/include/KHR)
set(ASSIMP_H /usr/local/Cellar/assimp/4.1.0/include/assimp)
include_directories(${GLAD_H} ${HEAD_H} ${GLFW_H} ${GLM_H} ${KHR_H} ${ASSIMP_H})

# 添加目标链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/4.1.0/lib/libassimp.4.1.0.dylib)
link_libraries(${OPENGL} ${GLFW_LINK} ${ASSIMP_LINK})

set(SOURCE_FILES glad.c main.cpp )
add_executable(Project03 ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(Project03 "-framework OpenGL")
endif()