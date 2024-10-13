#ifndef SHADER_H
#define SHALDER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
	public:
		unsigned int ID;
		Shader(const char* vertexPath, const char* fragmentPath){
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try{
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;

				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch(std::ifstream::failure e){
				std::cout << "Error in Shader, file couldn't be read" << std::endl;
			}

			const char* vShaderCode = vertexCode.c_str();
			const char* fShaderCode = fragmentCode.c_str();

			unsigned int vertex, fragment;
			int success;
			char infoLog[512];

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				std::cout << "Error in Shader, couldn't compile vertex shaders" << std::endl;
			}

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				std::cout << "Error in Shader, couldn't compile fragment shaders" << std::endl;
			}

			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);

			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if(!success){
				glGetProgramInfoLog(ID, 512, NULL, infoLog);
				std::cout << "Error in Shader, failed linking" << std::endl;
			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		void use(){
			glUseProgram(ID);
		}

		void setBool(const std::string &name, bool value)const{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}

		void setInt(const std::string &name, int value)const{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}

		void setFloat(const std::string &name, float value)const{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
};

#endif
