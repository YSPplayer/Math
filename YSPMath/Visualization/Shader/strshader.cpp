/*
	Created by YSP on 2025-05-15.
*/
#include "strshader.h"
namespace ysp {
	namespace gl {
		std::string V_Line2DShader = R"(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            uniform mat4 view;
		    uniform mat4 projection;
            uniform mat4 mposition;
            void main()
            {
                vec3 fragPos = vec3(mposition * vec4(aPos.x, aPos.y, 0.0,1.0));
                gl_Position = projection * view * vec4(fragPos, 1.0);
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