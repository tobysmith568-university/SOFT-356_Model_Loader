#include "InvalidModelFileException.h"

InvalidModelFileException::InvalidModelFileException(char const* const fileLocation, char const* const message)
	: fileLocation(fileLocation), std::runtime_error(message)
{
}

InvalidModelFileException::InvalidModelFileException(char const* const fileLocation, std::runtime_error inner)
	: fileLocation(fileLocation), std::runtime_error(inner)
{
}