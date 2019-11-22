#pragma once

#include "GLFW/glfw3.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileUtils
{
public:
	bool DoesFileExist(std::string& fileLocation);
	std::string GetExtension(std::string& fileLocation);
	std::string GetName(std::string& fileLocation);
	std::string GetFileName(std::string& fileLocation);
	std::string GetFolder(std::string& fileLocation);

	void EnsureFolderExists(std::string& folderLocation);
	std::string ReadFile(std::string fileLocation);
	std::vector<std::string> ReadFileAsLines(std::string fileLocation);

	void SaveFile(std::string& data, std::string& fileLocation);
};