#include "ModelLoaderFactory.h"
#include "ObjModelLoader.h"
#include "BasicModelLoader.h"

#include <stdexcept>

using namespace std;

ModelLoaderFactory::ModelLoaderFactory(FileUtils& _fileUtils, ConsoleUtil _consoleUtil)
									  : fileUtils(_fileUtils), consoleUtil(_consoleUtil)
{
}

IModelLoader& ModelLoaderFactory::GetLoaderForFile(std::string fileLocation)
{
	string fileExtension = fileUtils.GetExtension(fileLocation);
	
	if (fileExtension == "obj")
	{
		static MtlLoader mtlLoader = MtlLoader(fileUtils);
		static ObjModelLoader objModelLoader = ObjModelLoader(fileUtils, consoleUtil, mtlLoader);
		return objModelLoader;
	}
	else if (fileExtension == "basic")
	{
		static BasicModelLoader basicModelLoader = BasicModelLoader(fileUtils);
		return basicModelLoader;
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}