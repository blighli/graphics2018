#version 330 core

out vec4 FragColor;           //片段颜色
in vec3 Normal;				  //片段法向量
in vec3 FragPos;             //片段位置
uniform vec3 lightColor;    //光线颜色
uniform vec3 objectColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
uniform vec3 lightPos;    // 光源位置
uniform vec3 viewPos;     //观察者位置

vec3 norm = normalize(Normal);              //法向量标准化
vec3 lightDir = normalize(lightPos - FragPos);     //单位光线方向向量，片段指向光源
vec3 viewDir = normalize(viewPos - FragPos);       //观察者视线单位向量,片段指向观察者
vec3 reflectDir = reflect(-lightDir, norm);        //反射光方向向量

void main()
{
    float specularStrength = 0.5;                    //镜面强度
	float spec = pow(max(dot(viewDir, reflectDir),0.0),256); //镜面分量
	vec3 specular = specularStrength * spec *lightColor;   //镜面反射光
	float diff = max(dot(norm, lightDir),0.0);       //漫反射因子
	vec3 diffuse = lightColor * diff;                //漫反射光强
	float ambientStrength = 0.1;                     //环境光因子
	vec3 ambient = ambientStrength * lightColor;     //环境光强
    FragColor = vec4((ambient+diffuse+specular) * objectColor, 1.0);   //最终颜色
}