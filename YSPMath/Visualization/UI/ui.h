/*
    Created by YSP on 2025-05-23.
*/
#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
#include "../Geometry/data.h"
#include <imgui/imgui.h>
#include "style.h"
#include "../Geometry/scene.h"
#include "../../Math/Geometry/point.h"
using namespace ysp::gl::geometry;
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace ui {
            class Ui {
            public:
                Ui();
                void Init(GLFWwindow* window, Scene* pscene);
                void Render(RenderData& data);
                static bool ButtoClickCallback(GLFWwindow* window, int button, int action, int mods);
                static bool ButtonMoveCallback(GLFWwindow* window, double xpos, double ypos);
                static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
                static ImVec4 ColorToImVec4(const Color& color);
            private:
                void Draw(RenderData& data);
                void SetStyle();
                /// <summary>
                /// OpenGL归一化坐标转屏幕坐标
                /// </summary>
                /// <param name="point"></param>
                /// <param name="x"></param>
                /// <param name="y"></param>
                /// <param name="width"></param>
                /// <param name="height"></param>
                Point2D NDCToScreen(const Point2D& point, double x, double y, double width, double height);
                Scene* pscene;
            };
        }
    }
}