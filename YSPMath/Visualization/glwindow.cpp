/*
    Created by YSP on 2025-05-13.
*/
#include "glwindow.h"
#include <glad/glad.h>
#include <memory>
#include "../Math/Geometry/line.h"
#include <util.h>
#include "processbuild.h"
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace visualization {
            GlWindow::GlWindow(int width, int height, const std::string& name):width(width), height(height),
                name(name){
                obj = nullptr;
                showtype = -1;
                SetUi();
                initSuccess = GLInit();
            }


            bool GlWindow::Show(void** args) {
                std::unique_ptr<GlWindow> window = std::make_unique<GlWindow>(800,600,"ShowGeometry");
                if (window->IsInitSuccess() && window->BuildShow(args)) {
                    return window->Exe();
                }
                return false;
            }

            bool GlWindow::Exe() {
                glfwMakeContextCurrent(window);
                while (!glfwWindowShouldClose(window)) {
                    Render();
                }
                Close();
                glfwTerminate();
                return true;
            }

            void GlWindow::Close() {
                scene.ClearScene();
            }

            void GlWindow::UpdateRenderData() {
                glfwGetWindowSize(window, &rdata.width, &rdata.height);
                glViewport(rdata.x, rdata.y, rdata.width - rdata.x,rdata.height - rdata.y);
                rdata.type = showtype;
                if (obj) {
                    Object* geometry = nullptr;
                    if (showtype & GL_SHOW_TYPE_2D) { //坐标系
                        geometry = (Line2D*)obj;
                        //额外参数设置
                        scene.SetModelArgs("Line2DAxis", Util::Packing(new Color(Style::DefaultColor)));
                    }
                    rdata.args = Util::Packing(geometry);
                }
                else {
                    rdata.args = nullptr;
                }

            }

            void GlWindow::Render() {
                glfwPollEvents(); //接收事件，用于事件的触发
                UpdateRenderData();//更新data数据
                scene.Render(rdata);
                ui.Render(rdata);
                glfwSwapBuffers(window);//双缓冲机制来渲染图形，前缓冲用于显示图像，后缓冲用于图像绘制，防止图像闪烁显示
                EndRenderData();
            }


            void GlWindow::EndRenderData() {
                if (showtype == GL_SHOW_TYPE_LINE2D) {
                    //Line2D不需要释放
                    Util::ReleasePointer(rdata.args, true);
                }
            }

            void GlWindow::BindCallback() {
               /* glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                    glViewport(0, 0, width, height);
                });*/
            }

            bool GlWindow::BuildShow(void** args) {
                int type = *static_cast<int*>(args[0]);
                bool success = false;
                if (type == GL_SHOW_TYPE_LINE2D) {
                    Line2D* geometry = static_cast<Line2D*>(args[1]);
                    Point2D min;
                    Point2D max;
                    success = scene.AddModel(ProcBuild::BuildModelLine2D(geometry)) &&
                        scene.AddModel(ProcBuild::BuildModel2DAxis(geometry));
                    if (success) {
                        obj = geometry;
                        Util::ReleasePointer(args, true);
                    }
                    else {
                        Util::ReleasePointer<Line2D>(args[1]);
                        Util::ReleasePointer(args, 2);
                    }
                }
                else if (type == GL_SHOW_TYPE_TRIANGLE2D) {
                    Triangle2D* geometry = static_cast<Triangle2D*>(args[1]);
                    success = scene.AddModel(ProcBuild::BuildModelTriangle2D(geometry)) &&
                        scene.AddModel(ProcBuild::BuildModel2DAxis(geometry));
                    if (success) {
                        obj = geometry;
                        Util::ReleasePointer(args, true);
                    }
                    else {
                        Util::ReleasePointer<Triangle2D>(args[1]);
                        Util::ReleasePointer(args, 2);
                    }
                }
                showtype = success ? type : - 1;
                return success;
            }

            void GlWindow::SetUi() {
            }


            bool GlWindow::GLInit() {
                glfwInit(); //初始化glfw库
                //设置opengl的版本号为3.3
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                //指定使用Opengl的核心配置文件，不使用旧的功能
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
                if (window == nullptr) {
                    glfwTerminate(); //释放glfw相关的内存
                    return false;
                }
                glfwMakeContextCurrent(window); //设置glfw窗口当前的上下文 
                glfwSwapInterval(1);//启用垂直同步，避免cpu过载
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    glfwTerminate();
                    return false;//加载opengl的函数指针
                }
                //初始化Ui
                ui.Init(window,&scene);
                BindCallback();//绑定回调
                scene.InitScene();//初始化场景
                return true;
            }



        }
    }
}