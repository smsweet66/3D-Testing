#include "pch.hpp"

#pragma once

class Camera
{
public:
	Camera(const glm::vec3& location, float theta, float phi, const Shader& shader);

	void update(GLFWwindow* window, const float timestep);

private:
	glm::vec3 location;
	float theta;
	float phi;
	Shader shader;
};