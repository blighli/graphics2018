#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D texture_diffuse;
};

in vec2 TexCoords;

uniform Material material;

void main(){
    vec3 result = vec3(texture(material.texture_diffuse, TexCoords));
    FragColor = vec4(result, 1.0);
}

