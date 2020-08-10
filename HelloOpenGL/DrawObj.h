#pragma once
#include<glad/glad.h>
#include"Shader.h"
class DrawObj
{
public:
	DrawObj(Shader* shader, GLenum usage);
	void ReSetShader(Shader* shader);
	void BindVertex(GLuint location, float verteices[],int vcount);
	void BindElement(unsigned int indeices[],int icount);
	virtual void OnDraw(){}//可在其中设定shader及传入的uniform
	void Draw();
protected:
	Shader* shader;
private:
	GLuint VAO;
	GLenum usage;
};

