/*
	Created by YSP on 2025-05-13.
*/
#include "shader.h"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
namespace ysp {
	namespace gl {
		Shader::Shader() {
			shaderProgram = NULL;
		}

		Shader::~Shader() {
			//释放着色器管理对象内存
			if (shaderProgram) glDeleteProgram(shaderProgram);
		}

		void Shader::UseShader() {
			glUseProgram(shaderProgram);
		}

		/// <summary>
		/// 绑定顶点着色器+片段着色器对象
		/// </summary>
		/// <param name="vertexShader"></param>
		/// <param name="colorShader"></param>
		/// <returns></returns>
		bool Shader::CreateShader(const std::string& vertexShader, const std::string& colorShader) {
			shaderProgram = glCreateProgram();//着色器程序对象，用于管理多个着色器对象
			GLuint vShader = CreateShader(GL_VERTEX_SHADER, vertexShader); //顶点着色器
			GLuint cShader = CreateShader(GL_FRAGMENT_SHADER, colorShader); //片段着色器
			if (vShader && cShader) {
				glAttachShader(shaderProgram, vShader);
				glAttachShader(shaderProgram, cShader);
				glLinkProgram(shaderProgram);
				glValidateProgram(shaderProgram);
				//链接完成之后释放指针内存
				glDeleteShader(vShader);
				glDeleteShader(cShader);
				int success = 0;
				glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
				char infoLog[512];
				if (!success) {//编译失败
					glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); // 使用glGetProgramInfoLog而不是glGetShaderInfoLog
					std::cout << "[Error]{Shader::CreateShader} Linking failed:\n" << infoLog << std::endl;
					return false;
				}
				return true;
			}
			return false;
		}

		/// <summary>
		/// 设置shader全局变量
		/// </summary>
		/// <param name="mat4"></param>
		/// <param name="key"></param>
		void Shader::SetShaderMat4(const glm::mat4& mat4, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
		}

		void Shader::SetShaderMat3(const glm::mat3& mat3, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat3));
		}

		void Shader::SetShaderVec3(const glm::vec3& vec3, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniform3fv(loc, 1, glm::value_ptr(vec3));
		}

		void Shader::SetShaderVec4(const glm::vec4& vec4, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniform4fv(loc, 1, glm::value_ptr(vec4));
		}

		void Shader::SetShaderFloat(float value, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniform1f(loc, value);
		}

		void Shader::SetShaderInt(int value, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniform1i(loc, value);
		}

		/// <summary>
		/// 设置shader中的布尔变量
		/// </summary>
		/// <param name="value"></param>
		/// <param name="key"></param>
		void Shader::SetShaderBoolean(bool value, const std::string& key) {
			int loc = glGetUniformLocation(shaderProgram, key.c_str());
			glUniform1i(loc, value ? GL_TRUE : GL_FALSE);
		}

		/// <summary>
		/// 创建单个的着色器对象
		/// </summary>
		/// <param name="type"></param>
		/// <param name="strShader"></param>
		/// <returns></returns>
		GLuint Shader::CreateShader(GLuint type, const std::string& strShader) {
			GLuint shader;
			shader = glCreateShader(type); //创建一个着色器对象
			const char* source = strShader.c_str(); //shader代码
			glShaderSource(shader, 1, &source, NULL);//传入shader代码进行编译
			glCompileShader(shader);
			int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {//编译失败
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); // 使用glGetProgramInfoLog而不是glGetShaderInfoLog
				std::cout << "[Error]{Shader::CreateShader_2} Linking failed:\n" << infoLog << std::endl;
				return false;
			}
			return shader;
		}

	}
}