#pragma once

#include "GLFW/glfw3.h"

class Texture
{
public:
	Texture();

	GLint GetWidth();
	void SetWidth(GLint _width);

	GLint GetHeight();
	void SetHeight(GLint _height);

	GLint GetNrChannels();
	void SetNrChannels(GLint _nrChannels);

	const unsigned char* GetData();
	void SetData(const unsigned char* _data);

	void FreeData();

private:
	GLint width, height, nrChannels;
	const unsigned char* data;
};