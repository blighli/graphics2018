#version 440 core

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float increase;
uniform vec2 temp;
void main()
{
	
    FragColor = texture(ourTexture,TexCoord)*vec4(increase,increase,increase,1.0f);
}