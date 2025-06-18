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
#include "../../Math/Geometry/triangle.h"
#include "../../Math/Geometry/vector.h"
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
				/// 检查当前模型是否为空
				/// </summary>
				/// <returns></returns>
				inline bool IsEmpty() {
					return empty;
				}

				/// <summary>
				/// 设置顶点着色器
				/// </summary>
				inline void SetVShader(const std::string& vshader) {
					this->vshader = vshader;
				};

				/// <summary>
				/// 设置片段着色器
				/// </summary>
				inline void SetFShader(const std::string& fshader) {
					this->fshader = fshader;
				}

				/// <summary>
				/// 设置VBO
				/// </summary>
				inline void SetVBOS(const std::vector<VBOData>& vbodatas) {
					this->vbodatas = vbodatas;
				};
				
				/// <summary>
				/// 获取到指定的VBO数据
				/// </summary>
				/// <returns></returns>
				inline VBOData* GetVBOS(int index) {
					return &vbodatas[index];
				}
				
				/// <summary>
				/// 构建模型
				/// </summary>
				bool GL_FUNC Build(int type);

				/// <summary>
				/// 设置模型的名称
				/// </summary>
				/// <param name="name"></param>
				inline void SetName(const std::string& name) {
					this->name = name;
				}

				/// <summary>
				/// 获取到模型的名称
				/// </summary>
				/// <returns></returns>
				inline std::string GetName() const {
					return name;
				}

				/// <summary>
				/// 设置渲染参数
				/// </summary>
				inline void SetRenderArgs(void** args) {
					this->args = args;
				}

				/// <summary>
				/// 获取到模型包围盒大小
				/// </summary>
				/// <returns></returns>
				inline float GetModelSize() const {
					return modelSize;
				}

				/// <summary>
				/// 旋转模型
				/// </summary>
				void Rotate(const Point2D& center,const Angle& angle);

				/// <summary>
				/// 移动模型
				/// </summary>
				void Move(const Vector2D& vector2d);

				/// <summary>
				/// 缩放模型
				/// </summary>
				/// <param name="vector2d"></param>
				void Scale(double value);

				/// <summary>
				/// 更新顶点数组
				/// </summary>
				void UpdateVecter();

				/// <summary>
				/// 渲染模型
				/// </summary>
				virtual void GL_FUNC Render(RenderData& rdata,Camera& camera);

				/// <summary>
				/// 获取到模型的中心坐标
				/// </summary>
				/// <returns></returns>
				inline glm::vec3 GetCenterPosition() const {
					return centerPosition;
				}

				/// <summary>
				/// 设置几何图形
				/// </summary>
				/// <param name="geometry"></param>
				inline void SetGeometry(Object* geometry) {
					this->geometry = geometry;
				}
				void** args;//渲染参数
            private:
				Object* geometry;
				int type;
				int vsize;//顶点数组元素个数
				bool empty;
				std::string name;//模型名称
				std::string vshader;
				std::string fshader;
				float modelSize;//模型包围盒大小
				glm::vec3 centerPosition;//模型点的中心坐标
                Shader shader;
                GLuint vao;
				std::vector<VBOData> vbodatas;
			  	Point2D Normalize(const Point2D& value);
				template<typename T>
				static bool GL_FUNC BindBufferObject(GLuint& oID, GLenum bufferType, const T* data, GLsizei dataSize, GLint attributeIndex, GLint componentsPerVertex, GLenum usage = GL_STATIC_DRAW) {
					//生成并绑定VBO
					bool empty = oID == NULL;
					if (empty) glGenBuffers(1, &oID);
					//设置当前VBO上下文
					glBindBuffer(bufferType, oID);
					//先绑定空指针，直接绑定存在显存溢出的问题
					if (empty) glBufferData(bufferType, dataSize * sizeof(T), nullptr, usage);
					// 持久映射 CPU 缓冲区到 GPU 数据指针
					if (data != nullptr) {
						T* buffer = static_cast<T*>(glMapBufferRange(bufferType, 0, dataSize * sizeof(T), GL_MAP_WRITE_BIT));
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