/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include "model.h"
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
                bool InitScene();

                /// <summary>
                /// 渲染模型
                /// </summary>
                void Render();

                /// <summary>
                /// 检查当前场景是否为空
                /// </summary>
                inline bool IsEmpty() {
                    return !model || model->IsEmpty();
                }

                /// <summary>
                /// 设置当前场景中的模型
                /// </summary>
                /// <param name="model"></param>
                /// <returns></returns>
                bool SetCurrentModel(Model* model);

                /// <summary>
                /// 清理场景
                /// </summary>
                void ClearScene();
            private:
                Model* model;
            };
        }
    }
}