#version 330 core

layout (location = 0) in vec3 aPos;     // 位置变量
layout (location = 1) in vec3 aColor;   // 颜色变量
layout (location = 2) in vec2 aTexCoord;// 纹理坐标

out vec3 ourColor;	// 向片段着色器输出一个颜色
out vec2 TexCoord;	// 输出纹理坐标	

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}