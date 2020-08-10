#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Shader.h"
#include<fstream>
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void InitVertex(unsigned int* indices, int icount, GLuint& VAO, GLuint& VBO, GLuint& EBO);


//��������
float vertices[] =
{
  0.5f, 0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
-0.5f,0.0f, 0.0f,
0.0f,0.5f, 0.0f,
0.0f,0.0f, 0.0f
};

float vertexColor[] =
{
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};
//��������
unsigned int indices[] = { 0,1,4 };
unsigned int indices2[] = { 3,4,2 };
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
	//���Ӳ��֧�ֵ���ඥ����������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	unsigned int VAO,VBO,EBO;
	unsigned int VAO2;
	//�ǵ��޸������Сʱ�޸Ĵ����int����
	InitVertex(indices,1,VAO, VBO, EBO);
	InitVertex(indices2,1,VAO2,VBO, EBO);
	
	Shader timechangeShader("VertexShader", "FragmentShader");
	Shader blueShader("VertexShader", "FragmentShader2");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//input
		glClear(GL_COLOR_BUFFER_BIT);//clear

		float time = glfwGetTime();
		float greenValue = (sin(time) / 2.0f) + 0.5f;

		timechangeShader.use();
		timechangeShader.setFloat("unifCol",greenValue);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		blueShader.use();
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}


void InitVertex(unsigned int* indices, int icount, GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
	//�Ӱ�֮��������Ӧ�ð󶨺����ö�Ӧ��VBO������ָ�룬֮����VAO��֮��ʹ��
	//Ҳ���Բ���ʽ�����Ϊ�������ط�ʹ��ʱ��󶨵�����VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//��������md
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * icount, indices, GL_STATIC_DRAW);

	//��id=1����һ��VBO����
	glGenBuffers(1, &VBO);
	//�󶨵����㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//�Ѷ������ݸ��Ƶ�������ڴ���
	//��������md
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//���Ӷ�������
	//����opengl��ν��Ͷ�������
	//��������md
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//���ö�������ָ��
	glEnableVertexAttribArray(0);


	//unbind,�˴�Ҳ���Բ�д
	//this is allowed����Ϊ�Ѿ���VBO�����˶������ԣ����Խ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
