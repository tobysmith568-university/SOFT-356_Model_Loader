#pragma once

#include "FileUtils.h"
#include "IModelLoader.h"

#include <string>

class ModelLoaderFactory
{
public:
	ModelLoaderFactory(FileUtils& _fileUtils);
	IModelLoader& GetLoaderForFile(std::string fileLocation);

private:
	FileUtils fileUtils;
};