/*
	Created by YSP on 2025-06-12.
*/
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "model.h"
namespace ysp {
	namespace gl {
		namespace geometry {
			Camera::Camera() {
				cameraAttribute.position = glm::vec3(0.0f, 0.0f, 3.0f);
				cameraAttribute.front = glm::vec3(0.0f, 0.0f, -1.0f);
				cameraAttribute.worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
				cameraAttribute.right = glm::normalize(glm::cross(cameraAttribute.front, cameraAttribute.worldUp));
				cameraAttribute.up = glm::normalize(glm::cross(cameraAttribute.right, cameraAttribute.front));
				cameraAttribute.view = glm::lookAt(cameraAttribute.position, cameraAttribute.position + cameraAttribute.front, cameraAttribute.up);
				cameraAttribute.projection = glm::mat4(1.0f);
				par_fov = cameraAttribute.projection;
				per_fov = cameraAttribute.projection;
			}
			Camera::~Camera() {}
			/// <summary>
			/// ���������λ��
			/// </summary>
			/// <returns></returns>
			void Camera::ReSetPoisition(Model* model) {
				//ƽ���ӿ�
				float cameraDistance = 3.0f * model->GetModelSize();
				const glm::vec3& centerPosition = model->GetCenterPosition();
				
				// ����ƽ���ӿ�������� (index 0)
				cameraAttributes[0].position = glm::vec3(
					centerPosition.x,  // ���xλ�ö���ģ������
					centerPosition.y,  // ���yλ�ö���ģ������
					centerPosition.z + cameraDistance  // �����ģ���Ϸ�
				);
				// ���ʼ�ճ��¿�
				cameraAttributes[0].front = glm::vec3(0.0f, 0.0f, -1.0f);
				cameraAttributes[0].worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
				cameraAttributes[0].right = glm::normalize(glm::cross(cameraAttributes[0].front, cameraAttributes[0].worldUp));
				cameraAttributes[0].up = glm::normalize(glm::cross(cameraAttributes[0].right, cameraAttributes[0].front));
				// �ӵ��׼ģ������
				cameraAttributes[0].view = glm::lookAt(
					cameraAttributes[0].position,
					glm::vec3(centerPosition),  // ����ģ������
					cameraAttributes[0].up
				);

				// ����͸���ӿ�������� (index 1)
				cameraAttributes[1].position = glm::vec3(0.0f, 0.0f, 3.0f * model->GetModelSize());
				cameraAttributes[1].up = glm::vec3(0.0f, 1.0f, 0.0f);
				// ���λ�õ�ģ�����ĵ�����
				glm::vec3 direction = centerPosition - cameraAttributes[1].position;
				cameraAttributes[1].front = glm::normalize(direction);
				cameraAttributes[1].right = glm::normalize(glm::cross(cameraAttributes[1].front, cameraAttributes[1].up));
				cameraAttributes[1].up = glm::normalize(glm::cross(cameraAttributes[1].right, cameraAttributes[1].front));
				cameraAttributes[1].view = glm::lookAt(cameraAttributes[1].position, cameraAttributes[1].position + cameraAttributes[1].front, cameraAttributes[1].up);
			}

			/// <summary>
			/// ����Ⱦ�и���ֵ
			/// </summary>
			void Camera::Render(RenderData& data) {
				//ƽ���ӿ�
				par_fov = glm::ortho(
					-data.parallel, data.parallel, -data.parallel * static_cast<float>(data.height) / static_cast<float>(data.width), data.parallel * static_cast<float>(data.height) / static_cast<float>(data.width), 0.01f, 10.0f);
				//͸���ӿ�
				per_fov = glm::perspective(data.fov, static_cast<float>(data.width) / static_cast<float>(data.height), 0.1f,
					3000.0f);
				cameraAttribute.projection = data.isParallelFov ? par_fov : per_fov;
				int index = data.isParallelFov ? 0 : 1;
				cameraAttribute.position = cameraAttributes[index].position;
				cameraAttribute.front = cameraAttributes[index].front;
				cameraAttribute.worldUp = cameraAttributes[index].worldUp;
				cameraAttribute.right = cameraAttributes[index].right;
				cameraAttribute.up = cameraAttributes[index].up;
				cameraAttribute.view = cameraAttributes[index].view;
			}
		}
	}
}