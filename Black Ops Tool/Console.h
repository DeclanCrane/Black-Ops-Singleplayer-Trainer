#pragma once

#include <Windows.h>
#include <iostream>

// Color of Text
enum class ConsoleTextColor
{
	darkBlue		= 1,
	darkGreen		= 2,
	lightBlue		= 3,
	darkRed			= 4,
	purple			= 5,
	darkYellow		= 6,
	white			= 7,
	darkGrey		= 8,
	blue			= 9,
	green			= 10
};

// Type of Log
enum class LogType {
	Plain,
	Log,
	Warning,
	Error
};

struct ConsoleInfo {

	// Handle to the console
	HANDLE hConsole;

	// Pointer to the temp file
	FILE* fTemp;
};

class Console {

private:
	ConsoleInfo consoleInfo;

public:

	Console();

	~Console();

	// Allocates console, and redirects stream
	bool CreateConsole();

	// Cleans up and closes console
	void CloseConsole();

	// Sets the color of the text in the console
	void SetConsoleColor(ConsoleTextColor color);

	// Debug test for console colors
	void ConsoleColors();

	// Resets console color to default
	void ResetConsoleColor();

	// Prints to the console
	void Print(LogType logType, const char * message, bool bNewLine = true);

	void PrintCustom(const char* message, ConsoleTextColor color, bool bNewLine = true);
};