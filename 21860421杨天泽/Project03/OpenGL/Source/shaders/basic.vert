#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model_matrix = mat4(1);
uniform mat4 view_matrix = mat4(1);
uniform mat4 proj_matrix = mat4(1);

out vec3 pass_normal;
out vec3 fragPos;

void main(){
  gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position,1.0);
  fragPos = vec3(model_matrix * vec4(position,1.0));
  pass_normal = mat3(transpose(inverse(model_matrix))) * normal;
}
