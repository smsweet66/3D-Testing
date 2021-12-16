#include "pch.hpp"

#pragma once

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
public:
	Shader(const std::string &vertexPath, const std::string &fragmentPath);

	~Shader();

	void bind() const;

	void unbind() const;

	void setUniform1i(const std::string& name, int value) const;

	void setUniform3f(const std::string& name, float v1, float v2, float v3) const;

	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const;

	void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;

private:
	unsigned int compileShader(unsigned int type, const std::string& source);

	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	ShaderSource parseShader();

	unsigned int getUniformLocation(const std::string& name) const;

	mutable std::unordered_map<std::string, int> uniformLocationCache;
	unsigned int ID;
};