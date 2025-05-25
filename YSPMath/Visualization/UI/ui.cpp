/*
    Created by YSP on 2025-05-23.
*/
#include "ui.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <util.h>
#include <fmt/core.h>
#include "../../Math/Geometry/line.h"
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace ui {
            Ui::Ui() {
            }

            void Ui::Init(GLFWwindow* window) {
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                //���������ļ�����·��  Util::WStringToChar((Util::GetRootPath() + L"imgui.ini"))
                io.IniFilename = nullptr;
                ImFontConfig fontCfg;//֧��������ʾ����ȡ����·��
                io.Fonts->AddFontFromFileTTF(Util::WStringToString((Util::GetRootPath() + L"Font/Alibaba-PuHuiTi-Regular.ttf")).c_str(), 21.0f, &fontCfg, io.Fonts->GetGlyphRangesChineseFull());
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init("#version 330 core");
            }

            /// <summary>
            /// ��ȾUI
            /// </summary>
            void Ui::Render(RenderData& data) {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                Draw(data);
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

            ImVec4 Ui::ColorToImVec4(const Color& color) {
                return ImVec4(color.RF(), color.GF(), color.BF(), color.AF());
            }

            void Ui::Draw(RenderData& data) {
                SetStyle();
                //���ò˵�����
                {
                    ImGui::SetNextWindowPos(ImVec2(float(0), float(0)));
                    ImGui::SetNextWindowSize(ImVec2(float(static_cast<float>(data.width) / 5.0f), float(data.height)));
                    ImGui::Begin(u8"�˵�", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
                    ImVec2 actualSize = ImGui::GetWindowSize();
                    float windowWidth = actualSize.x;  // ʵ�ʿ��
                    float windowHeight = actualSize.y; // ʵ�ʸ߶�
                    if (data.args) {
                        //�������
                        if (data.type == GL_SHOW_TYPE_LINE2D) {//���ƶ�ά�߶�������
                            Line2D* line2d = static_cast<Line2D*>(data.args[0]);
                            {
                                if (ImGui::TreeNode(u8"��������")) {
                                    //text�Ŀ�����ı�����
                                    ImGui::Text(u8"�������ƣ��߶�");
                                    ////
                                    ImGui::Text(u8"��ʼ��: ");
                                    ImGui::SameLine(); //����һ�������һ��
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("[x:{:.2f},y:{:.2f}]", line2d->StartPoint().X(), line2d->StartPoint().Y()).c_str());
                                    ////

                                     ////
                                    ImGui::Text(u8"�յ�: ");
                                    ImGui::SameLine();
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("[x:{:.2f},y:{:.2f}]", line2d->EndPoint().X(), line2d->EndPoint().Y()).c_str());
                                    ////
                                    

                                     ////
                                    ImGui::Text(u8"����: ");
                                    ImGui::SameLine();
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("{:.2f}", line2d->Length()).c_str());
                                    ////

                                    ImGui::TreePop();

                                }
                 
                            }
                            Util::ReleasePointer<Line2D*>(data.args[0]);
                            Util::ReleasePointer(data.args, 1);
                        }
                    }
                    ImGui::End();
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