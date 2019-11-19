#pragma once

#include "FileUtils.h"

#include <string>

class ConsoleUtil
{
public:
	ConsoleUtil(FileUtils& _fileUtils);
	void ClearConsole();
	void Print(std::string message);
	std::string GetInput(std::string question);
	std::string GetFileName(std::string question);

private:
	FileUtils& fileUtils;
};