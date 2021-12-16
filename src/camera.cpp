#include "pch.hpp"

Camera::Camera(const glm::vec3& location, float theta, float phi, const Shader& shader)
: location(location), theta(theta), phi(phi), shader(shader)
{ shader.setUniformMat4("u_view", glm::lookAt(location, location + glm::vec3(-cos(phi)*sin(theta), sin(phi), cos(phi)*cos(theta)), glm::vec3(0.0f, 1.0f, 0.0f))); }

void Camera::update(GLFWwindow* window, const float timestep)
{
	float movementVec[2] = {0.0f};
	int state = glfwGetKey(window, GLFW_KEY_W);
	if(state == GLFW_PRESS)
	{
		movementVec[0] += -cos(phi)*sin(theta);
		movementVec[1] += cos(phi)*cos(theta);
	}

	state = glfwGetKey(window, GLFW_KEY_S);
	if(state == GLFW_PRESS)
	{
		movementVec[0] += cos(phi)*sin(theta);
		movementVec[1] += -cos(phi)*cos(theta);
	}

	state = glfwGetKey(window, GLFW_KEY_A);
	if(state == GLFW_PRESS)
	{
		movementVec[0] += -cos(phi)*sin(theta - 3.1415926f/2.0f);
		movementVec[1] += cos(phi)*cos(theta - 3.1415926f/2.0f);
	}

	state = glfwGetKey(window, GLFW_KEY_D);
	if(state == GLFW_PRESS)
	{
		movementVec[0] += -cos(phi)*sin(theta + 3.1415926f/2.0f);
		movementVec[1] += cos(phi)*cos(theta + 3.1415926f/2.0f);
	}

	state = glfwGetKey(window, GLFW_KEY_SPACE);
	if(state == GLFW_PRESS)
		location.y += 5.0f*timestep;

	state = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
	if(state == GLFW_PRESS)
		location.y -= 5.0f*timestep;

	double mousePos[2] = {0.0, 0.0};
	glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
	theta += mousePos[0]/750;
	phi -= mousePos[1]/750;
	if(phi > 3.14f/2.0f)
		phi = 3.14f/2.0f;
	else if(phi < -3.14f/2.0f)
		phi = -3.14f/2.0f;

	glfwSetCursorPos(window, 0, 0);

	float moveMag = std::sqrt(movementVec[0]*movementVec[0] + movementVec[1]*movementVec[1]);
	if(std::abs(moveMag) > 0.000001) //actually moving in x or z direction
	{
		movementVec[0] *= 5.0f/moveMag;
		movementVec[1] *= 5.0f/moveMag;
		location.x += movementVec[0]*timestep;
		location.z += movementVec[1]*timestep;
	}

	shader.setUniform3f("u_lightLoc", location.x, location.y, location.z);
	shader.setUniformMat4("u_view", glm::lookAt(location, location + glm::vec3(-cos(phi)*sin(theta), sin(phi), cos(phi)*cos(theta)), glm::vec3(0.0f, 1.0f, 0.0f)));
}