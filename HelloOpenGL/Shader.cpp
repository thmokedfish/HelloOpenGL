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
	��ɫ���������(Shader Program Object)�Ƕ����ɫ���ϲ�֮������������ɵİ汾��
	���Ҫʹ�øղű������ɫ�����Ǳ������������(Link)Ϊһ����ɫ���������Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
	�Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ�á�
	*/
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infolog[512];
	//��֤�Ƿ����ӳɹ�
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infolog);
	}
	//���ӵ���������ɾ����ɫ������
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

	//������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//��ȡshaderԴ��
	shaderSource=Read(filename);
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

unsigned int getFragmentShader(const char* filename)
{
	std::string shaderSource;
	shaderSource.reserve(128);
	//Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//��ȡshaderԴ��
	shaderSource=Read(filename);
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
