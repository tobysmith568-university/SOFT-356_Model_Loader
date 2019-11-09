#pragma once

#include "GLFW/glfw3.h"

class Index
{
public:
	Index(GLuint _vertexIndex, GLuint _textureIndex, GLuint _normalIndex);

	GLuint vertexIndex;
	GLuint textureIndex;
	GLuint normalIndex;
};