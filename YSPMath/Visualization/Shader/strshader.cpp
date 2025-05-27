/*
	Created by YSP on 2025-05-15.
*/
#include "strshader.h"
namespace ysp {
	namespace gl {
		std::string V_Line2DShader = R"(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
            }
        )";

        std::string F_Line2DShader = R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec4 color;
            void main()
            {
                FragColor = color; 
            }
        )";
	}
}