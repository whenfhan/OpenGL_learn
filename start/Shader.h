#pragma once

#include <glad\glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// ����ID
	unsigned int ID;

	// ������������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setUniform(const std::string &name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
};

