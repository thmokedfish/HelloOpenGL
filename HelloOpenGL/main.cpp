#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Draw(GLuint& shaderProgram, GLuint& VAO);
void InitVertex(float vertices2[], int vcount, unsigned int indeices2[], int icount, GLuint& VAO, GLuint& VBO, GLuint& EBO);
void CompileShader(char* vertexFilename, char* fragFilename, GLuint& shaderProgram);
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


	//��������
	float vertices[] =
	{
	  0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f,0.0f, 0.0f,
	0.0f,0.5f, 0.0f,
	0.0f,0.0f, 0.0f
	};
	
	//��������
	unsigned int indeices[] = { 0,1,4 };
	unsigned int indeices2[] = { 3,4,2 };

	unsigned int VAO,VBO,EBO;
	unsigned int VAO2;
	unsigned int shaderProgram;
	unsigned int shaderProgram2;
	//�ǵ��޸������Сʱ�޸Ĵ����int����
	InitVertex(vertices, 5, indeices, 1, VAO, VBO, EBO);
	InitVertex(vertices, 5, indeices2, 1, VAO2, VBO, EBO);

	CompileShader((char*)"VertexShader.txt",(char*)"FragmentShader.txt",shaderProgram);
	CompileShader((char*)"VertexShader.txt", (char*)"FragmentShader2.txt", shaderProgram2);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//input
		glClear(GL_COLOR_BUFFER_BIT);//clear

		//draw
		Draw(shaderProgram,VAO);
		Draw(shaderProgram2, VAO2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}


inline void Read(const char* filename,std::string& str)
{
	std::ifstream readf;
	str.clear();
	readf.open(filename);
	char line[128];
	while (readf.getline(line, 128))
	{
		int i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '/')
			{
				if (line[i + 1] == '/')
				{
					break;
				}
			}
			str += line[i];
			i++;
		}
		str += '\n';
	}
	readf.close();
}

unsigned int getVertexShader(char* filename)
{
	std::string shaderSource;
	shaderSource.reserve(128);

	//������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//��ȡshaderԴ��
	Read(filename, shaderSource);
	const char* source = shaderSource.c_str();
	//��shaderԴ�븽�ӵ�shader������
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);
	//����Ƿ����ɹ�
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}
	return vertexShader;
}

unsigned int getFragmentShader(char* filename)
{
	std::string shaderSource;
	shaderSource.reserve(128);
	//Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//��ȡshaderԴ��
	Read(filename, shaderSource);
	const char* source = shaderSource.c_str();
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);

	//����Ƿ����ɹ�
	int success;
	char infolog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}
	return fragmentShader;
}

void CompileShader(char* vertexFilename,char* fragFilename,GLuint& shaderProgram)
{
	unsigned int vertexShader = getVertexShader(vertexFilename);
	unsigned int fragmentShader = getFragmentShader(fragFilename);
	/*
	��ɫ���������(Shader Program Object)�Ƕ����ɫ���ϲ�֮������������ɵİ汾��
	���Ҫʹ�øղű������ɫ�����Ǳ������������(Link)Ϊһ����ɫ���������Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
	�Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ�á�
	*/
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infolog[512];
	//��֤�Ƿ����ӳɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
	}
	//���ӵ���������ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void InitVertex(float vertices[],int vcount,unsigned int indeices[],int icount,GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
	//�Ӱ�֮��������Ӧ�ð󶨺����ö�Ӧ��VBO������ָ�룬֮����VAO��֮��ʹ��
	//Ҳ���Բ���ʽ�����Ϊ�������ط�ʹ��ʱ��󶨵�����VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3*icount, indeices, GL_STATIC_DRAW);

	//��id=1����һ��VBO����
	glGenBuffers(1, &VBO);
	//�󶨵����㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//�Ѷ������ݸ��Ƶ�������ڴ���
	//��������md
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*vcount, vertices, GL_STATIC_DRAW);



	//���Ӷ�������
	//����opengl��ν��Ͷ�������
	//��������md
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//���ö�������ָ��
	glEnableVertexAttribArray(0);

	//unbind,�˴�Ҳ���Բ�д
	//this is allowed����Ϊ�Ѿ���VBO�����˶������ԣ����Խ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Draw(GLuint& shaderProgram,GLuint& VAO)
{
	//����������
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

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
