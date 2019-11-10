#pragma once

#include "GLFW/glfw3.h"

#include <string>

class Material
{
public:
	Material();

	std::string name;

	GLfloat specularColourWeight = 0;
	GLfloat dissolve = 0;
	GLfloat illuminationModel = 0;
	
	std::string ambientTextureMap;
	std::string diffuseTextureMap;
	std::string alphaTextureMap;
};