#version 440 core

layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 aTexCoord;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);

out vec3 Normal;
out vec2 TexCoord;

void main()
{
gl_Position =  projection_matrix * view_matrix * model_matrix * position;
Normal = normal;
TexCoord = aTexCoord;
}