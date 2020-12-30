#include "gadgets.h"

void go_to(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO cs;
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &cs);
	cs.dwCursorPosition.X = 4 * x;
	cs.dwCursorPosition.Y = 2 * y;
	SetConsoleCursorPosition(hConsoleOut, cs.dwCursorPosition);
}