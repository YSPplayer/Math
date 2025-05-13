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
                /// ��Ⱦģ��
                /// </summary>
                void Render();

                /// <summary>
                /// ��鵱ǰ�����Ƿ�Ϊ��
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