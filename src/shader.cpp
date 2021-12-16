#include "pch.hpp"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
: ID(0)
{
	std::ifstream vertexFile(vertexPath);
	char buf[200];
	std::string vertexSource;
	while(vertexFile.getline(buf, 200))
	{
		vertexSource += buf;
		vertexSource += '\n';
	}

	std::ifstream fragmentFile(fragmentPath);
	std::string fragmentSource;
	while(fragmentFile.getline(buf, 200))
	{
		fragmentSource += buf;
		fragmentSource += '\n';
	}

	ID = createShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{ glDeleteProgram(ID); }

void Shader::bind() const
{ glUseProgram(ID); }

void Shader::unbind() const
{ glUseProgram(0); }

/*
 takes the shader and compiles it, returning an id
 returns 0 if any errors were detected in compilation
*/
unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile ";
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		delete[] message;
		return 0;
	}

	return id;
}

/*
 generates the vertex and fragment shader and links them to a program
 the program is still not used untill explicitly stated
*/
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::setUniform1i(const std::string& name, int value) const
{ glUniform1i(getUniformLocation(name), value); }

void Shader::setUniform3f(const std::string& name, float v1, float v2, float v3) const
{ glUniform3f(getUniformLocation(name), v1, v2, v3); }

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const
{ glUniform4f(getUniformLocation(name), v1, v2, v3, v4); }

void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix) const
{ glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]); }

unsigned int Shader::getUniformLocation(const std::string& name) const
{ 
	if(uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	int location = glGetUniformLocation(ID, name.c_str());

	if(location == -1)
		std::cout << "Shader variable: " << name << " does not exist" << std::endl;

	uniformLocationCache[name] = location;
	return location;
}