#include "FileUtils.h"

using namespace std;

// Checks if a file exists or not
bool FileUtils::DoesFileExist(std::string& filePath)
{
	ifstream f(filePath.c_str());
	return f.good();
}

// Returns the .extension from a file path. The path can include folders and/or drives
string FileUtils::GetExtension(std::string& filePath)
{
	if (filePath.size() < 1)
	{
		throw invalid_argument("An empty file path was given");
	}

	string result = "";

	for (size_t i = filePath.size(); i > 0; i--)// Works through the path from back-to-front
	{
		if (filePath[i - 1] == '.')// If the char is a . then stop
		{
			return result;
		}

		result = filePath[i - 1] + result;// Otherwise, build up a result back-to-front
	}

	return result;
}

// Returns a file path with the .extension removed
std::string FileUtils::GetName(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument("An empty file path was given");
	}

	string result = "";

	bool foundDot = false;
	for (size_t i = fileLocation.size(); i > 0; i--)// Works through the path from back-to-front
	{
		if (foundDot)
		{
			result = fileLocation[i - 1] + result;// Builds up a result once a . has been found
		}
		else if (fileLocation[i - 1] == '.')// Otherwise, tests to see if a . has been found
		{
			foundDot = true;
		}
	}

	if (result == "")
	{
		throw invalid_argument("An extension was never found in the given path");
	}

	return result;
}

// Returns a file path with the file name and the .extension removed
std::string FileUtils::GetFolder(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument("An empty file path was given");
	}

	string result = "";

	bool foundSlash = false;
	for (size_t i = fileLocation.size(); i > 0; i--)// Works through the path from back-to-front
	{
		if (!foundSlash && (fileLocation[i - 1] == '/' || fileLocation[i - 1] == '\\'))// Declares that a slash is found if the current char is a \ or /
		{
			foundSlash = true;
		}

		if (foundSlash)
		{
			result = fileLocation[i - 1] + result;// Builds up a result once a / or \ has been found
		}
	}

	if (result == "")
	{
		throw invalid_argument("A slash was never found in the given path");
	}

	return result;
}

// Reads in a whole file into a single string result
string FileUtils::ReadFile(string fileLocation)
{
	ifstream stream(fileLocation);
	string content = string(istreambuf_iterator<char>(stream), istreambuf_iterator<char>());

	return content;
}

// Reads in a whole file into a vector of lines
vector<string> FileUtils::ReadFileAsLines(string fileLocation)
{
	vector<string> result = vector<string>();

	ifstream file(fileLocation);
	if (!file.is_open())
	{
		throw runtime_error("Could not open the given file");
	}

	string readLine;
	while (getline(file, readLine))// Reads in the file line by line
	{
		result.push_back(readLine);
	}

	return result;
}

// Saves a file to the machine. IMPORTANT: This will overwrite any existing data at the given file path
void FileUtils::SaveFile(std::string& data, std::string& fileLocation)
{
	ofstream file;
	file.open(fileLocation, ios::out | ios::trunc);

	if (!file.is_open())
	{
		throw runtime_error("Could not open the given file");
	}

	file << data;

	file.close();
}