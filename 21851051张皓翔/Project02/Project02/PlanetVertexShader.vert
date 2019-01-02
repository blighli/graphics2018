#version 450 core
layout (location = 0) in vec3 vPosition;   
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 normal;

out vec2 textCoordination;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
	fragPos = vec3(model * vec4(vPosition, 1.0));
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	fragNormal = normalMatrix * normal;   
	textCoordination = textCoord;

}