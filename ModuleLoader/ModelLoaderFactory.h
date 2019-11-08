#pragma once

#include "FileUtils.h"
#include "ConsoleUtil.h"
#include "IModelLoader.h"

#include <string>
#include <map>
#include <memory>

class ModelLoaderFactory
{
public:
	ModelLoaderFactory(FileUtils& _fileUtils, ConsoleUtil _consoleUtil);
	IModelLoader& GetLoaderForFile(std::string fileLocation);

private:
	FileUtils fileUtils;
	ConsoleUtil consoleUtil;
};