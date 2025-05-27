/*
	Created by YSP on 2025-05-13.
*/
#pragma once
#include <glad/glad.h> 
#include <string>
#include <glm/glm.hpp>
#include "../Geometry/data.h"
namespace ysp {
	namespace gl {
		class Shader {
		public:
			Shader();
			GL_FUNC ~Shader();
			void GL_FUNC UseShader();
			bool GL_FUNC CreateShader(const std::string& vertexShader, const std::string& colorShader);
			void GL_FUNC SetShaderMat4(const glm::mat4& mat4, const std::string& key);
			void GL_FUNC SetShaderMat3(const glm::mat3& mat3, const std::string& key);
			void GL_FUNC SetShaderVec3(const glm::vec3& vec3, const std::string& key);
			void GL_FUNC SetShaderFloat(float value, const std::string& key);
			void GL_FUNC SetShaderInt(int value, const std::string& key);
			void GL_FUNC SetShaderBoolean(bool value, const std::string& key);
			void GL_FUNC SetShaderVec4(const glm::vec4& vec4, const std::string& key);
		private:
			GLuint GL_FUNC CreateShader(GLuint type, const std::string& strShader);
			GLuint shaderProgram;
		};
	}
}