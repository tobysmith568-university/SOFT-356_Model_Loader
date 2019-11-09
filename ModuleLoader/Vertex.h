#pragma once

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;

struct Vertex
{
public:
	Vertex();
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetTexture(GLfloat x, GLfloat y);
	void SetNormal(GLfloat x, GLfloat y, GLfloat z);

private:
	vec3 position;
	vec2 texture;
	vec3 normal;
};