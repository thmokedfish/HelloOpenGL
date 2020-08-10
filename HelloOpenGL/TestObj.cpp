#include"DrawObj.h"
#include<GLFW\glfw3.h>
class TestObj:public DrawObj
{
public:
	void OnDraw() override
	{
		float time = glfwGetTime();
		float greenValue = (sin(time) / 2.0f) + 0.5f;
		this->shader->setFloat("unifCol", greenValue);
	}
};