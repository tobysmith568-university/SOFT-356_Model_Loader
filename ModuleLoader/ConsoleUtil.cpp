#include "ConsoleUtil.h"

#include <iostream>

using namespace std;

ConsoleUtil::ConsoleUtil(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void ConsoleUtil::ClearConsole()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

void ConsoleUtil::Print(string message)
{
	cout << message;
}

string ConsoleUtil::GetInput(string question)
{
	cout << endl << question << endl << "--> ";

	string result;
	cin >> result;

	return result;
}

std::string ConsoleUtil::GetFileName(std::string question)
{
	string input = GetInput(question);
	while (!fileUtils.DoesFileExist(input))
	{
		ClearConsole();
		Print("File does not exist!");
		input = GetInput(question);
	}

	return input;
}