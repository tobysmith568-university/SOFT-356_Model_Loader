#include "ConsoleUtil.h"

#include <iostream>

using namespace std;

ConsoleUtil::ConsoleUtil(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

// Clears the console by printing 30 newline characters
void ConsoleUtil::ClearConsole()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

// Prints a message to the console
void ConsoleUtil::Print(string message)
{
	cout << message;
}

// Prints a question to the console and then prompts for an answer
string ConsoleUtil::GetInput(string question)
{
	cout << endl << question << endl << "--> ";

	string result;
	getline(cin, result);

	return result;
}

// Prints a question to the console, and continues to prompt for an answer until the answer is a valid file path
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