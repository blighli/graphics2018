#version 330 core
out vec4 FragColor;

struct PointLight {
    vec3 position;
    vec3 light;
    float constant;
    float linear;
    float quadratic;
};

struct Material{
    sampler2D texture_diffuse;
};

vec3 CalcPointLight(PointLight light, vec3 normal);

#define NR_POINT_LIGHTS 1

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 ambientLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

void main(){
    // 属性
    vec3 norm = normalize(Normal);

    vec3 result = ambientLight * vec3(texture(material.texture_diffuse, TexCoords));
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm);

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal){
    vec3 lightDir = normalize(FragPos - light.position);
    // 漫反射着色
    float diff    = max(dot(normal, -lightDir), 0.0);
    vec3 diffuse  = light.light  * vec3(texture(material.texture_diffuse, TexCoords))  * diff;
    // 衰减
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return diffuse * attenuation;
}

