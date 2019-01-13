#version 440 core
layout (location = 0) in vec4 aPos; // 位置变量的属性位置值为0


 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =  projection * view *model * aPos;

}