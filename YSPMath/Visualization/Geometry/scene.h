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
                /// 渲染模型
                /// </summary>
                void Render();

                /// <summary>
                /// 检查当前场景是否为空
                /// </summary>
                inline bool IsEmpty() {
                    return !model || model->IsEmpty();
                }
            private:
                Model* model;
            };
        }
    }
}