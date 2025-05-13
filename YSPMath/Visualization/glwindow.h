/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <string>
#include <GLFW/glfw3.h>
namespace ysp {
    namespace gl {
        namespace visualization {
            class GlWindow {
            public:
                GlWindow(int width, int height, const std::string& name);

                /// <summary>
                /// 检查当前窗口是否初始化成功
                /// </summary>
                /// <returns></returns>
                inline bool IsInitSuccess() {
                    return initSuccess;
                }


                /// <summary>
                /// 可视化当前视口
                /// </summary>
                static void Show();
            private:
                void SetUi();
                bool GLInit();
                GLFWwindow* window;//主窗口
                std::string name;
                int width;
                int height;
                bool initSuccess;
            };
        }
    }
}
