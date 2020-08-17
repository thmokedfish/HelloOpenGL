#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Shader.h"
#include<fstream>
#include<iostream>
#include"DrawObj.h"
#include"TestObj.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//输出硬件支持的最多顶点属性组数
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	//顶点数组
	float vertices[] =
	{
	  -0.5f,- 0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f,
	  0.0f,0.5f, 0.0f,
	  0.0f,0.1f, 0.0f,
	  0.0f,0.0f, 0.0f
	};

	float vertexColor[] =
	{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};
	//索引数组
	unsigned int indices[] = { 0,1,2 };
	unsigned int indices2[] = { 3,4,2 };
	
	Shader timechangeShader("VertexShader", "FragmentShader");
	Shader colorShader("VertexShader", "FragmentShader2");
	colorShader.use();
	colorShader.setValue("move", 0.5f);
	DrawObj obj(&colorShader);
	obj.BindArrayBuffer(0, vertices, 5);
	obj.BindArrayBuffer(1, vertexColor, 5);
	obj.BindElement(indices, 1);
	
	//TestObj changing(&timechangeShader);
	//changing.BindVertex(0, vertices, 5);
	//changing.BindElement(indices2, 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//input
		glClear(GL_COLOR_BUFFER_BIT);//clear

		obj.Draw();
		//changing.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



inline void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
