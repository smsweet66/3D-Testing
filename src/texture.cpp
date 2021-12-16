#include "pch.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.hpp"

Texture::Texture(const std::string& path)
: ID(0), filePath(path), buffer(nullptr), width(0), height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	buffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	if(buffer)
		stbi_image_free(buffer);
}

Texture::~Texture()
{
	unbind();
	glDeleteTextures(1, &ID);
}

void Texture::bind(unsigned int slot) const
{ 
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const
{ glBindTexture(GL_TEXTURE_2D, 0); }