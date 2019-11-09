#include "ModelLoaderFactory.h"
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
	
	if (fileExtension == "obj")
	{
		static MtlLoader mtlLoader = MtlLoader();
		static ObjModelLoader objModelLoader = ObjModelLoader(fileUtils, mtlLoader);
		return objModelLoader;
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}