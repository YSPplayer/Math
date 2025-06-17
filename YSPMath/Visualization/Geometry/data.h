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
//归一化值的范围
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
            std::map<std::string,std::vector<uint32_t>> includes;//特殊点索引
            GLenum bufferType{ GL_ARRAY_BUFFER };
            GLint attributeIndex{ 3 }; //几个值组合成一个gl点对象
            GLenum usage{ GL_STATIC_DRAW };
            int type;//类型 线段 或其他
        };

        struct RenderData {
            int width;
            int height;
            float x{0.0f};//当前菜单栏宽度
            float y{0.0f};//当前菜单栏高度
            int type;//绘制的种类
            void** args;
            char buffer[512];
            bool isParallelFov{ true }; //是否为平行视口
            bool isRotationZ{ false };//是否旋转
            bool isMove{ false };//是否移动
            Angle rotationZ{ 0 };//旋转角度
            Vector2D moveVector{0.0,0.0};//移动向量
            double movestep{ 10.0 };//移动步长
            Point3D rotationCenter{ 0.0,0.0,0.0 };//旋转中心
            float parallel{ 0.83f };//平行视口视野大小
            float baseParallel{ 0.83f };//平行视口视野大小
            float fov{ M_PI / 9.0f };//视口视野大小
            float baseFov{ M_PI / 9.0f };//视口原始视野大小
        };

        struct CameraAttribute {//相机属性
            glm::vec3 front{ 0.0f,0.0f,0.0f };//摄像机看向的方向，看向Z轴的负方向【写死】
            glm::vec3 position{ 0.0f,0.0f,0.0f }; //相机的世界坐标系位置
            glm::vec3 right{ 0.0f,0.0f,0.0f };//前方向和后方向计算的结果向量
            glm::vec3 worldUp{ 0.0f,0.0f,0.0f };//世界坐标系的上方向向量，固定不变，根据这个向量与Z方向向量叉乘，可以得到X轴的方向向量【写死】
            glm::vec3 up{ 0.0f,0.0f,0.0f };//相机的视角向量，表示相机的本地上方向
            glm::mat4 view{};//相机视角的观察矩阵，对于任意世界坐标系中的模型，都可以转换到这个位置中 
            glm::mat4 projection{};//透视或平行视口

        };
        class Print {
        public:
            static void Vec3(const glm::vec3& vec3) {
                std::cout << fmt::format("vec3[x:{:.2f},y:{:.2f},z:{:.2f}]", vec3.x, vec3.y, vec3.z) << std::endl;
            }
        };
       
        class Color {
        private:
            unsigned char r, g, b, a;  // 0-255范围

        public:
            // 构造函数
            Color() : r(0), g(0), b(0), a(255) {}
            Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
                : r(red), g(green), b(blue), a(alpha) {}

            // 获取颜色分量
            unsigned char R() const { return r; }
            unsigned char G() const { return g; }
            unsigned char B() const { return b; }
            unsigned char A() const { return a; }

            // 设置颜色分量
            void SetR(unsigned char value) { r = value; }
            void SetG(unsigned char value) { g = value; }
            void SetB(unsigned char value) { b = value; }
            void SetA(unsigned char value) { a = value; }

            // 归一化颜色值到0.0-1.0范围
            float RF() const { return r / 255.0f; }
            float GF() const { return g / 255.0f; }
            float BF() const { return b / 255.0f; }
            float AF() const { return a / 255.0f; }

            // 整体设置颜色
            void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) {
                r = red; g = green; b = blue; a = alpha;
            }
        };


    }
}