#version 440 core

layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);

out vec3 Normal;
out vec3 FragPos;

void main()
{
gl_Position =  projection_matrix * view_matrix * model_matrix * position;
Normal = normal;
FragPos = vec3(model_matrix * position);
}