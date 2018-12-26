#ifndef SHADER_H
#define SHADER_H
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
using namespace std;
class Shader{public:	//程序的ID	
	GLuint Program;	//读取渲染程序并创建
	Shader	Shader(const GLchar * vertexSourcePath,const GLchar *fragmentSource);	
	{		
		//1.从文件路径获得vertex/fragment源码		
		string vertexCode;		
		string fragmentCode;		
		try{			
			//打开文件Open files			
			
			ifstream vShaderFile(vertexPath);			
			ifstream fShaderFile(fragmentPath); 			
			stringstream vShaderStream,fShaderStream;			//读取文件缓冲到流、			
			vShaderStream<<vShaderFile.rdbuf();			
			fShaderStream<<fShaderFile.rdbuf(); 			//关闭文件句柄			
			vShaderFile.close();			
			fShaderFile.close();			//将流转为GLchar数组			
			vertexCode = vShaderStream.str();         
			fragmentCode = fShaderStream.str(); 		
		}		
		catch(std::exception e)     
		{         
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;      
		}		const GLchar* vShaderCode = vertexCode.c_str();        
		const GLchar * fShaderCode = fragmentCode.c_str();        // 2.编译着色器        
		GLuint vertex, fragment;        
		GLint success;        
		GLchar infoLog[512];        // 顶点着色器        
		vertex = glCreateShader(GL_VERTEX_SHADER);        
		glShaderSource(vertex, 1, &vShaderCode, NULL);        
		glCompileShader(vertex);        // 打印着色器是否错误        
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);        
		if (!success)        
		{            
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);            
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;        
		}        // 片段着色器        fragment = glCreateShader(GL_FRAGMENT_SHADER);        
		glShaderSource(fragment, 1, &fShaderCode, NULL);        
		glCompileShader(fragment);        // 打印是否有任何错误        
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);        
		if (!success)        
		{            
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);            
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;        
		}        // 着色器程序        
		this->Program = glCreateProgram();       
		glAttachShader(this->Program, vertex);        
		glAttachShader(this->Program, fragment);       
		glLinkProgram(this->Program);        // 打印是否有错误       
		
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);        
		if (!success)        
		{           
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);            
			
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;        
		}        // 删除着色器程序        
		glDeleteShader(vertex);       
		glDeleteShader(fragment);	}	//使用Program	
	void Use();	
	{glUseProgram(this->Program);	}
}
#endif
