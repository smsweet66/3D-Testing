#include "pch.hpp"

namespace Renderer
{
	static void draw(const VertexArray &va, const Shader &shader, unsigned int count)
	{
		shader.bind();
		va.bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
	}
}