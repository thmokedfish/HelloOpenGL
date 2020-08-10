#include"DrawObj.h"




DrawObj::DrawObj(Shader* shader,GLenum usage=GL_DYNAMIC_DRAW)
	:shader(shader),usage(usage)
{
	glGenVertexArrays(1, &VAO);
}

void DrawObj::ReSetShader(Shader* shader)
{
	this->shader = shader;
}

void DrawObj::BindVertex(GLuint location,float vertices[],int vcount)
{
	unsigned int VBO;
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	std::cout<<"VBO"<<VBO<<std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vcount, vertices, usage);

	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//设置顶点属性指针
	glEnableVertexAttribArray(location);
}

void DrawObj::BindElement(unsigned int indices[],int icount)
{
	unsigned int EBO;
	glBindVertexArray(VAO);
	glGenBuffers(1, &EBO);
	std::cout << "EBO" << EBO << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * icount, indices, usage);
}


void DrawObj::Draw()
{
	OnDraw();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
