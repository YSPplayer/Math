/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <string>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Geometry/scene.h"
#include "UI/ui.h"
#include "Geometry/data.h"
#include <object.h>
using namespace ysp::gl::geometry;
using namespace ysp::gl::ui;
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
                static bool Show(void** args);

                /// <summary>
                /// 循环绘制窗体
                /// </summary>
                /// <returns></returns>
                bool Exe();

                /// <summary>
                /// 关闭窗口
                /// </summary>
                /// <returns></returns>
                void Close();
            private:

                /// <summary>
                /// 渲染数据的更新
                /// </summary>
                void UpdateRenderData();

                /// <summary>
                /// 渲染窗口
                /// </summary>
                void Render();
                
                /// <summary>
                /// 渲染后数据销毁
                /// </summary>
                void EndRenderData();

                /// <summary>
                /// 绑定事件回调
                /// </summary>
                void BindCallback();

                /// <summary>
                /// 构建可视化对象
                /// </summary>
                /// <param name="args"></param>
                bool BuildShow(void** args);
                
                void SetUi();
                bool GLInit();
                GLFWwindow* window;//主窗口
                Object* obj;//当前绘制的几何图形
                std::string name;
                int showtype;//展示类型
                int width;
                int height;
                bool initSuccess;
                Scene scene;//当前GL场景
                static RenderData rdata;
                Ui ui;//UI对象
            };
        }
    }
}
