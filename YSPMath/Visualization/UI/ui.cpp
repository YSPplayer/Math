/*
    Created by YSP on 2025-05-23.
*/
#include "ui.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "../../util.h"
#include "../Geometry/data.h"
namespace ysp {
    namespace gl {
        namespace ui {
            Ui::Ui() {
                type = 0;
            }

            void Ui::Init(GLFWwindow* window) {
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                //���������ļ�����·��  Util::WStringToChar((Util::GetRootPath() + L"imgui.ini"))
                io.IniFilename = nullptr;
                ImFontConfig fontCfg;//֧��������ʾ����ȡ����·��
                io.Fonts->AddFontFromFileTTF(Util::WStringToString((Util::GetRootPath() + L"Font/Alibaba-PuHuiTi-Regular.ttf")).c_str(), 14.0f, &fontCfg, io.Fonts->GetGlyphRangesChineseFull());
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init("#version 330 core");
            }

            /// <summary>
            /// ��ȾUI
            /// </summary>
            void Ui::Render() {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
   /*             Draw(data);*/
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            bool Ui::ButtoClickCallback(GLFWwindow* window, int button, int action, int mods) {
                ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
                return ImGui::GetIO().WantCaptureMouse;
            }

            bool Ui::ButtonMoveCallback(GLFWwindow* window, double xpos, double ypos) {
                ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
                return ImGui::GetIO().WantCaptureMouse;
            }
            void Ui::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
                ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
            }

            void Ui::Draw() {
                SetStyle();
                if (type == GL_SHOW_TYPE_LINE2D) {//���ƶ�ά�߶�������

                }
            }

            /// <summary>
            /// ��������Ŀ����ʽ
            /// </summary>
            void Ui::SetStyle() {
                //���������ɫ
                ImGuiStyle& style = ImGui::GetStyle();
                style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
                //ȡ���߿���ʽ 
                style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // ���ñ߿���ɫΪ͸��
                style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // ������Ӱ��ɫΪ͸��
                style.FrameBorderSize = 0.0f; // ���ñ߿���Ϊ0
                //data.transparentBg ? 0.0f : 
                float transparent = 0.94f;
                //���ñ����Ƿ�͸��
                style.Colors[ImGuiCol_WindowBg].w = transparent;
                style.Colors[ImGuiCol_PopupBg].w = transparent;
            }
        }
    }
}