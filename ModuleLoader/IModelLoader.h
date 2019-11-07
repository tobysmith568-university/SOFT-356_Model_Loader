#pragma once
#include "Model.h"
#include "GLFW/glfw3.h"
#include <string>

class IModelLoader
{
public:
	virtual Model& GetModel(std::string fileLocation) = 0;
};