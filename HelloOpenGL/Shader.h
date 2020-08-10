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
	inline void setBool(const std::string& name,bool value) const;
	inline void setInt(const std::string& name,int value) const;
	inline void setFloat(const std::string& name,float value) const;
	unsigned int& getProgram() { return ID; }
	
};

inline void Shader::setBool(const std::string& name, bool value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}
inline void Shader::setFloat(const std::string& name, float value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformVal, value);
}
inline void Shader::setInt(const std::string& name, int value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}

inline void Shader::use()
{
	glUseProgram(ID);
}

