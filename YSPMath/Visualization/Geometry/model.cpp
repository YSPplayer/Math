#include "model.h"
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
                    if (vbodatas[i].type == GL_EBO_TYPE_VECTOR) vsize = vbodatas[i].data.size();
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

            void Model::Render() {
                if (empty) return;
                glBindVertexArray(vao);
                shader.UseShader();
                if (type == GL_SHOW_TYPE_LINE2D) {
                    Color color(255, 255, 255);
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