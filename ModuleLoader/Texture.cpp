#include "Texture.h"
#include "stb_image.h"

Texture::Texture(GLint _width, GLint _height, GLint _nrChannels, unsigned char* _data)
	: width(_width), height(_height), nrChannels(_nrChannels), data(_data)
{
}

GLint Texture::GetWidth()
{
	return width;
}

GLint Texture::GetHeight()
{
	return height;
}

GLint Texture::GetNrChannels()
{
	return nrChannels;
}

unsigned char* Texture::GetData()
{
	return data;
}

void Texture::FreeData()
{
	stbi_image_free(data);
}
