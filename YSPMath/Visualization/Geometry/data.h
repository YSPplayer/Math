/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <vector>
#include <glad/glad.h> 
#include <string>
#include <glm/glm.hpp>
#define GL_SHOW_TYPE_LINE2D 0

#define GL_EBO_TYPE_VECTOR 0
namespace ysp {
    namespace gl {
        struct VBOData {
            GLuint vbo{ NULL };
            std::vector<float> data;
            GLenum bufferType{ GL_ARRAY_BUFFER };
            GLint attributeIndex{ 3 }; //几个值组合成一个gl点对象
            GLenum usage{ GL_STATIC_DRAW };
            int type;//类型 线段 或其他
        };
    }
}