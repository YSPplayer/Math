/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "../Shader/shader.h"
#include "../../Math/Geometry/degrees.h"
#include "../../Math/Geometry/point.h"
#include "../../Math/Geometry/line.h"
#include "data.h"
#include "camera.h"
using namespace ysp::gl;
using namespace ysp::math::geometry;
namespace ysp {
    namespace gl {
        namespace geometry {
            class Model {
            public:
                Model();
				GL_FUNC ~Model();
				
				/// <summary>
				/// ��鵱ǰģ���Ƿ�Ϊ��
				/// </summary>
				/// <returns></returns>
				inline bool IsEmpty() {
					return empty;
				}

				/// <summary>
				/// ���ö�����ɫ��
				/// </summary>
				inline void SetVShader(const std::string& vshader) {
					this->vshader = vshader;
				};

				/// <summary>
				/// ����Ƭ����ɫ��
				/// </summary>
				inline void SetFShader(const std::string& fshader) {
					this->fshader = fshader;
				}

				/// <summary>
				/// ����VBO
				/// </summary>
				inline void SetVBOS(const std::vector<VBOData>& vbodatas) {
					this->vbodatas = vbodatas;
				};
				
				/// <summary>
				/// ��ȡ��ָ����VBO����
				/// </summary>
				/// <returns></returns>
				inline VBOData* GetVBOS(int index) {
					return &vbodatas[index];
				}
				
				/// <summary>
				/// ����ģ��
				/// </summary>
				bool GL_FUNC Build(int type);

				/// <summary>
				/// ����ģ�͵�����
				/// </summary>
				/// <param name="name"></param>
				inline void SetName(const std::string& name) {
					this->name = name;
				}

				/// <summary>
				/// ��ȡ��ģ�͵�����
				/// </summary>
				/// <returns></returns>
				inline std::string GetName() const {
					return name;
				}

				/// <summary>
				/// ������Ⱦ����
				/// </summary>
				inline void SetRenderArgs(void** args) {
					this->args = args;
				}

				/// <summary>
				/// ��ȡ��ģ�Ͱ�Χ�д�С
				/// </summary>
				/// <returns></returns>
				inline float GetModelSize() const {
					return modelSize;
				}

				/// <summary>
				/// ��תģ��
				/// </summary>
				void Rotate(const Point2D& center,const Angle& angle);

				/// <summary>
				/// ��Ⱦģ��
				/// </summary>
				virtual void GL_FUNC Render(RenderData& rdata,Camera& camera);

				/// <summary>
				/// ��ȡ��ģ�͵���������
				/// </summary>
				/// <returns></returns>
				inline glm::vec3 GetCenterPosition() const {
					return centerPosition;
				}
				void** args;//��Ⱦ����
            private:
				int type;
				int vsize;//��������Ԫ�ظ���
				bool empty;
				std::string name;//ģ������
				std::string vshader;
				std::string fshader;
				float modelSize;//ģ�Ͱ�Χ�д�С
				glm::vec3 centerPosition;//ģ�͵����������
                Shader shader;
                GLuint vao;
				std::vector<VBOData> vbodatas;
				template<typename T>
				static bool GL_FUNC BindBufferObject(GLuint& oID, GLenum bufferType, const T* data, GLsizei dataSize, GLint attributeIndex, GLint componentsPerVertex, GLenum usage = GL_STATIC_DRAW) {
					//���ɲ���VBO
					bool empty = oID == NULL;
					if (empty) glGenBuffers(1, &oID);
					//���õ�ǰVBO������
					glBindBuffer(bufferType, oID);
					//�Ȱ󶨿�ָ�룬ֱ�Ӱ󶨴����Դ����������
					if (empty) glBufferData(bufferType, dataSize * sizeof(T), nullptr, usage);
					// �־�ӳ�� CPU �������� GPU ����ָ��
					if (data != nullptr) {
						T* buffer = static_cast<T*>(glMapBufferRange(bufferType, 0, dataSize * sizeof(T), GL_MAP_WRITE_BIT));
						if (!buffer) {
							std::cerr << "[Model::BindBufferObject]Bind buffer object error:GPU mapping failed." << std::endl;
							GLenum error = glGetError();
							if (error != GL_NO_ERROR) {
								std::cerr << "[Model::BindBufferObject]Bind buffer object error code:" << (int)error << std::endl;
							}
							return false;//���ӳ���Ƿ�ɹ�
						}
						else {
							// �������ݵ�������
							std::memcpy(buffer, data, dataSize * sizeof(T));
							glUnmapBuffer(bufferType); //ȡ��ӳ��
						}
					}
					if (bufferType == GL_ARRAY_BUFFER) {
						/*
							-1.���ö�������ָ��
							0.���������׸�Ԫ�ص�����
							1.���ٸ��������һ��vec����
							2.vec������������
							3.�Ƿ�����ݹ�һ��(0-1)��?
							4.һ��vec����Ĵ�С
							5.�����ڻ�������ʼλ�õ�ƫ����
						*/
						glVertexAttribPointer(attributeIndex, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(T), (void*)0);
						glEnableVertexAttribArray(attributeIndex); // ���ö�������
					}
					return true;
				};
            };
        }
    }
}