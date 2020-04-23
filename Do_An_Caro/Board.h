#pragma once

#include <iostream>
#include "Point.h"
#include "Common.h"
using namespace std;

class _Board {
private:
	int _size;
	int _left, _top;
	_Point** _pArr;
public:
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	int getCheckAt(int, int);
	_Board(int, int, int);
	~_Board();
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int testBoard(int, int);
	void setCheckBoard(int, int, int);
	void loadBoard(int, int);
	int checkBoardMan(int, int);
	int setBoardCom(int, int);
};