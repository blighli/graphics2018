#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;                                 //天空盒以原点为中心采样，所以局部世界坐标即为纹理坐标
    gl_Position = projection * view * vec4(aPos, 1.0);
}