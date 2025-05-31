/*
    Created by YSP on 2025-05-23.
*/
#include "ui.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <util.h>
#include <fmt/core.h>
#include "../../Math/Geometry/line.h"
#include "../../Math/Geometry/triangle.h"
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace ui {
            Ui::Ui() {
            }

            void Ui::Init(GLFWwindow* window, Scene* pscene){
                this->pscene = pscene;
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                //设置配置文件保存路径  Util::WStringToChar((Util::GetRootPath() + L"imgui.ini"))
                io.IniFilename = nullptr;
                ImFontConfig fontCfg;//支持中文显示，获取字体路径
                io.Fonts->AddFontFromFileTTF(Util::WStringToString((Util::GetRootPath() + L"Font/Alibaba-PuHuiTi-Regular.ttf")).c_str(), 21.0f, &fontCfg, io.Fonts->GetGlyphRangesChineseFull());
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init("#version 330 core");
            }

            /// <summary>
            /// 渲染UI
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
                //设置菜单容器
                {
                    ImGui::SetNextWindowPos(ImVec2(float(0), float(0)));
                    ImGui::SetNextWindowSize(ImVec2(float(static_cast<float>(data.width) / 5.0f), float(data.height)));
                    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
                    ImGui::Begin(u8"菜单", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
                    ImVec2 actualSize = ImGui::GetWindowSize();
                    float windowWidth = actualSize.x;  // 实际宽度
                    float windowHeight = actualSize.y; // 实际高度
                    static bool wasCollapsed = false;
                    bool isCollapsed = ImGui::IsWindowCollapsed();
                    if (wasCollapsed != isCollapsed) { //如果菜单栏未折叠动态更新gl视口
                        if (isCollapsed) {
                            data.x = 0.0;
                            data.y = 0.0;
                        }
                        else {
                            data.x = windowWidth;
                            data.y = 0.0;
                        }
                        wasCollapsed = isCollapsed;
                    }
                    if (data.args) {
                        //组件类型
                        if (data.type == GL_SHOW_TYPE_LINE2D) {//绘制二维线段相关组件
                            Line2D* line2d = static_cast<Line2D*>(data.args[0]);
                            {
                                if (ImGui::TreeNode(u8"几何属性")) {
                                    //text的宽度由文本决定
                                    ImGui::Text(u8"几何名称：线段");
                                    ////
                                    ImGui::Text(u8"起始点: ");
                                    ImGui::SameLine(); //让下一个组件在一行
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("[x:{:.2f},y:{:.2f}]", line2d->StartPoint().X(), line2d->StartPoint().Y()).c_str());
                                    ////

                                     ////
                                    ImGui::Text(u8"终点: ");
                                    ImGui::SameLine();
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("[x:{:.2f},y:{:.2f}]", line2d->EndPoint().X(), line2d->EndPoint().Y()).c_str());
                                    ////
                                    

                                     ////
                                    ImGui::Text(u8"长度: ");
                                    ImGui::SameLine();
                                    ImGui::TextColored(ColorToImVec4(Style::DefaultColor), fmt::format("{:.2f}", line2d->Length()).c_str());
                                    ////

                                    ImGui::TreePop();

                                }
                 
                            }

                        }
                    }
                    ImGui::End();
                }
                if (data.args) {
                    //绘制坐标轴
                    Point2D min2d;
                    Point2D max2d;
                    if (data.type == GL_SHOW_TYPE_LINE2D) {
                        Line2D* geometry = static_cast<Line2D*>(data.args[0]);
                        geometry->GetPointMinMax(min2d, max2d);
                    }
                    else if (data.type == GL_SHOW_TYPE_TRIANGLE2D) {
                        Triangle2D* geometry = static_cast<Triangle2D*>(data.args[0]);
                        geometry->GetPointMinMax(min2d, max2d);
                    }
                    Point2D::SetMinMaxNextPowerOfTen2D(min2d, max2d);
                    float nmin = N_MIN;
                    float namx = N_MAX;
                    VBOData* vbodata = pscene->GetCurrentModel("Line2DAxis")->GetVBOS(0);
                    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // 完全透明背景
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));     // 纯绿色文本
                    for (int i = 0; i < vbodata->includes["AxisX"].size(); ++i) {
                        int index = vbodata->includes["AxisX"][i];
                        Point2D currentPoint(vbodata->data[index], vbodata->data[index + 1]);
                        Point2D position = NDCToScreen(currentPoint,
                            data.x, data.y, data.width, data.height);
                        {

                            double xvalue = Point2D::Denormalize(currentPoint, min2d, max2d, nmin, namx).X();
                            std::string strvalue = fmt::format("{:.1f}", xvalue);
                            float textWidth = ImGui::CalcTextSize(strvalue.c_str()).x;
                            ImGui::SetNextWindowPos(ImVec2(
                                position.X() - textWidth * 0.5f,  // 水平居中
                                position.Y() + 5.0f               // 垂直偏移
                            ));
                            ImGui::Begin(fmt::format("LabelWindow_X{}", i).c_str(), nullptr,
                                ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoScrollbar |
                                ImGuiWindowFlags_NoBackground);

                            ImGui::Text(strvalue.c_str());  // 显示文本内容
                            ImGui::End();
                        }
                    }

                    for (int i = 0; i < vbodata->includes["AxisY"].size(); ++i) {
                        int index = vbodata->includes["AxisY"][i];
                        Point2D currentPoint(vbodata->data[index], vbodata->data[index + 1]);
                        Point2D position = NDCToScreen(currentPoint,
                            data.x, data.y, data.width, data.height);
                        {

                            double yvalue = Point2D::Denormalize(currentPoint, min2d, max2d, nmin, namx).Y();
                            if (yvalue == 0.0f) continue;//跳过0轴，X轴已经标注
                            std::string strvalue = fmt::format("{:.1f}", yvalue);
                            float textHeight = ImGui::CalcTextSize(strvalue.c_str()).y;
                            ImGui::SetNextWindowPos(ImVec2(
                                position.X() + 6.0f,  // 水平居中
                                position.Y() - textHeight * 0.5f  // 垂直偏移
                            ));
                            ImGui::Begin(fmt::format("LabelWindow_Y{}", i).c_str(), nullptr,
                                ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoScrollbar |
                                ImGuiWindowFlags_NoBackground);

                            ImGui::Text(strvalue.c_str());  // 显示文本内容
                            ImGui::End();
                        }
                    }
                    ImGui::PopStyleColor(2);  // 恢复样式
                       
                }
            }

            /// <summary>
            /// 设置整体的框架样式
            /// </summary>
            void Ui::SetStyle() {
                //设置组件颜色
                ImGuiStyle& style = ImGui::GetStyle();
                style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
                //取消边框样式 
                style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // 设置边框颜色为透明
                style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // 设置阴影颜色为透明
                style.FrameBorderSize = 0.0f; // 设置边框宽度为0
                //data.transparentBg ? 0.0f : 
                float transparent = 0.94f;
                //设置背景是否透明
                style.Colors[ImGuiCol_WindowBg].w = transparent;
                style.Colors[ImGuiCol_PopupBg].w = transparent;
            }

            Point2D Ui::NDCToScreen(const Point2D& point, double x, double y, double width, double height) {
                // 考虑菜单栏的偏移
                float screenX = ((point.X() + 1.0f) * 0.5f) * (width - x) + x;
                float screenY = ((1.0f - point.Y()) * 0.5f) * height + y;
                return Point2D(screenX, screenY);
            }
        }
    }
}