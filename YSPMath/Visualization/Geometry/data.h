/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <vector>
#include <glad/glad.h> 
#include <string>
#include <glm/glm.hpp>
#define GL_SHOW_TYPE_LINE2D 0
#define GL_SHOW_TYPE_LINE2D_AXIS 1

#define GL_EBO_TYPE_VECTOR 0
namespace ysp {
    namespace gl {
#define GL_FUNC
        struct VBOData {
            GLuint vbo{ NULL };
            std::vector<float> data;
            GLenum bufferType{ GL_ARRAY_BUFFER };
            GLint attributeIndex{ 3 }; //����ֵ��ϳ�һ��gl�����
            GLenum usage{ GL_STATIC_DRAW };
            int type;//���� �߶� ������
        };

        struct RenderData {
            int width;
            int height;
            int type;//���Ƶ�����
            void** args;
            char buffer[512];
        };
    }
}