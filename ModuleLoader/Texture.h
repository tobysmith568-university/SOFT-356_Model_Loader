#pragma once

#include "GLFW/glfw3.h"

class Texture
{
public:
	Texture(GLint _width, GLint _height, GLint _nrChannels, unsigned char* _data);

	GLint GetWidth();
	GLint GetHeight();
	GLint GetNrChannels();
	unsigned char* GetData();
	void FreeData();

private:
	GLint width, height, nrChannels;
	unsigned char* data;
};