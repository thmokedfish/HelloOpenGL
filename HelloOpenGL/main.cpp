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
	  0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f,0.0f, 0.0f,
	0.0f,0.5f, 0.0f,
	0.0f,0.0f, 0.0f
	};
	
	//索引数组
	unsigned int indeices[] = { 0,1,4 };
	unsigned int indeices2[] = { 3,4,2 };

	unsigned int VAO,VBO,EBO;
	unsigned int VAO2;
	unsigned int shaderProgram;
	unsigned int shaderProgram2;
	//记得修改数组大小时修改传入的int参数
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

	//创建着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//读取shader源码
	Read(filename, shaderSource);
	const char* source = shaderSource.c_str();
	//将shader源码附加到shader对象上
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);
	//检查是否编译成功
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
	//片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//读取shader源码
	Read(filename, shaderSource);
	const char* source = shaderSource.c_str();
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);

	//检查是否编译成功
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
	着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本。
	如果要使用刚才编译的着色器我们必须把它们链接(Link)为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。
	已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。
	*/
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infolog[512];
	//验证是否链接成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
	}
	//链接到程序对象后删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void InitVertex(float vertices[],int vcount,unsigned int indeices[],int icount,GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
	//从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用
	//也可以不显式解绑，因为在其他地方使用时会绑定到其他VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3*icount, indeices, GL_STATIC_DRAW);

	//用id=1生成一个VBO对象
	glGenBuffers(1, &VBO);
	//绑定到顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//把顶点数据复制到缓冲的内存中
	//参数查阅md
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*vcount, vertices, GL_STATIC_DRAW);



	//链接顶点属性
	//告诉opengl如何解释顶点数据
	//参数查阅md
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//设置顶点属性指针
	glEnableVertexAttribArray(0);

	//unbind,此处也可以不写
	//this is allowed，因为已经把VBO链接了顶点属性，可以解绑了
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Draw(GLuint& shaderProgram,GLuint& VAO)
{
	//激活程序对象
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
