#version 330 core

layout (location = 0) in vec3 aPos;     // 位置变量
layout (location = 1) in vec2 aTexCoord;// 纹理坐标

out vec3 ourColor;	// 向片段着色器输出一个颜色
out vec2 TexCoord;	// 输出纹理坐标	

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}