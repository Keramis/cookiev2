#include "includes.h"

void waitForEscButton()
{
	//while (!GetAsyncKeyState(VK_ESCAPE))
	//{
	//	Sleep(150);
	//}
	char a{};
	while (a != 27)
	{
		a = _getch();
		Sleep(150);
	}
}

void setConsoleNonResizable()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

bool wasKeyJustPressed(int key)
{
	if (GetAsyncKeyState(key))
	{
		while (GetAsyncKeyState(key))
		{
			Sleep(10);
		}
		return true;
	}
	return false;
}

std::string dead_spaces(150, ' ');
void printAtCoords(std::string text, SHORT x, SHORT y, bool clearLine)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	if (clearLine) { std::cout << dead_spaces; }
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << text;
}

void clearConsole()
{
	for (int i = 0; i < 100; ++i)
	{
		printAtCoords(" ", 0, i, true);
	}
	COORD startCoord = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), startCoord);
}

void setConsoleTitleString(std::string input)
{
	auto cstr = input.c_str();
	SetConsoleTitleA(cstr);
}