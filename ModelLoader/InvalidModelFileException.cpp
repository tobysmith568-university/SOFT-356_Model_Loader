#include "InvalidModelFileException.h"

InvalidModelFileException::InvalidModelFileException(std::string fileLocation, std::string message)
	: fileLocation(fileLocation), message(message)
{
}

std::string InvalidModelFileException::What()
{
	std::string result = "\n\nThere was a problem with the file:\n"
		+ fileLocation;// Create a default message

	if (message.size() > 0)
	{
		result += "\n\n" + message;// Add the message data if it exists
	}

	return result;
}