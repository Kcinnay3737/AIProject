#include "Logger/ConsoleLogger.h"
#include <windows.h>
#include <stdio.h>
#include <consoleapi.h>
#include <iostream>

using namespace NPEngine;

bool ConsoleLogger::Initialize(const Param& Params)
{
	AllocConsole();

	int R = freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

	_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	return true;
}

void ConsoleLogger::Shutdown(const Param& Params)
{
	FreeConsole();
}

void ConsoleLogger::LogMessage(const char* Message, ...)
{
	va_list Args;
	va_start(Args, Message);
	vprintf(Message, Args);
	va_end(Args);
	printf("\n");
}

void ConsoleLogger::SetTextColor(EColor ForegourndColor, EColor BackgroundColor)
{
	SetConsoleTextAttribute(_HConsole, MapToForegroundColor(ForegourndColor) | MapToBackgroundColor(BackgroundColor));
}

uint8_t ConsoleLogger::MapToForegroundColor(EColor Color)
{
	switch (Color)
	{
	case EColor::Black: return 0;
	case EColor::Blue: return FOREGROUND_BLUE;
	case EColor::Brown: return FOREGROUND_RED | FOREGROUND_GREEN;
	case EColor::Cyan: return FOREGROUND_GREEN | FOREGROUND_BLUE;
	case EColor::Green: return FOREGROUND_GREEN;
	case EColor::Grey: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	case EColor::Magenta: return FOREGROUND_RED | FOREGROUND_BLUE;
	case EColor::Orange: return FOREGROUND_RED | FOREGROUND_GREEN;
	case EColor::Purple: return FOREGROUND_RED | FOREGROUND_BLUE;
	case EColor::Red: return FOREGROUND_RED;
	case EColor::White: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	case EColor::Yellow: return FOREGROUND_RED | FOREGROUND_GREEN;
	default: return 0;
	}
}

uint8_t ConsoleLogger::MapToBackgroundColor(EColor Color)
{
	switch (Color)
	{
	case EColor::Black: return 0;
	case EColor::Blue: return BACKGROUND_BLUE;
	case EColor::Brown: return BACKGROUND_RED | BACKGROUND_GREEN;
	case EColor::Cyan: return BACKGROUND_GREEN | BACKGROUND_BLUE;
	case EColor::Green: return BACKGROUND_GREEN;
	case EColor::Grey: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	case EColor::Magenta: return BACKGROUND_RED | BACKGROUND_BLUE;
	case EColor::Orange: return BACKGROUND_RED | BACKGROUND_GREEN;
	case EColor::Purple: return BACKGROUND_RED | BACKGROUND_BLUE;
	case EColor::Red: return BACKGROUND_RED;
	case EColor::White: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	case EColor::Yellow: return BACKGROUND_RED | BACKGROUND_GREEN;
	default: return 0;
	}
}