/*
    Created by YSP on 2025-05-13.
*/
#include "glwindow.h"
#include <glad/glad.h>
#include <memory>
#include "Geometry/data.h"
#include "Shader/strshader.h"
#include "../Math/Geometry/line.h"
#include <util.h>
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace visualization {
            GlWindow::GlWindow(int width, int height, const std::string& name):width(width), height(height),
                name(name){
                SetUi();
                initSuccess = GLInit();
                if (initSuccess) {
                    BindCallback();//绑定回调
                    scene.InitScene();
                } 
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
                    glfwPollEvents(); //接收事件，用于事件的触发
                    Render();
                    glfwSwapBuffers(window);//双缓冲机制来渲染图形，前缓冲用于显示图像，后缓冲用于图像绘制，防止图像闪烁显示
                }
                Close();
                glfwTerminate();
                return true;
            }

            void GlWindow::Close() {
                scene.ClearScene();
            }

            void GlWindow::Render() {
                scene.Render();
            }

            void GlWindow::BindCallback() {
                glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                    glViewport(0, 0, width, height);
                });
            }

            bool GlWindow::BuildShow(void** args) {
                int type = *static_cast<int*>(args[0]);
                bool success = false;
                if (type == GL_SHOW_TYPE_LINE2D) {
                    Line2D* line2D = static_cast<Line2D*>(args[1]);
                    VBOData vboData;
                    vboData.attributeIndex = 2;
                    vboData.type = GL_EBO_TYPE_VECTOR;
                    // 找出坐标的最小值和最大值
                    double min_x = std::numeric_limits<double>::max();
                    double min_y = std::numeric_limits<double>::max();
                    double max_x = std::numeric_limits<double>::lowest();
                    double max_y = std::numeric_limits<double>::lowest();
                    std::vector<Point2D> points;
                    points.push_back(line2D->StartPoint());
                    points.push_back(line2D->EndPoint());
                    for (const auto& point : points) {
                        min_x = std::min(min_x, point.X());
                        min_y = std::min(min_y, point.Y());
                        max_x = std::max(max_x, point.X());
                        max_y = std::max(max_y, point.Y());
                    }
                    min_x = std::abs(Util::NextPowerOfTen(min_x));
                    min_y = std::abs(Util::NextPowerOfTen(min_y));
                    max_x = std::abs(Util::NextPowerOfTen(max_x));
                    max_y = std::abs(Util::NextPowerOfTen(max_y));
                    double max = std::max({ min_x,min_y,max_x,max_y });
                    double min = -max;
                    Point2D nstart = line2D->StartPoint();
                    Point2D nend = line2D->EndPoint();
                    Point2D max2d = {max,max};
                    Point2D min2d = { min,min };
                    nstart = Point2D::Normalize(nstart, min2d, max2d);
                    nend = Point2D::Normalize(nend, min2d, max2d);
                    vboData.data.push_back(nstart.X());
                    vboData.data.push_back(nstart.Y());
                    vboData.data.push_back(nend.X());
                    vboData.data.push_back(nend.Y());
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetVBOS({ vboData });
                    model->Build(type);
                    success  = scene.SetCurrentModel(model);
                    Util::ReleasePointer<Line2D>(args[1]);
                    Util::ReleasePointer(args, 2);
                }
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
                return true;
            }



        }
    }
}