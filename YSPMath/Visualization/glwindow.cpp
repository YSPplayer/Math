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
                glfwSwapInterval(1);
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    glfwTerminate();
                    return false;//加载opengl的函数指针
                }
                return true;
            }



        }
    }
}