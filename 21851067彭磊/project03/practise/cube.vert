#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);    //立方体位置
	FragPos = vec3(model * vec4(aPos, 1.0));                      //片段位置在世界坐标系下
	Normal = mat3(transpose(inverse(model)))*aNormal;
	TexCoords = aTexCoords;
}