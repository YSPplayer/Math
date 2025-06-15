/*
	Created by YSP on 2025-06-12.
*/
#pragma once
#include "data.h"
namespace ysp {
	namespace gl {
		namespace geometry {
			class Model;
			class Camera {
			public:
				Camera();
				~Camera();
				void ReSetPoisition(Model* model);
				void Render(RenderData& data);
				CameraAttribute cameraAttribute;//相机属性
				glm::vec2 GetNDC(const glm::vec3& pos) const;
			private:
				CameraAttribute cameraAttributes[2];//相机备份属性 0是平行视口 1是透视视口
				glm::mat4 par_fov;//平行视口
				glm::mat4 per_fov;//透视视口
				inline glm::mat4 GetProjection(bool isParallelFov) {
					return isParallelFov ? par_fov : per_fov;
				};
			};
		}
	}
}