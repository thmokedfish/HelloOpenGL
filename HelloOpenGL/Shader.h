#pragma once
#include<glad\glad.h>
#include <string>
#include <fstream>
#include <iostream>
class Shader
{
public:
	unsigned int ID;
	Shader(const std::string& vertexFilename, const std::string& fragFilename);
	~Shader();
	void use();
	void setValue(const std::string& name, bool value) const;
	inline void setValue(const std::string& name,int value) const;
	inline void setValue(const std::string& name,float value) const;
	unsigned int& getProgram() { return ID; }
	
};

inline void Shader::setValue(const std::string& name, bool value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}
inline void Shader::setValue(const std::string& name, float value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformVal, value);
}
inline void Shader::setValue(const std::string& name, int value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}

inline void Shader::use()
{
	glUseProgram(ID);
}

