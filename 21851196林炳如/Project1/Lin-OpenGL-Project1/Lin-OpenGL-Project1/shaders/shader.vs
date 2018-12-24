#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 bTexCoord;

out vec2 TexCoord1;
out vec2 TexCoord2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord1 = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
	TexCoord2 = vec2(bTexCoord.x, 1.0 - bTexCoord.y);
}
