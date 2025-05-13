/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <vector>
#include "../Shader/shader.h"
#include "data.h"
using namespace ysp::gl;
namespace ysp {
    namespace gl {
        namespace geometry {
            class Model {
            public:
                Model();
				~Model();
				
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
				void SetVShader(const std::string& vshader) {
					this->vshader = vshader;
				};

				/// <summary>
				/// ����Ƭ����ɫ��
				/// </summary>
				void SetFShader(const std::string& fshader) {
					this->fshader = fshader;
				}

				/// <summary>
				/// ����VBO
				/// </summary>
				void SetVBOS(const std::vector<EBOData>& ebodatas) {
					this->ebodatas = ebodatas;
				};

				/// <summary>
				/// ����ģ��
				/// </summary>
				bool Build();


				/// <summary>
				/// ��Ⱦģ��
				/// </summary>
				virtual void Render();
            private:
				bool empty;
				std::string vshader;
				std::string fshader;
                Shader shader;
                GLuint vao;
				std::vector<EBOData> ebodatas;
				template<typename T>
				static bool BindBufferObject(GLuint& oID, GLenum bufferType, const T* data, GLsizei dataSize, GLint attributeIndex, GLint componentsPerVertex, GLenum usage = GL_STATIC_DRAW) {
					//���ɲ���VBO
					bool empty = oID == NULL;
					if (empty) glGenBuffers(1, &oID);
					//���õ�ǰVBO������
					glBindBuffer(bufferType, oID);
					//�Ȱ󶨿�ָ�룬ֱ�Ӱ󶨴����Դ����������
					if (empty) glBufferData(bufferType, dataSize * sizeof(T), nullptr, usage);
					// �־�ӳ�� CPU �������� GPU ����ָ��
					if (data != nullptr) {
						T* buffer = static_cast<T*>(glMapBufferRange(bufferType, 0, dataSize * sizeof(T), GL_MAP_WRITE_BIT | Gl_MAP_INVALIDATE_BUFFER_BIT));
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