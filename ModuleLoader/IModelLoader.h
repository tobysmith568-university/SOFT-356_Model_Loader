#pragma once
#include "Model.h"
#include "GLFW/glfw3.h"
#include <string>

class IModelLoader
{
public:
	virtual void GetModel(Model& model, std::string fileLocation) = 0;
};