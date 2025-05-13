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
				/// 检查当前模型是否为空
				/// </summary>
				/// <returns></returns>
				inline bool IsEmpty() {
					return empty;
				}

				/// <summary>
				/// 设置顶点着色器
				/// </summary>
				void SetVShader(const std::string& vshader) {
					this->vshader = vshader;
				};

				/// <summary>
				/// 设置片段着色器
				/// </summary>
				void SetFShader(const std::string& fshader) {
					this->fshader = fshader;
				}

				/// <summary>
				/// 设置VBO
				/// </summary>
				void SetVBOS(const std::vector<EBOData>& ebodatas) {
					this->ebodatas = ebodatas;
				};

				/// <summary>
				/// 构建模型
				/// </summary>
				bool Build();


				/// <summary>
				/// 渲染模型
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
					//生成并绑定VBO
					bool empty = oID == NULL;
					if (empty) glGenBuffers(1, &oID);
					//设置当前VBO上下文
					glBindBuffer(bufferType, oID);
					//先绑定空指针，直接绑定存在显存溢出的问题
					if (empty) glBufferData(bufferType, dataSize * sizeof(T), nullptr, usage);
					// 持久映射 CPU 缓冲区到 GPU 数据指针
					if (data != nullptr) {
						T* buffer = static_cast<T*>(glMapBufferRange(bufferType, 0, dataSize * sizeof(T), GL_MAP_WRITE_BIT | Gl_MAP_INVALIDATE_BUFFER_BIT));
						if (!buffer) {
							std::cerr << "[Model::BindBufferObject]Bind buffer object error:GPU mapping failed." << std::endl;
							GLenum error = glGetError();
							if (error != GL_NO_ERROR) {
								std::cerr << "[Model::BindBufferObject]Bind buffer object error code:" << (int)error << std::endl;
							}
							return false;//检查映射是否成功
						}
						else {
							// 复制数据到缓冲区
							std::memcpy(buffer, data, dataSize * sizeof(T));
							glUnmapBuffer(bufferType); //取消映射
						}
					}
					if (bufferType == GL_ARRAY_BUFFER) {
						/*
							-1.设置顶点属性指针
							0.顶点数据首个元素的索引
							1.多少个数据组成一个vec对象
							2.vec对象数据类型
							3.是否把数据归一化(0-1)中?
							4.一个vec对象的大小
							5.数据在缓冲中起始位置的偏移量
						*/
						glVertexAttribPointer(attributeIndex, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(T), (void*)0);
						glEnableVertexAttribArray(attributeIndex); // 启用顶点属性
					}
					return true;
				};
            };
        }
    }
}