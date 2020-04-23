#pragma once

#include <iostream>
using namespace std;

class _Point{
private:
	int _x, _y, _check;
public:
	_Point();
	_Point(int, int);
	bool setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};