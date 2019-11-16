#pragma once

#include <stdexcept>

class InvalidModelFileException
{
public:
	InvalidModelFileException(std::string fileLocation, std::string message);

	std::string What();
private:
	std::string fileLocation;
	std::string message;
};