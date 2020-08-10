#include "Shader.h"

unsigned int getVertexShader(const char* filename);
unsigned int getFragmentShader(const char* filename);
inline std::string Read(const char* filename);

Shader::Shader(const std::string& vertexFilename, const std::string& fragFilename)
{
	std::string vname=vertexFilename + ".shader";
	std::string fname =fragFilename+ ".shader";
	unsigned int vertexShader = getVertexShader(vname.c_str());
	unsigned int fragmentShader = getFragmentShader(fname.c_str());
	/*
	着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本。
	如果要使用刚才编译的着色器我们必须把它们链接(Link)为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。
	已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。
	*/
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infolog[512];
	//验证是否链接成功
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infolog);
	}
	//链接到程序对象后删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader()
{
	glDeleteShader(ID);
}
void Shader::setBool(const std::string& name, bool value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformVal, value);
}
void Shader::setInt(const std::string& name, int value) const
{
	int uniformVal = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformVal, value);
}

void Shader::use()
{
	glUseProgram(ID);
}

unsigned int getVertexShader(const char* filename)
{
	std::string shaderSource;
	shaderSource.reserve(128);

	//创建着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//读取shader源码
	shaderSource=Read(filename);
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

unsigned int getFragmentShader(const char* filename)
{
	std::string shaderSource;
	shaderSource.reserve(128);
	//片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//读取shader源码
	shaderSource=Read(filename);
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

inline std::string Read(const char* filename)
{
	std::ifstream readf;
	std::string str;
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
	return std::move(str);
}
