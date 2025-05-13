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
                /// ��鵱ǰ�����Ƿ��ʼ���ɹ�
                /// </summary>
                /// <returns></returns>
                inline bool IsInitSuccess() {
                    return initSuccess;
                }


                /// <summary>
                /// ���ӻ���ǰ�ӿ�
                /// </summary>
                static void Show();
            private:
                void SetUi();
                bool GLInit();
                GLFWwindow* window;//������
                std::string name;
                int width;
                int height;
                bool initSuccess;
            };
        }
    }
}
