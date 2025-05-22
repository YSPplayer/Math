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
                /// ��ʼ������
                /// </summary>
                /// <returns></returns>
                bool InitScene();

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

                /// <summary>
                /// ���õ�ǰ�����е�ģ��
                /// </summary>
                /// <param name="model"></param>
                /// <returns></returns>
                bool SetCurrentModel(Model* model);

                /// <summary>
                /// ������
                /// </summary>
                void ClearScene();
            private:
                Model* model;
            };
        }
    }
}