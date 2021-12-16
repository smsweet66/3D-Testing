#include "pch.hpp"

#pragma once

class Texture
{
public:
	Texture(const std::string& path);

	~Texture();

	void bind(unsigned int slot = 0) const;

	void unbind() const;

private:
	unsigned int ID;
	std::string filePath;
	unsigned char* buffer;
	int width, height, BPP;
};