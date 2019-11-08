#pragma once

#include "IModelLoader.h"

class ObjModelLoader : public IModelLoader
{
public:
	ObjModelLoader();
	Model& GetModel(std::string fileLocation);

private:

};