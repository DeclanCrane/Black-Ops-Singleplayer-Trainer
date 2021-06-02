#include "Console.h"

void Console::ConsoleColors()
{
	// you can loop k higher to see more color choices
	for (int k = 1; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(consoleInfo.hConsole, k);
		std::cout << k << "Hello World!" << std::endl;
	}
	if (CloseHandle(consoleInfo.hConsole))
		std::cout << "Console closed!" << std::endl;
	else
		std::cout << "Console handle not closed!" << std::endl;
}

void Console::ResetConsoleColor()
{
	SetConsoleColor(ConsoleTextColor::white);
}

void Console::Print(LogType logType,  const char* message, bool bNewLine)
{
	if (logType == LogType::Plain)
	{
		SetConsoleColor(ConsoleTextColor::white);
		std::cout << message;

		ResetConsoleColor();
	}

	if (logType == LogType::Log)
	{
		SetConsoleColor(ConsoleTextColor::green);
		std::cout << "[LOG]: " << message;

		ResetConsoleColor();
	}

	if (logType == LogType::Warning)
	{
		SetConsoleColor(ConsoleTextColor::darkYellow);
		std::cout << "[WARNING]: " << message;

		ResetConsoleColor();
	}

	if (logType == LogType::Error)
	{
		SetConsoleColor(ConsoleTextColor::darkRed);
		std::cout << "[ERROR]: " << message;

		ResetConsoleColor();
	}

	// Creates new line if the parameter is set to true
	if (bNewLine)
	{
		std::cout << "\n";
	}
}

void Console::PrintCustom(const char* message, ConsoleTextColor color, bool bNewLine)
{
	SetConsoleColor(color);
	std::cout << message;

	ResetConsoleColor();


	if (bNewLine)
		std::cout << "\n";
}

Console::Console()
{
	if (CreateConsole())
	{
		// Gets handle to console
		consoleInfo.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
}

Console::~Console()
{
	CloseConsole();
}

bool Console::CreateConsole()
{
	if (!AllocConsole())
		return false;

	//Redirect stream to temp file
	freopen_s(&consoleInfo.fTemp, "CONOUT$", "w", stdout);

	return true;
}

void Console::CloseConsole()
{
	// Closes handle to console
	CloseHandle(consoleInfo.hConsole);

	if (consoleInfo.fTemp)
		fclose(consoleInfo.fTemp);

	FreeConsole();
}

void Console::SetConsoleColor(ConsoleTextColor color)
{
	SetConsoleTextAttribute(consoleInfo.hConsole, (WORD)color);
}
