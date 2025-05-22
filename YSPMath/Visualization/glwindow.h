/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <string>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Geometry/scene.h"
#include "UI/ui.h"
using namespace ysp::gl::geometry;
using namespace ysp::gl::ui;
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
                static bool Show(void** args);

                /// <summary>
                /// ѭ�����ƴ���
                /// </summary>
                /// <returns></returns>
                bool Exe();

                /// <summary>
                /// �رմ���
                /// </summary>
                /// <returns></returns>
                void Close();
            private:
                /// <summary>
                /// ��Ⱦ����
                /// </summary>
                void Render();

                /// <summary>
                /// ���¼��ص�
                /// </summary>
                void BindCallback();

                /// <summary>
                /// �������ӻ�����
                /// </summary>
                /// <param name="args"></param>
                bool BuildShow(void** args);
                void SetUi();
                bool GLInit();
                GLFWwindow* window;//������
                std::string name;
                int width;
                int height;
                bool initSuccess;
                Scene scene;//��ǰGL����
                Ui ui;//UI����
            };
        }
    }
}
