#include "ModelLoaderFactory.h"
#include "ObjModelLoader.h"
#include "BasicModelLoader.h"
#include "DaeModelLoader.h"

#include <stdexcept>

using namespace std;

ModelLoaderFactory::ModelLoaderFactory(FileUtils& _fileUtils, ConsoleUtil _consoleUtil)
									  : fileUtils(_fileUtils), consoleUtil(_consoleUtil)
{
}

IModelLoader& ModelLoaderFactory::GetLoaderForFile(std::string fileLocation)
{
	string fileExtension = fileUtils.GetExtension(fileLocation);// Get the file extension from the file path
	
	if (fileExtension == "obj")// If this file extension is for a .obj file
	{
		static MtlLoader mtlLoader = MtlLoader(fileUtils);
		static ObjModelLoader objModelLoader = ObjModelLoader(fileUtils, consoleUtil, mtlLoader);
		return objModelLoader;// Create and return an ObjModelLoader
	}
	else if (fileExtension == "dae")// If this file extension is for a .dae file
	{
		static DaeModelLoader daeModelLoader = DaeModelLoader(fileUtils);
		return daeModelLoader;// Create and return a DaeModelLoader
	}
	else if (fileExtension == "basic")// If this file extension is for a .basic file
	{
		static BasicModelLoader basicModelLoader = BasicModelLoader(fileUtils);
		return basicModelLoader;// Create and return a BasicModelLoader
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}