#include "Texture.h"
#include "stb_image.h"

Texture::Texture()
{
	data = (const unsigned char*)"ÿÿÿ";// This data represents a single pixel which is 0,0,0,0 RGBA
	height = 1;
	width = 1;
	nrChannels = 4;
}

std::string Texture::GetPath()
{
	return path;
}

void Texture::SetPath(std::string _path)
{
	path = _path;
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