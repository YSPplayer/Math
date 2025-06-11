/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include "model.h"
#include <util.h>
#include "camera.h"
namespace ysp {
    namespace gl {
        namespace geometry {
            class Scene {
            public:
                Scene();

                /// <summary>
                /// 初始化场景
                /// </summary>
                /// <returns></returns>
                bool GL_FUNC InitScene();

                /// <summary>
                /// 渲染模型
                /// </summary>
                void GL_FUNC Render(RenderData& rdata);

                /// <summary>
                /// 设置模型的额外渲染参数
                /// </summary>
                void SetModelArgs(const std::string& name,void** args);

                /// <summary>
                /// 获取到当前场景中的模型
                /// </summary>
                /// <returns></returns>
                Model* GetCurrentModel(const std::string& name);

                /// <summary>
                /// 检查当前场景是否为空
                /// </summary>
                inline bool IsEmpty() {
                    return ListFilter::Count<Model*>(models, [](Model* model)->bool {
                        return model && !model->IsEmpty();
                        }) <= 0;
                }

                /// <summary>
                /// 设置当前场景中的模型
                /// </summary>
                /// <param name="model"></param>
                /// <returns></returns>
                bool AddModel(Model* model);

                /// <summary>
                /// 清理场景
                /// </summary>
                void GL_FUNC ClearScene();
            private:
                std::vector<Model*> models;
                Camera camera;
            };
        }
    }
}