/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <vector>
#include <glad/glad.h> 
#include <string>
#include <glm/glm.hpp>
namespace ysp {
    namespace gl {
        struct EBOData {
            GLuint vbo{ NULL };
            std::vector<float> data;
            GLenum bufferType{ 0 };
            GLint attributeIndex{ 0 };
            GLenum usage{ 0 };
        };
    }
}