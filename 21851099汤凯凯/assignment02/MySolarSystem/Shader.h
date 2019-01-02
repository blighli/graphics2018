//
//  main.m
//  assignment02
//
//  Created by 汤凯凯 on 2018/12/26.
//  Copyright © 2019 汤凯凯. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader {
public:

	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();
};

#endif // !SHADER_H
