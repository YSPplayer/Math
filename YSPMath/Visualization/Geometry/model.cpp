/*
    Created by YSP on 2025-05-11.
*/
#include "model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <util.h>
namespace ysp {
    namespace gl {
        namespace geometry {
            Model::Model() {
                vao = NULL;
                type = -1;
                empty = true;
                vsize = 0;
                vshader = "";
                fshader = "";
                name = "";
                args = nullptr;
            }

            Model::~Model() {
                for (int i = 0; i < vbodatas.size(); ++i)
                    glDeleteBuffers(1, &vbodatas.at(i).vbo);
                if (vao) glDeleteVertexArrays(1, &vao);
            }

            bool Model::Build(int type) {
                if (vbodatas.size() <= 0) return false;
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);
                for (int i = 0; i < vbodatas.size(); ++i) {
                    if (vbodatas[i].type == GL_EBO_TYPE_VECTOR) {
                        vsize = vbodatas[i].data.size();
                        centerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
                        if (type & GL_SHOW_TYPE_2D) {
                            glm::vec3 maxPosition(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), 0.0f);
                            glm::vec3 minPosition(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), 0.0f);
                            int pointCount = vsize / 2;
                            for (int j = 0; j < pointCount; ++j) {
                                float x = vbodatas[i].data[j * 2 + 0];
                                float y = vbodatas[i].data[j * 2 + 1];
                                maxPosition.x = std::max(maxPosition.x, x);
                                maxPosition.y = std::max(maxPosition.y, y); 
                                minPosition.x = std::min(minPosition.x, x); 
                                minPosition.y = std::min(minPosition.y, y);
                                centerPosition.x += x;
                                centerPosition.y += y;
                            }
                            modelSize = glm::length(maxPosition - minPosition);
                            centerPosition.x /= pointCount;
                            centerPosition.y /= pointCount;
                        }
                    } 
                    if (!BindBufferObject<float>(vbodatas[i].vbo, vbodatas[i].bufferType, vbodatas[i].data.data(),
                        vbodatas[i].data.size(), i, vbodatas[i].attributeIndex, vbodatas[i].usage)) return false;

                }
                if (shader.CreateShader(vshader, fshader)) {
                    empty = false;
                    this->type = type;
                    return true;
                }
                return false;
            }

            /// <summary>
            /// 模型旋转
            /// </summary>
            /// <param name="angle"></param>
            void Model::Rotate(const Point2D& center, const Angle& angle) {
                if (type & GL_SHOW_TYPE_2D) {
                    auto vector = vbodatas[GL_EBO_TYPE_VECTOR].data;
                    int pointsize = vector.size() / 2;
                    for (int i = 0; i < pointsize; ++i) {
                        int index1 = i * 2 + 0;
                        int index2 = i * 2 + 1;
                        const Point2D& point = Point2D(vector[index1],vector[index2]).Rotate(center, angle);
                        vector[i * 2 + 0] = point.X();
                        vector[i * 2 + 1] = point.Y();
                    }
                    BindBufferObject<float>(vbodatas[GL_EBO_TYPE_VECTOR].vbo, vbodatas[GL_EBO_TYPE_VECTOR].bufferType, vector.data(),
                        vector.size(), GL_EBO_TYPE_VECTOR, vbodatas[GL_EBO_TYPE_VECTOR].attributeIndex, vbodatas[GL_EBO_TYPE_VECTOR].usage);
                }
            }
            void Model::Render(RenderData& rdata, Camera& camera) {
                if (empty) return;
                glBindVertexArray(vao);
                shader.UseShader();
                //渲染相机
                CameraAttribute& cameraAttribute = camera.cameraAttribute;
                shader.SetShaderMat4(glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), "mposition");
                shader.SetShaderMat4(cameraAttribute.view, "view");
                shader.SetShaderMat4(cameraAttribute.projection, "projection");
                shader.SetShaderVec3(cameraAttribute.position, "viewPos");
                if (type & GL_SHOW_TYPE_2D) {
                    Color color(255, 255, 255);
                    if (name != "Line2DAxis" && rdata.isRotationZ) {
                        Rotate(Point2D(centerPosition.x, centerPosition.y), rdata.rotationZ);
                    }
                    if (args) {
                        color = *static_cast<Color*>(args[0]);
                    }
                    shader.SetShaderVec4(glm::vec4(color.RF(), color.GF(), color.BF(), color.AF()),"color");
                    glEnable(GL_LINE_SMOOTH);
                    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable(GL_MULTISAMPLE);
                    glLineWidth(1.45f);
                    glDrawArrays(GL_LINES, 0, vsize / 2);
                    if (args) {
                        Util::ReleasePointer<Color>(args[0]);
                        Util::ReleasePointer(args, true);
                    }
                }
            }

        }
    }
}