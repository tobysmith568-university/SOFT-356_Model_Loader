#pragma once

#include "GLFW/glfw3.h"

#include <vector>

class Source
{
public:

	const std::vector<GLfloat> GetData();
	void SetData(std::vector<GLfloat> _data);

	const GLuint GetStride();
	void SetStride(GLuint _stride);

private:
	std::vector<GLfloat> data;
	GLuint stride;
};

