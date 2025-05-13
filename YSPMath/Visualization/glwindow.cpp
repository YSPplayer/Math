/*
    Created by YSP on 2025-05-13.
*/
#include "glwindow.h"
#include <glad/glad.h>
#include <memory>
namespace ysp {
    namespace gl {
        namespace visualization {
            GlWindow::GlWindow(int width, int height, const std::string& name):width(width), height(height),
                name(name){
                SetUi();
                initSuccess = GLInit();
            }


            void GlWindow::Show() {
                std::unique_ptr<GlWindow> window = std::make_unique<GlWindow>();
                if (window->IsInitSuccess()) {
                    
                }
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
                glfwSwapInterval(1);
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    glfwTerminate();
                    return false;//����opengl�ĺ���ָ��
                }
                return true;
            }



        }
    }
}