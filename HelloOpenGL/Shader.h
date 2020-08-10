#pragma once
#include<glad\glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
	unsigned int ID;
	Shader(const std::string& vertexFilename, const std::string& fragFilename);
	~Shader();
	void use();
	void setBool(const std::string& name,bool value) const;
	void setInt(const std::string& name,int value) const;
	void setFloat(const std::string& name,float value) const;
	unsigned int& getProgram() { return ID; }
	
};

