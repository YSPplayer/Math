/*
    Created by YSP on 2025-05-14.
*/
#include "scene.h"
namespace ysp {
    namespace gl {
        namespace geometry {
            Scene::Scene() {
                model = nullptr;
            }

            void Scene::Render() {
                if (IsEmpty()) return;
                model->Render();
            }
        }
    }
}