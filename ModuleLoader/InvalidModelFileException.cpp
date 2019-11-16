#include "InvalidModelFileException.h"

InvalidModelFileException::InvalidModelFileException(std::string fileLocation, std::string message)
	: fileLocation(fileLocation), message(message)
{
}

std::string InvalidModelFileException::What()
{
	std::string result = "\n\nThere was a problem with the file:\n"
		+ fileLocation;

	if (message.size() > 0)
	{
		result += "\n\n" + message;
	}

	return result;
}