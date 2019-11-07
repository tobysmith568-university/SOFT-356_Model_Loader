#pragma once

#include <stdexcept>

class InvalidModelFileException : public std::runtime_error
{
public:
	InvalidModelFileException(char const* const fileLocation, char const* const message);
	InvalidModelFileException(char const* const fileLocation, std::runtime_error inner);

private:
	char const* const fileLocation;
};