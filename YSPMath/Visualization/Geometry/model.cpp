#include "model.h"
#include <util.h>
namespace ysp {
    namespace gl {
        namespace geometry {
            Model::Model() {
                vao = NULL;
                empty = true;
                vshader = "";
                fshader = "";
            }

            Model::~Model() {
                for (int i = 0; i < ebodatas.size(); ++i)
                    glDeleteBuffers(1, &ebodatas.at(i).vbo);
                if (vao) glDeleteVertexArrays(1, &vao);
            }

            bool Model::Build() {
                if (ebodatas.size() <= 0) return false;
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);
                for (int i = 0; i < ebodatas.size(); ++i) {
                    if (!BindBufferObject<float>(ebodatas[i].vbo, GL_ARRAY_BUFFER, ebodatas[i].data.data(),
                        ebodatas[i].data.size(), i, ebodatas[i].attributeIndex, ebodatas[i].usage)) return false;

                }
                if (shader.CreateShader(vshader, fshader)) {
                    empty = false;
                    return true;
                }
                return false;
            }

            void Model::Render()
            {
            }

        }
    }
}