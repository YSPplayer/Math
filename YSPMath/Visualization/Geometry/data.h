/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <vector>
#include <map>
#include <glad/glad.h> 
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
            std::map<std::string,std::vector<uint32_t>> includes;//���������
            GLenum bufferType{ GL_ARRAY_BUFFER };
            GLint attributeIndex{ 3 }; //����ֵ��ϳ�һ��gl�����
            GLenum usage{ GL_STATIC_DRAW };
            int type;//���� �߶� ������
        };

        struct RenderData {
            int width;
            int height;
            float x{0.0f};//��ǰ�˵������
            float y{0.0f};//��ǰ�˵����߶�
            int type;//���Ƶ�����
            void** args;
            char buffer[512];
        };

        class Color {
        private:
            unsigned char r, g, b, a;  // 0-255��Χ

        public:
            // ���캯��
            Color() : r(0), g(0), b(0), a(255) {}
            Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
                : r(red), g(green), b(blue), a(alpha) {}

            // ��ȡ��ɫ����
            unsigned char R() const { return r; }
            unsigned char G() const { return g; }
            unsigned char B() const { return b; }
            unsigned char A() const { return a; }

            // ������ɫ����
            void SetR(unsigned char value) { r = value; }
            void SetG(unsigned char value) { g = value; }
            void SetB(unsigned char value) { b = value; }
            void SetA(unsigned char value) { a = value; }

            // ��һ����ɫֵ��0.0-1.0��Χ
            float RF() const { return r / 255.0f; }
            float GF() const { return g / 255.0f; }
            float BF() const { return b / 255.0f; }
            float AF() const { return a / 255.0f; }

            // ����������ɫ
            void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) {
                r = red; g = green; b = blue; a = alpha;
            }
        };


    }
}