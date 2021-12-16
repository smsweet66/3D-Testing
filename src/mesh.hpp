#include "pch.hpp"

#pragma once

class Mesh
{
private:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t attribute;

	VertexBuffer vb;
	VertexArray va;
	Texture texture;
	Shader shader;

	std::vector<unsigned int> ibData;
	std::vector<Vertex> vertices;

public:
	Mesh(const std::string &inputFile, const std::string &textureFile, const Shader &shader);

	void draw() const;
};