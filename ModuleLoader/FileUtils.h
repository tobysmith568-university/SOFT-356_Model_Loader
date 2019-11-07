#pragma once

#include "GL/glew.h"

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
	std::string ReadFile(std::string fileLocation);
	std::vector<std::string> ReadFileAsLines(std::string fileLocation);
};