#version 400 core

layout (location = 0) in vec3 position;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA {
	vec4 color;
}vs_out;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
	vs_out.color = vec4(0.6f, 0.2f, 0.2f, 1.0f);
}