#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;


class _Common {
public: 
	static void fixConsoleWindow();
	static void gotoXY(int, int);
};