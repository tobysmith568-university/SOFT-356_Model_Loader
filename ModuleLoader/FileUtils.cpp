#include "FileUtils.h"

using namespace std;

bool FileUtils::DoesFileExist(std::string& filePath)
{
	ifstream f(filePath.c_str());
	return f.good();
}

string FileUtils::GetExtension(std::string& filePath)
{
	if (filePath.length() < 1)
	{
		return filePath;
	}

	string result = "";

	for (size_t i = filePath.length(); i > 0; i--)
	{
		if (filePath[i - 1] == '.')
		{
			return result;
		}

		result = filePath[i - 1] + result;
	}

	return result;
}

std::string FileUtils::GetName(std::string& fileLocation)
{
	if (fileLocation.length() < 1)
	{
		return fileLocation;
	}

	string result = "";

	bool foundDot = false;
	for (size_t i = fileLocation.length(); i > 0; i--)
	{
		if (foundDot)
		{
			result = fileLocation[i - 1] + result;
		}
		else if (fileLocation[i - 1] == '.')
		{
			foundDot = true;
		}
	}

	if (result == "")
	{
		return fileLocation;
	}

	return result;
}

string FileUtils::ReadFile(string fileLocation)
{
	ifstream stream(fileLocation);
	string content = string(istreambuf_iterator<char>(stream), istreambuf_iterator<char>());
	return content;
}

vector<string> FileUtils::ReadFileAsLines(string fileLocation)
{
	vector<string> result = vector<string>();

	ifstream file(fileLocation);
	if (!file.is_open())
	{
		//TODO: Error checking
		return result;
	}

	string readLine;
	while (getline(file, readLine))
	{
		result.push_back(readLine);
	}

	return result;
}
