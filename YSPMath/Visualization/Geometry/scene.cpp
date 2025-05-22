/*
    Created by YSP on 2025-05-14.
*/
#include "scene.h"
#include <util.h>
namespace ysp {
    namespace gl {
        namespace geometry {
            Scene::Scene() {
                model = nullptr;
            }

            bool Scene::InitScene() {
                glEnable(GL_DEPTH_TEST); //������Ȳ���
                glEnable(GL_MULTISAMPLE);//���ö��ز������߶ο����
                return true;
            }

            void Scene::Render() {
                glClearColor(0, 0, 0, 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_CULL_FACE);
                if (IsEmpty()) return;
                model->Render();
            }

            bool Scene::SetCurrentModel(Model* model) {
                if (!model || model->IsEmpty()) return false;
                this->model = model;
                return true;
            }

            void Scene::ClearScene() {
                Util::ReleasePointer(model);
            }
        }
    }
}