#include <glad/glad.h>
#include <gl/GL.h>

#include "Shapes.h"

Shader::Shader() {
	const char* vertex_shader_text =
		"uniform mat4 Model;\n"
		"uniform mat4 View;\n"
		"uniform mat4 Project;\n"
		"attribute vec3 vCol;\n"
		"attribute vec3 vPos;\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Project * View * Model * vec4(vPos, 1.0);\n"
		"    color = vCol;\n"
		"}\n";
	const char* fragment_shader_text =
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(color, 1.0);\n"
		"}\n";

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	MVP_location[0] = glGetUniformLocation(program, "Model");
	MVP_location[1] = glGetUniformLocation(program, "View");
	MVP_location[2] = glGetUniformLocation(program, "Project");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");
}
Shader::~Shader() {

}
void Shape::init(Shader* shader) {
	this->shader = shader;
	//初始化MVP
	for (int i = 0; i < 3; i++) {
		mat4x4_identity(MVP[i]);
	}
	//初始化顶点数组对象
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//子类绑定具体的顶点数据
	bindData();
	glBindVertexArray(NULL);
}
void Shape::draw() {
	glBindVertexArray(vao);
	glUseProgram(shader->program);
	prepareMVP();
	for (int i = 0; i < 3; i++) {
		glUniformMatrix4fv(shader->MVP_location[i], 1, GL_FALSE, (const GLfloat*)MVP[i]);
	}
	drawData();
	glBindVertexArray(NULL);
}
void Shape::mvp(mat4x4 model, mat4x4 view, mat4x4 projection) {
	mat4x4_dup(MVP[0], model);
	mat4x4_dup(MVP[1], view);
	mat4x4_dup(MVP[2], projection);
}

static const PointColor co_data[6] = {
	{0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
	{0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f}
};
void Coordinate::bindData() {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(co_data), co_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader->vpos_location);
	glVertexAttribPointer(shader->vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(PointColor), (void*)0);
	glEnableVertexAttribArray(shader->vcol_location);
	glVertexAttribPointer(shader->vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(PointColor), (void*)(sizeof(float) * 3));
}
void Coordinate::prepareMVP() {
	//将坐标移动到左上角
	mat4x4 translate;
	mat4x4_translate(translate, -3.f, 3.f, 0.f);
	mat4x4_mul(MVP[0], translate, MVP[0]);
}
void Coordinate::drawData() {
	glDrawArrays(GL_LINES, 0, 6);
}

static const int NumofObjVertices = 8;
static const int NumofObjIndices = 36;
static const PointColor obj_vertices[NumofObjVertices] = {
	{-1.f, -1.f, -1.f, 1.0f, 0.0f, 0.0f},
	{ 1.f, -1.f, -1.f, 1.0f, 0.0f, 0.0f},
	{ 1.f,  1.f, -1.f, 1.0f, 0.0f, 0.0f},
	{-1.f,  1.f, -1.f, 1.0f, 0.0f, 0.0f},
	{-1.f, -1.f,  1.f, 0.0f, 1.0f, 0.0f},
	{ 1.f, -1.f,  1.f, 0.0f, 1.0f, 0.0f},
	{ 1.f,  1.f,  1.f, 0.0f, 1.0f, 0.0f},
	{-1.f,  1.f,  1.f, 0.0f, 1.0f, 0.0f},
};

static const GLuint obj_Indices[NumofObjIndices] = {
	0, 3, 2, 0, 2, 1,//前
	3, 7, 6, 3, 6, 2,//上
	3, 0, 4, 3, 4, 7,//左
	0, 1, 5, 0, 5, 4,//下
	1, 2, 6, 1, 6, 5,//右
	4, 5, 6, 4, 6, 7//后
};
void Cube::bindData() {
	GLuint vbo, ebo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vertices), obj_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader->vpos_location);
	glVertexAttribPointer(shader->vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(PointColor), (void*)0);
	glEnableVertexAttribArray(shader->vcol_location);
	glVertexAttribPointer(shader->vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(PointColor), (void*)(sizeof(float) * 3));

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj_Indices), obj_Indices, GL_STATIC_DRAW);
}
void Cube::prepareMVP() {

}
void Cube::drawData() {
	glDrawElements(GL_TRIANGLES, NumofObjIndices, GL_UNSIGNED_INT, 0);
}