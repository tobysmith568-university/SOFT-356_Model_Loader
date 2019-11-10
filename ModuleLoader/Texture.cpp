#include "Texture.h"
#include "stb_image.h"

Texture::Texture()
{
}

GLint Texture::GetWidth()
{
	return width;
}

void Texture::SetWidth(GLint _width)
{
	width = _width;
}

GLint Texture::GetHeight()
{
	return height;
}

void Texture::SetHeight(GLint _height)
{
	height = _height;
}

GLint Texture::GetNrChannels()
{
	return nrChannels;
}

void Texture::SetNrChannels(GLint _nrChannels)
{
	nrChannels = _nrChannels;
}

const unsigned char* Texture::GetData()
{
	return data;
}

void Texture::SetData(const unsigned char* _data)
{
	data = _data;
}

void Texture::FreeData()
{
	//stbi_image_free(data);
}
