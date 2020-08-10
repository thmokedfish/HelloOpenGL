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
	void ReSetShader(Shader* shader);
	void BindVertex(GLuint location, float verteices[],int vcount);
	void BindElement(unsigned int indeices[],int icount);
	virtual void OnDraw(){}//���������趨shader�������uniform
	void Draw();
protected:
	Shader* shader;
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLenum usage;
};

