#include "ModelLoaderFactory.h"
#include "BasicModelLoader.h"

#include <stdexcept>

using namespace std;

ModelLoaderFactory::ModelLoaderFactory(FileUtils& _fileUtils)
									  : fileUtils(_fileUtils)
{
}

IModelLoader& ModelLoaderFactory::GetLoaderForFile(std::string fileLocation)
{
	string fileExtension = fileUtils.GetExtension(fileLocation);

	if (fileExtension == "basic")
	{
		static BasicModelLoader b(fileUtils);
		return b;
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}