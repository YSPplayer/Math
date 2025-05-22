/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include "model.h"
#include "../../util.h"
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
                    return ListFilter::Count<Model*>(models, [](Model* model)->bool {
                        return model && !model->IsEmpty();
                        }) <= 0;
                }

                /// <summary>
                /// ���õ�ǰ�����е�ģ��
                /// </summary>
                /// <param name="model"></param>
                /// <returns></returns>
                bool AddModel(Model* model);

                /// <summary>
                /// ������
                /// </summary>
                void ClearScene();
            private:
                std::vector<Model*> models;
            };
        }
    }
}