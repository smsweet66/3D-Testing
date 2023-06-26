#include "pch.hpp"

Mesh::Mesh(const std::string &inputFile, const std::string &textureFile, const Shader &shader)
: texture(textureFile), shader(shader)
{
	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attribute, &shapes, &materials, &warn, &err, inputFile.c_str());
	if (!warn.empty())
		std::cerr << "WARN:  " << warn << std::endl;
	if (!err.empty())
		std::cerr << "ERROR: " << err << std::endl;
	if (!ret)
		exit(1);

	unsigned int numIndices = 0;
	for(const auto &shape : shapes)
		numIndices += shape.mesh.indices.size();

	vertices.reserve(numIndices);
	for(const auto &shape : shapes)
	{
		for(const auto &index : shape.mesh.indices)
		{
			vertices.emplace_back(Vertex {
				glm::vec3(attribute.vertices[index.vertex_index*3], attribute.vertices[index.vertex_index*3 + 1], attribute.vertices[index.vertex_index*3 + 2]),
				glm::vec3(index.normal_index > 0 ? attribute.normals[index.normal_index*3] : 0,
				          index.normal_index > 0 ? attribute.normals[index.normal_index*3 + 1] : 0,
				          index.normal_index > 0 ? attribute.normals[index.normal_index*3 + 2] : 0),
				glm::vec2(index.texcoord_index > 0 ? attribute.texcoords[index.texcoord_index*2] : 0,
				          index.texcoord_index > 0 ? attribute.texcoords[index.texcoord_index*2 + 1] : 0)
			});
		}
	}

	VertexBufferLayout vbl;
	vbl.push<float>(3, GL_FALSE);
	vbl.push<float>(3, GL_FALSE);
	vbl.push<float>(2, GL_FALSE);

	vb.addData(&vertices[0], vertices.size()*sizeof(Vertex));
	va.addBuffer(vb, vbl);
	texture.bind();
}

void Mesh::draw() const
{
	texture.bind();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(1.0, 0.0, 0.0));
	shader.setUniformMat4("u_model", model);
	shader.setUniform1i("u_texture", 0);
	Renderer::draw(va, shader, vertices.size());
}