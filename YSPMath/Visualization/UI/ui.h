/*
    Created by YSP on 2025-05-23.
*/
#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "../Geometry/data.h"
#include <imgui/imgui.h>
#include "style.h"
namespace ysp {
    namespace gl {
        namespace ui {
            class Ui {
            public:
                Ui();
                void Init(GLFWwindow* window);
                void Render(RenderData& data);
                static bool ButtoClickCallback(GLFWwindow* window, int button, int action, int mods);
                static bool ButtonMoveCallback(GLFWwindow* window, double xpos, double ypos);
                static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
                static ImVec4 ColorToImVec4(const Color& color);
            private:
                void Draw(RenderData& data);
                void SetStyle();
            };
        }
    }
}