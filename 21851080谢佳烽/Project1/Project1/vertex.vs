#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexcoord;

out vec2 outTexcoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(aPos,1.0);
   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);
};
