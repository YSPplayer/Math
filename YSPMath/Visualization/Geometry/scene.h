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
                /// ��ʼ������
                /// </summary>
                /// <returns></returns>
                bool GL_FUNC InitScene();

                /// <summary>
                /// ��Ⱦģ��
                /// </summary>
                void GL_FUNC Render(RenderData& rdata);

                /// <summary>
                /// ����ģ�͵Ķ�����Ⱦ����
                /// </summary>
                void SetModelArgs(const std::string& name,void** args);

                /// <summary>
                /// ��ȡ����ǰ�����е�ģ��
                /// </summary>
                /// <returns></returns>
                Model* GetCurrentModel(const std::string& name);

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
                void GL_FUNC ClearScene();

                /// <summary>
                /// ��ά����ת��ά��Ļ����
                /// </summary>
                /// <param name="pos"></param>
                /// <returns></returns>
                glm::vec2 GetGLNDC(const glm::vec2& pos,int width,int height) const;

                /// <summary>
                /// ���ñ���
                /// </summary>
                void ResetAttribute(RenderData& rdata);
            private:
                std::vector<Model*> models;
                Camera camera;
            };
        }
    }
}