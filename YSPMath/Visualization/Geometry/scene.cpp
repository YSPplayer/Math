/*
    Created by YSP on 2025-05-14.
*/
#include "scene.h"
#include <util.h>
namespace ysp {
    namespace gl {
        namespace geometry {
            Scene::Scene() {
            }

            bool Scene::InitScene() {
                glEnable(GL_DEPTH_TEST); //启用深度测试
                glEnable(GL_MULTISAMPLE);//启用多重采样，线段抗锯齿
                return true;
            }

            void Scene::Render() {
                glClearColor(0, 0, 0, 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_CULL_FACE);
                if (IsEmpty()) return;
                for (int i = 0; i < models.size(); ++i) {
                    models[i]->Render();
                }
               
            }

            bool Scene::AddModel(Model* model) {
                if (!model || model->IsEmpty()) return false;
                models.push_back(model);
                return true;
            }

            void Scene::ClearScene() {
                for (int i = 0; i < models.size(); ++i)
                    Util::ReleasePointer(models[i]);
            }
        }
    }
}