#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "Board.h"
#include "Random.h"

using namespace std;

class _Game{
private:
	_Board* _b;
	bool _turn;
	int _x, _y;
	int _command;
	bool _loop;
	int _count1;
	int _count2;
	int _countWin1;
	int _countWin2;
	bool _checkPointer;
	bool _checkPlayWithMan;
public:
	_Game(int, int, int);
	~_Game();
	int getCommand();
	bool isContinue();
	char waitKeyBoard();
	char askContinue();
	void startGame();
	void exitGame();
	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void saveGame();
	bool getTurn();
	void loadGame();
	void makeEffectWin(int);
	void displayEffect();
	void displayMenu();
	void displayAbout();
	void moveMenuDown();
	void moveMenuUp();
	void playGame();
	void setXY(int, int);
	int getX();
	int getY();
	void setPointer();
	void setColorMenu(int);
	void deleteColorMenu(int);
	void nameGameXO();
	void settingGame();
	bool getCheckPlayWithMan();
	void playGameWithCom();
	void displaySetting();
	void setColorSetting(int);
	void deleteColorSetting(int);
	void setPointerSetting();
	bool processCheckBoardMan();
	int processFinishCom();
	void setCom();
	
};



