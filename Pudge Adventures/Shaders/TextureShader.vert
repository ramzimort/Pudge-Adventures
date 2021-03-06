#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 ourColor;
out vec2 TexCoord;

layout (location = 0) uniform mat4 persp_matrix;
layout (location = 1) uniform mat4 view_matrix;
layout (location = 2) uniform mat4 model_matrix;

void main()
{
	gl_Position = persp_matrix*view_matrix*model_matrix*vec4(aPos.xy,0,1);
	ourColor = aColor;
	TexCoord = aTexCoord;
}