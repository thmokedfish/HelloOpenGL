#pragma once
#include"DrawObj.h"
#include<GLFW\glfw3.h>
class TestObj :public DrawObj
{
public:
	TestObj(Shader* shader, GLenum usage = GL_DYNAMIC_DRAW) :DrawObj(shader, usage)
	{}
	void OnDraw() override
	{
		float time = glfwGetTime();
		float greenValue = (sin(time) / 2.0f) + 0.5f;
		this->shader->setValue("unifCol", greenValue);
	}
};