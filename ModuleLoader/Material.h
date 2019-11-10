#pragma once

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

class Material
{
public:
	Material();

	std::string name;

	GLfloat specularColourWeight = 0;
	GLfloat dissolve = 0;
	GLfloat illuminationModel = 0;

	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;
	
	std::string ambientTextureMap;
	std::string diffuseTextureMap;
	std::string alphaTextureMap;
};