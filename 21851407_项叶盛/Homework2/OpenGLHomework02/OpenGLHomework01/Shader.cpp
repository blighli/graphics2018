#include <iostream>
#include "Shader.h"

bool compileShader(const char* text, GLuint& shader, GLenum shaderType) {
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		char buffer[4096];
		glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
		std::cout << (shaderType == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << std::endl;
		std::cout << buffer << std::endl;
		return false;
	}
	return true;
}

Shader::Shader() {
	const char* vertex_shader_text =
		"#version 430 core\n"
		"uniform mat4 Model;\n"
		"uniform mat4 View;\n"
		"uniform mat4 Project;\n"
		"attribute vec3 vPos;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Project * View * Model * vec4(vPos, 1.0);\n"
		"}\n";
	const char* fragment_shader_text =
		"#version 430 core\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n";
	if (!compileShader(vertex_shader_text, vertex_shader, GL_VERTEX_SHADER)) {
		exit(EXIT_FAILURE);
	}
	if (!compileShader(fragment_shader_text, fragment_shader, GL_FRAGMENT_SHADER)) {
		exit(EXIT_FAILURE);
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	MVP_location[0] = glGetUniformLocation(program, "Model");
	MVP_location[1] = glGetUniformLocation(program, "View");
	MVP_location[2] = glGetUniformLocation(program, "Project");
	vpos_location = glGetAttribLocation(program, "vPos");
}
Shader::~Shader() {

}

void Shader::setMVP(mat4x4 model, mat4x4 view, mat4x4 projection)
{
	glUniformMatrix4fv(MVP_location[0], 1, GL_FALSE, (const GLfloat*)model);
	glUniformMatrix4fv(MVP_location[1], 1, GL_FALSE, (const GLfloat*)view);
	glUniformMatrix4fv(MVP_location[2], 1, GL_FALSE, (const GLfloat*)projection);
}

LightShader::LightShader()
{
	const char* vertex_shader_text =
		"#version 430 core\n"
		"uniform mat4 Model;\n"
		"uniform mat4 View;\n"
		"uniform mat4 Project;\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 tex_coord;\n"
		"\n"
		"out vec2 vs_tex_coord;\n"
		"out vec3 vs_worldpos;\n"
		"out vec3 vs_normal;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = Project * View * Model* position;\n"
		"    vs_worldpos = gl_Position.xyz;\n"
		"    vs_normal = mat3(View * Model) * normal;\n"
		"    vs_tex_coord = tex_coord;\n"
		"}\n";
	const char* fragment_shader_text =
		"#version 430 core\n"
		"uniform sampler2D Texture;\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"in vec2 vs_tex_coord;\n"
		"in vec3 vs_worldpos;\n"
		"in vec3 vs_normal;\n"
		"\n"
		"uniform vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0);\n"
		"uniform float shininess = 77.0f;\n"
		"\n"
		"uniform vec3 light_position = vec3(0f, 0f, 0f);\n"
		"\n"
		"void main(void)\n"
		"{\n"
		//光照方向
		"    vec3 light_direction = normalize(light_position - vs_worldpos);\n"
		//顶点法向量
		"    vec3 normal = normalize(vs_normal);\n"
		"    vec3 half_vector = normalize(light_direction + normalize(vs_worldpos));\n"
		"    float diffuse = max(0.0, dot(normal, light_direction));\n"
		"    float specular = pow(max(0.0, dot(vs_normal, half_vector)), shininess);\n"
		//"	 color = texture(Texture, vs_tex_coord) + vec4(0.2, 0.2, 0.2, 1.0);\n"
		"	 vec4 tex_color = texture(Texture, vs_tex_coord);\n"
		//"    color = tex_color + diffuse * tex_color + specular * tex_color;\n"
		"    color = ambient * tex_color + diffuse * tex_color + specular * tex_color;\n"
		//"    color = ambient * tex_color ;\n"
		"}\n";

	if (!compileShader(vertex_shader_text, vertex_shader, GL_VERTEX_SHADER)) {
		exit(EXIT_FAILURE);
	}
	if (!compileShader(fragment_shader_text, fragment_shader, GL_FRAGMENT_SHADER)) {
		exit(EXIT_FAILURE);
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	MVP_location[0] = glGetUniformLocation(program, "Model");
	MVP_location[1] = glGetUniformLocation(program, "View");
	MVP_location[2] = glGetUniformLocation(program, "Project");
}

LightShader::~LightShader()
{
}
