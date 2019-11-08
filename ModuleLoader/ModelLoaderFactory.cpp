#include "ModelLoaderFactory.h"
#include "BasicModelLoader.h"
#include "ObjModelLoader.h"

#include <stdexcept>

using namespace std;

ModelLoaderFactory::ModelLoaderFactory(FileUtils& _fileUtils, ConsoleUtil _consoleUtil)
									  : fileUtils(_fileUtils), consoleUtil(_consoleUtil)
{
}

IModelLoader& ModelLoaderFactory::GetLoaderForFile(std::string fileLocation)
{
	string fileExtension = fileUtils.GetExtension(fileLocation);
	
	if (fileExtension == "basic")
	{
		static BasicModelLoader b = BasicModelLoader(fileUtils, consoleUtil);
		return b;
	}
	else if (fileExtension == "obj")
	{
		static ObjModelLoader o = ObjModelLoader(fileUtils);
		return o;
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}