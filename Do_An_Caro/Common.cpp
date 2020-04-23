#include "Common.h"


void _Common::gotoXY(int pX, int pY) {
		COORD coord;
		coord.X = pX;
		coord.Y = pY;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void _Common::fixConsoleWindow() {
		HWND consoleWindow = GetConsoleWindow();
		LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
		style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
		SetWindowLong(consoleWindow, GWL_STYLE, style);
}
