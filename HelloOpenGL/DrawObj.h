#pragma once
#include<glad/glad.h>
#include"Shader.h"
class DrawObj
{
public:
	DrawObj(Shader* shader, GLenum usage = GL_DYNAMIC_DRAW);
	~DrawObj()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

	}
	void SetShader(Shader* shader);
	void BindArrayBuffer(GLuint location, float verteices[],int vcount);
	void BindElement(unsigned int indeices[],int icount);
	virtual void OnDraw(){}//可在其中设定shader及传入的uniform
	void Draw();
protected:
	Shader* shader;
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLenum usage;
};

