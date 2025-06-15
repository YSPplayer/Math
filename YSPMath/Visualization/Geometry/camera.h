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
				CameraAttribute cameraAttribute;//�������
				glm::vec2 GetNDC(const glm::vec3& pos) const;
			private:
				CameraAttribute cameraAttributes[2];//����������� 0��ƽ���ӿ� 1��͸���ӿ�
				glm::mat4 par_fov;//ƽ���ӿ�
				glm::mat4 per_fov;//͸���ӿ�
				inline glm::mat4 GetProjection(bool isParallelFov) {
					return isParallelFov ? par_fov : per_fov;
				};
			};
		}
	}
}