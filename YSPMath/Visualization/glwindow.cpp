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
                    if (showtype == GL_SHOW_TYPE_LINE2D) {
                        geometry = new Line2D((Line2D*)obj);
                        //�����������
                        scene.SetModelArgs("Line2DAxis", Util::Packing(new Color(Style::DefaultColor)));
                    }
                    rdata.args = Util::Packing(geometry);
                }
                else {
                    rdata.args = nullptr;
                }

            }

            void GlWindow::Render() {
                glfwPollEvents(); //�����¼��������¼��Ĵ���
                UpdateRenderData();//����data����
                scene.Render(rdata);
                ui.Render(rdata);
                glfwSwapBuffers(window);//˫�����������Ⱦͼ�Σ�ǰ����������ʾͼ�񣬺󻺳�����ͼ����ƣ���ֹͼ����˸��ʾ
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
                    Line2D* line2D = static_cast<Line2D*>(args[1]);
                    success = scene.AddModel(ProcBuild::BuildModelLine2D(line2D)) &&
                        scene.AddModel(ProcBuild::BuildModelLine2DAxis(line2D));
                    if (success) {
                        obj = line2D;
                        Util::ReleasePointer(args, true);
                    }
                    else {
                        Util::ReleasePointer<Line2D>(args[1]);
                        Util::ReleasePointer(args, 2);
                    }
                }
                showtype = success ? type : - 1;
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
                //��ʼ��Ui
                ui.Init(window,&scene);
                BindCallback();//�󶨻ص�
                scene.InitScene();//��ʼ������
                return true;
            }



        }
    }
}