#version 440 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 perspective_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);



out vec3 Normal;
out vec3 FragPos;


out vec2 texPos;

void main(){

	//¼ÆËãÎÆÀí×ø±ê
	texPos = texCoord;
	texPos.y = 1 - texPos.y;


	Normal = mat3(transpose(inverse(model_matrix))) * vec3(normal);  

	gl_Position = perspective_matrix * view_matrix * model_matrix * position;

	FragPos = vec3(model_matrix * position);

}