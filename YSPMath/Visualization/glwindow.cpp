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
                    BindCallback();//�󶨻ص�
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
                    glfwPollEvents(); //�����¼��������¼��Ĵ���
                    Render();
                    glfwSwapBuffers(window);//˫�����������Ⱦͼ�Σ�ǰ����������ʾͼ�񣬺󻺳�����ͼ����ƣ���ֹͼ����˸��ʾ
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
                    // �ҳ��������Сֵ�����ֵ
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
                glfwInit(); //��ʼ��glfw��
                //����opengl�İ汾��Ϊ3.3
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                //ָ��ʹ��Opengl�ĺ��������ļ�����ʹ�þɵĹ���
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
                if (window == nullptr) {
                    glfwTerminate(); //�ͷ�glfw��ص��ڴ�
                    return false;
                }
                glfwMakeContextCurrent(window); //����glfw���ڵ�ǰ�������� 
                glfwSwapInterval(1);//���ô�ֱͬ��������cpu����
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    glfwTerminate();
                    return false;//����opengl�ĺ���ָ��
                }
                return true;
            }



        }
    }
}