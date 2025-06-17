/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <vector>
#include <map>
#include <string>
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <iostream>
#include <fmt/core.h>
#include "../../Math/Geometry/degrees.h"
#include "../../Math/Geometry/point.h"
#include "../../Math/Geometry/vector.h"
#define GL_SHOW_TYPE_LINE2D 0x1
#define GL_SHOW_TYPE_TRIANGLE2D 0x2
#define GL_SHOW_TYPE_2D 0x3
//��һ��ֵ�ķ�Χ
#define N_MIN -0.9f
#define N_MAX 0.9f
#define GL_EBO_TYPE_VECTOR 0
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI
using namespace ysp::math::geometry;
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
            bool isParallelFov{ true }; //�Ƿ�Ϊƽ���ӿ�
            bool isRotationZ{ false };//�Ƿ���ת
            bool isMove{ false };//�Ƿ��ƶ�
            Angle rotationZ{ 0 };//��ת�Ƕ�
            Vector2D moveVector{0.0,0.0};//�ƶ�����
            double movestep{ 10.0 };//�ƶ�����
            Point3D rotationCenter{ 0.0,0.0,0.0 };//��ת����
            float parallel{ 0.83f };//ƽ���ӿ���Ұ��С
            float baseParallel{ 0.83f };//ƽ���ӿ���Ұ��С
            float fov{ M_PI / 9.0f };//�ӿ���Ұ��С
            float baseFov{ M_PI / 9.0f };//�ӿ�ԭʼ��Ұ��С
        };

        struct CameraAttribute {//�������
            glm::vec3 front{ 0.0f,0.0f,0.0f };//���������ķ��򣬿���Z��ĸ�����д����
            glm::vec3 position{ 0.0f,0.0f,0.0f }; //�������������ϵλ��
            glm::vec3 right{ 0.0f,0.0f,0.0f };//ǰ����ͺ������Ľ������
            glm::vec3 worldUp{ 0.0f,0.0f,0.0f };//��������ϵ���Ϸ����������̶����䣬�������������Z����������ˣ����Եõ�X��ķ���������д����
            glm::vec3 up{ 0.0f,0.0f,0.0f };//������ӽ���������ʾ����ı����Ϸ���
            glm::mat4 view{};//����ӽǵĹ۲���󣬶���������������ϵ�е�ģ�ͣ�������ת�������λ���� 
            glm::mat4 projection{};//͸�ӻ�ƽ���ӿ�

        };
        class Print {
        public:
            static void Vec3(const glm::vec3& vec3) {
                std::cout << fmt::format("vec3[x:{:.2f},y:{:.2f},z:{:.2f}]", vec3.x, vec3.y, vec3.z) << std::endl;
            }
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