#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Texture
{
public:
	Texture();

	std::string GetPath();
	void SetPath(std::string _path);

	GLint GetWidth();
	void SetWidth(GLint _width);

	GLint GetHeight();
	void SetHeight(GLint _height);

	GLint GetNrChannels();
	void SetNrChannels(GLint _nrChannels);

	const unsigned char* GetData();
	void SetData(const unsigned char* _data);

private:
	std::string path;
	GLint width, height, nrChannels;
	const unsigned char* data;
};