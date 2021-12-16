#include "pch.hpp"

typedef std::vector<tinyobj::shape_t> Shape;
typedef std::vector<tinyobj::material_t> Material;
typedef tinyobj::attrib_t Attribute;

constexpr unsigned int width = 2560, height = 1440, maxHertz = 60;

int main()
{
	if(!glfwInit())
	{
		std::cout << "GLFW could not be initialized";
		glfwTerminate();
		return 1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "3D-Testing", glfwGetPrimaryMonitor(), nullptr);
	if(!window)
	{
		std::cout << "Window creation failed";
		glfwTerminate();
		return 3;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return 3;
	}

	glEnable(GL_CULL_FACE);                             //only shows vertexes that face the camera
	glEnable(GL_DEPTH_TEST);                            //draws the closest thing
	glEnable(GL_BLEND);                                 //allows the use of alpha values
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //how blending is to be done

	{
		Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
		shader.bind();

		shader.setUniformMat4("u_proj", glm::perspective(45.0f, width/(float) height, 0.1f, 1000.0f));
		Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 0, 0, shader);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if(glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		else
			std::cout << "Raw mouse motion not supported!!!" << std::endl;

		Mesh object("res/objects/rungholt.obj", "res/objects/rungholt-RGBA.png", shader);

		double timestep = 1.0/maxHertz;
		glfwSwapBuffers(window);
		while(!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			camera.update(window, timestep);
			double start = glfwGetTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			object.draw();
			glfwSwapBuffers(window);

			double end = glfwGetTime();
			while(end - start < (1.0/maxHertz))
				end = glfwGetTime();

			timestep = (1/(end - start) < maxHertz ? end - start : 1.0/maxHertz);
		}

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}