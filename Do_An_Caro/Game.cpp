#include "Game.h"
#include "conio.h"
#include "time.h"

_Game::_Game(int pSize, int pLeft, int pTop){
	_b = new _Board(pSize, pLeft, pTop);		
	_loop = _turn = true;
	_command = -1;
	_x = pLeft; _y = pTop;
	_count1 = 0;
	_count2 = 0;
	_countWin1 = 0;
	_countWin2 = 0;
	_checkPlayWithMan = true;
}

_Game::~_Game(){ 
	delete _b; 
}

int _Game::getCommand(){ 
	return _command; 
}

bool _Game::isContinue(){ 
	return _loop; 
}

char _Game::waitKeyBoard(){
	_command = toupper(_getch());
	return _command;
}

char _Game::askContinue(){
	_Common::gotoXY(92,24);
	cout << "Press Y to continue";
	_Common::gotoXY(92, 25);
	cout << "Press Esc to exit";
	return waitKeyBoard();
}

void _Game::startGame(){
	system("cls");
	_b->resetData();
	_b->drawBoard(); 
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
	_count1 = 0;
	_count2 = 0;
	displayEffect();
}

void _Game::exitGame() {
	system("cls");
	_loop = false;
}

bool _Game::processCheckBoard() {
	switch (_b->checkBoard(_x, _y, _turn)){
		case -1:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
			cout << "X";
			_count1++;
			break;
		case 1:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
			cout << "0";
			_count2++;
			break;
		case 0: 
			return false; 
	}
	return true;
}

int _Game::processFinish() {
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard(_x,_y);
	switch (pWhoWin){
	case -1:
		makeEffectWin(pWhoWin);
		_countWin1++;
		break;
	case 1:
		makeEffectWin(pWhoWin);
		_countWin2++;
		break;
	case 0:
		makeEffectWin(pWhoWin);
		break;
	case 2:
		_turn = !_turn; 
	}
	_Common::gotoXY(_x, _y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // lam lai mau trang
	return pWhoWin;
}

void _Game::moveRight() {
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)){
		_x += 4;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0)) {
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveDown() {
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)){
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveUp() {
	if (_y > _b->getYAt(0, 0)) {
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::saveGame(){
	char str[100];
	_Common::gotoXY(_x, _y);
	cout << "Input file to save game: ";
	cin.getline(str, 100);

	ofstream outFile;
	outFile.open(str);

	for (int i = 0; i < _b->getSize(); i++){
		for (int j = 0; j < _b->getSize(); j++)
			outFile << _b->getCheckAt(i, j) << " ";
	}
	
	outFile << _count1 << " " << _count2 << " " << _countWin1 <<" "<< _countWin2 << " " << _turn;

	if (!outFile.eof())
		cout << "File da duoc save thanh cong!" << endl;

	outFile.close();
}

bool _Game::getTurn(){
	return _turn;
}

void _Game::loadGame(){
	ifstream inFile;
	
	do{
		char str[100];
		_Common::gotoXY(_x, _y);
		cout << "Open save game file: ";
		cin.getline(str, 100);

		inFile.open(str);

		if (inFile.fail()){
			_Common::gotoXY(_x, _y + 1);
			cout << "Can not open file, please try again!";
		}
			
	} while (inFile.fail());

	string temp;
	int check;
 
	int sum = 0;
	startGame();
	for (int i = 0; i < _b->getSize(); i++){
		for (int j = 0; j < _b->getSize(); j++){
			inFile >> check;
			_b->setCheckBoard(i, j, check);
			_b->loadBoard(i, j);
			sum += check; //dung de tinh luot di truoc khi save la X hay O
		}
	}

	int count;
	inFile >> count;
	_count1 = count;
	inFile >> count;
	_count2 = count;
	inFile >> count;
	_countWin1 = count;
	inFile >> count;
	_countWin2 = count;

	if (sum == -1){
		_turn = false;
	}
	inFile.close();
	displayEffect();
}

void _Game::makeEffectWin(int pWhoWin){

	const int X_FIRST_UP = 90;
	const int Y_FIRST_DOWN = 3;

	const int X_SECOND_UP = 90;
	const int Y_SECOND_DOWN = 29;
	
	int X = 87;
	int Y = 12;

	string str;
	if (pWhoWin == -1)
		str = "PLAYER 1 WIN !";
	else if (pWhoWin == 1)
		str = "PLAYER 2 WIN !";
	else if (pWhoWin == 0)
		str = "PLAYER 1 DRAW PLAYER 2";
	if (str != " ") {
		int n = str.length();
		bool turn = true; //turn = true: tu trai sang phai, turn = false: tu phai sang trai
		int count = 0;
		Random* random1 = new Random();
		Random* random2 = new Random();
		while (true) {
			int color = random1->Next(15) + 1;
			//In chu Win lon va chinh mau hang thang
			if (pWhoWin == -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);			
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN);
				cout << "__   __   __  _   __   _ ";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 1);
				cout << "\\ \\ /  \\ / / | | |  \\ | |";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 2);
				cout << " \\ / /\\ \\ /  | | | | \\| |";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 3);
				cout << "  \\_/  \\_/   |_| |_|\\___|";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 4);
				cout << "                            ";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN);
				cout << " _     _____  ____   ____ ";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 1);
				cout << "| |   |  _  ||  __| |  __|";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 2);
				cout << "| |__ | |_| ||  \\_  | -__ ";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 3);
				cout << "|____||_____||____| |____|";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 4);
				cout << "                            ";
			}
			else if (pWhoWin == 1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN);
				cout << "__   __   __  _   __   _ ";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 1);
				cout << "\\ \\ /  \\ / / | | |  \\ | |";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 2);
				cout << " \\ / /\\ \\ /  | | | | \\| |";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 3);
				cout << "  \\_/  \\_/   |_| |_|\\___|";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 4);
				cout << "                            ";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN);
				cout << " _     _____  ____   ____ ";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 1);
				cout << "| |   |  _  ||  __| |  __|";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 2);
				cout << "| |__ | |_| ||  \\_  | -__ ";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 3);
				cout << "|____||_____||____| |____|";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 4);
				cout << "                            ";
			}
			else if (pWhoWin == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN);
				cout << " ____  ____    _  __  __  __";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 1);
				cout << "|  _ ||   O|  / \\ \\ \\/  \\/ /";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 2);
				cout << "| |  || |  | / - \\ \\  /\\  / ";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 3);
				cout << "|____||_|\\_|/_/ \\_\\ \\____/  ";
				_Common::gotoXY(X_FIRST_UP, Y_FIRST_DOWN + 4);
				cout << "                            ";

				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN);
				cout << " ____  ____    _  __  __  __";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 1);
				cout << "|  _ ||   O|  / \\ \\ \\/  \\/ /";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 2);
				cout << "| |  || |  | / - \\ \\  /\\  / ";
				_Common::gotoXY(X_SECOND_UP, Y_SECOND_DOWN + 3);
				cout << "|____||_|\\_|/_/ \\_\\ \\____/  ";

			}
		


			//Chay chu nguoi choi thang
			color = random2->Next(15) + 1;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			if (turn == true){
				_Common::gotoXY(X - 1, Y);
				cout << " ";
			}

			if (turn == false) {
				_Common::gotoXY(X + n, Y);
				cout << " ";
			}

			_Common::gotoXY(X, Y);
			cout << str;

			if (X <= 86){
				turn = true;
			}
			else if (X >= 99){
				turn = false;
			}			 

			if (turn == true){
				X++;
			}
			else if (turn == false){
				X--;
			}
			Sleep(400);

			count++;
			if (count == 34)
				break;
		}
		delete random1;
		delete random2;
	}

}

void _Game::displayEffect(){
	const int X = 83;
	const int Y = 12;
	const int COLOR_PLAYER_1 = 12;
	const int COLOR_PLAYER_2 = 3;
	const int X_LINE_UP = 79;
	const int Y_LINE_UP = 0;
	const int X_LINE_DOWN = 79;
	const int Y_LINE_DOWN = 26;
	// Cai dat hinh vuong tren
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	_Common::gotoXY(X_LINE_UP,Y_LINE_UP);
	int i;
	int j;
	for (i = Y_LINE_UP; i <= 10; i++){
		for (j = X_LINE_UP; j <= 125; j++){
			if (i == Y_LINE_UP || i == Y_LINE_UP +1 || i == 9 || i == 10 || j == X_LINE_UP || j==X_LINE_UP+1 ||j == 125 || j == 124){
				if (j % 2 != 0 || j== X_LINE_UP){
					cout << "*";
				}
				else
					cout << " ";
			}
			else
				cout << " ";
		}
		_Common::gotoXY(X_LINE_UP,i+1);
	}

	//Cai dat hinh vuong duoi
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	_Common::gotoXY(X_LINE_DOWN, Y_LINE_DOWN);
	for (i = Y_LINE_DOWN; i <= 36; i++){
		for (j = X_LINE_DOWN; j <= 125; j++){
			if (i == Y_LINE_DOWN || i == Y_LINE_DOWN + 1 || i == 36 || i == 35 || j == X_LINE_DOWN || j == 125 || j == X_LINE_DOWN + 1 || j == 124){
				if (j % 2 != 0 || j == X_LINE_DOWN){
					cout << "*";
				}
				else
					cout << " ";
			}
			else
				cout << " ";
		}
		_Common::gotoXY(X_LINE_DOWN, i + 1);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PLAYER_1);
	_Common::gotoXY(97, 3);
	cout << "Player 1";
	_Common::gotoXY(97, 5);
	cout << "Won: " << _countWin1;;
	_Common::gotoXY(97, 7);
	cout << "Turn: " << _count1;

	_Common::gotoXY(X, Y + 2);
	cout << "___     ___";
	_Common::gotoXY(X, Y + 3);
	cout << "\\  \\   /  /";
	_Common::gotoXY(X, Y + 4);
	cout << " \\  \\_/  /  ";
	_Common::gotoXY(X, Y + 5);
	cout << "  \\     /    ";
	_Common::gotoXY(X, Y + 6);
	cout << "   \\   /     ";
	_Common::gotoXY(X, Y + 7);
	cout << "   /   \\     ";
	_Common::gotoXY(X, Y + 8);
	cout << "  /  _  \\    ";
	_Common::gotoXY(X, Y + 9);
	cout << " /  / \\  \\  ";
	_Common::gotoXY(X, Y + 10);
	cout << "/__/   \\__\\ ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	_Common::gotoXY(X + 1, Y + 1);
	cout << "NEXT TURN";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	_Common::gotoXY(X+20, Y+1);
	cout << "HOW TO PLAY";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	_Common::gotoXY(X+20, Y+3);
	cout << "W: Move Up";
	_Common::gotoXY(X+20, Y+4);
	cout << "S: Move Down";
	_Common::gotoXY(X+20, Y+5);
	cout << "D: Move Right";
	_Common::gotoXY(X+20, Y+6);
	cout << "A: Move Left";
	_Common::gotoXY(X+20, Y+7);
	cout << "L: Save Game";
	_Common::gotoXY(X+20, Y+8);
	cout << "T: Load Game";
	_Common::gotoXY(X+20, Y + 9);
	cout << "Enter: Put X/O";
	_Common::gotoXY(X+20, Y + 10);
	cout << "Esc: Exit Game";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_Common::gotoXY(97, 29);
	cout << "Player 2";
	_Common::gotoXY(97, 31);
	cout << "Won: " << _countWin2;
	_Common::gotoXY(97, 33);
	cout << "Turn: " << _count2;

	if (_turn == false){
		if (_count2 != 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			_Common::gotoXY(97, 3);
			cout << "Player 1";
			_Common::gotoXY(97, 5);
			cout << "Won: " << _countWin1;;
			_Common::gotoXY(97, 7);
			cout << "Turn: " << _count1;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PLAYER_1);
			_Common::gotoXY(X, Y + 2);
			cout << "___     ___"  ;
			_Common::gotoXY(X, Y + 3);
			cout << "\\  \\   /  / ";
			_Common::gotoXY(X, Y + 4);
			cout << " \\  \\_/  /  ";
			_Common::gotoXY(X, Y + 5);
			cout << "  \\     /    ";
			_Common::gotoXY(X, Y + 6);
			cout << "   \\   /     ";
			_Common::gotoXY(X, Y + 7);
			cout << "   /   \\     ";
			_Common::gotoXY(X, Y + 8);
			cout << "  /  _  \\    ";
			_Common::gotoXY(X, Y + 9);
			cout << " /  / \\  \\  ";
			_Common::gotoXY(X, Y + 10);
			cout << "/__/   \\__\\";


			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PLAYER_2);
			_Common::gotoXY(97, 29);
			cout << "Player 2";
			_Common::gotoXY(97, 31);
			cout << "Won: " << _countWin2;
			_Common::gotoXY(97, 33);
			cout << "Turn: " << _count2;
			
		}
	}
	else{
		if (_count1 != 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PLAYER_1);
			_Common::gotoXY(97, 3);
			cout << "Player 1";
			_Common::gotoXY(97, 5);
			cout << "Won: " << _countWin1;;
			_Common::gotoXY(97, 7);
			cout << "Turn: " << _count1;


			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			_Common::gotoXY(97, 29);
			cout << "Player 2";
			_Common::gotoXY(97, 31);
			cout << "Won: " << _countWin2;
			_Common::gotoXY(97, 33);
			cout << "Turn: " << _count2;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PLAYER_2);
			_Common::gotoXY(X, Y + 2);
			cout << "  ________  ";
			_Common::gotoXY(X, Y + 3);
			cout << " /  ____  \\ ";
			_Common::gotoXY(X, Y + 4);
			cout << "|  |    |  |";
			_Common::gotoXY(X, Y + 5);
			cout << "|  |    |  |";
			_Common::gotoXY(X, Y + 6);
			cout << "|  |    |  |";
			_Common::gotoXY(X, Y + 7);
			cout << "|  |    |  |";
			_Common::gotoXY(X, Y + 8);
			cout << "|  |    |  |";
			_Common::gotoXY(X, Y + 9);
			cout << "|  |____|  |";
			_Common::gotoXY(X, Y + 10);
			cout << " \\________/";
		}
	}


}

void _Game::setXY(int x, int y){
	_x = x;
	_y = y;
}

int _Game::getX(){
	return _x;
}

int _Game::getY(){
	return _y;
}

void _Game::moveMenuDown(){
	_y = _y + 1;
	_Common::gotoXY(15, _y);
	_checkPointer = true;
}

void _Game::moveMenuUp(){
	_y = _y - 1;
	_Common::gotoXY(15, _y);
	_checkPointer = false;
}

void _Game::playGame(){
	while (isContinue()){
		waitKeyBoard();
		if (getCommand() == 27){
			setXY(85, 24);
			saveGame();
			exitGame();
		}
		else {
			switch (getCommand()){
			case 'A':
				moveLeft();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			case 'D':
				moveRight();
				break;
			case 'L':
				setXY(85, 24);
				saveGame();
				exitGame();
				break;
			case 'T':
				setXY(85, 24);
				loadGame();
				break;
			case 13:
				if (processCheckBoard()){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
					displayEffect();
					switch (processFinish()){
					case -1: case 1: case 0:
						if (askContinue() != 'Y')
							exitGame();
						else startGame();
					}
				}
			}
		}
	}
}

void _Game::displayMenu(){
	const int X = 57;
	const int Y = 17;
	const int X_MENU = 50;
	const int Y_MENU = 13;
	_Common::gotoXY(X_MENU , Y_MENU);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9);
	cout << "  _____   ___  ____   _  _";
	_Common::gotoXY(X_MENU, Y_MENU+1);
	cout << " |     | | _  |    | | || |";
	_Common::gotoXY(X_MENU, Y_MENU+2);
	cout << " |_|_|_| |___ |_||_| |____|";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);

	_Common::gotoXY(X, Y+1);
	cout << "1. New Game" << endl;
	_Common::gotoXY(X, Y+2);
	cout << "2. Load Game" << endl;
	_Common::gotoXY(X, Y+3);
	cout << "3. About" << endl;
	_Common::gotoXY(X, Y+4);
	cout << "4. Exit" << endl;
	

	int X_LINE = 36;
	int Y_LINE = 29;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
	_Common::gotoXY(X_LINE, Y_LINE);
	for (int i = Y_LINE; i < 37 ; i++){
		for (int j = X_LINE; j < 66; j++){
			if (i == 29 || i ==  36 || j == 36 || j == 65)
				cout << "*";
			else
				cout << " ";
			cout << " ";
		}
		_Common::gotoXY(X_LINE, i + 1);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
	_Common::gotoXY(X_LINE + 23, Y_LINE + 1);
	cout << "HOW TO PLAY";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(X_LINE + 4, Y_LINE + 2);
	cout << "W: Move Up";
	_Common::gotoXY(X_LINE + 17, Y_LINE + 2);
	cout << "S: Move Down";
	_Common::gotoXY(X_LINE + 32, Y_LINE + 2);
	cout << "B: Back";
	_Common::gotoXY(X_LINE + 42, Y_LINE + 2);
	cout << "Enter: Choose";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
	_Common::gotoXY(X_LINE + 25, Y_LINE + 3);
	cout << "NOTICE";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(X_LINE + 2, Y_LINE + 4);
	cout << "If you can not play game, try to adjust setting: Click";

	_Common::gotoXY(X_LINE + 2, Y_LINE + 5);
	cout << "right on top left conner -> choose Properties, set in";

	_Common::gotoXY(X_LINE + 2, Y_LINE + 6);
	cout << "Window Size Width = 128, Height = 38 and restart game";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(50,1);
	cout << "HO CHI MINH UNIVERSITY OF SCIENCE";
	_Common::gotoXY(60,2);
	cout << "FIT - K2017";

	_Common::gotoXY(X, Y);
	
}

void _Game::displayAbout(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(50, 1);
	cout << "HO CHI MINH UNIVERSITY OF SCIENCE";
	_Common::gotoXY(60, 2);
	cout << "FIT - K2017";


	int X_LINE = 36;
	int Y_LINE = 5;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
	_Common::gotoXY(X_LINE, Y_LINE);
	for (int i = Y_LINE; i < 36; i++){
		for (int j = X_LINE; j < 67; j++){
			if (i == 5 || i == 35 || j == 36 || j == 66)
				cout << "*";
			else
				cout << " ";
			cout << " ";
		}
		_Common::gotoXY(X_LINE, i + 1);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(X_LINE + 27 , Y_LINE + 2);
	cout << "ABOUT";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
	_Common::gotoXY(X_LINE + 16, Y_LINE + 4);
	cout << "Author: Nguyen Huu Luong Anh";

	_Common::gotoXY(X_LINE + 16, Y_LINE + 6);
	cout << "Class: 17CTT2";

	_Common::gotoXY(X_LINE + 16, Y_LINE + 8);
	cout << "Student Number: 1712277";

	_Common::gotoXY(X_LINE + 4, Y_LINE + 11);
	cout << "This game is created for final project of OPP practise";

	_Common::gotoXY(X_LINE + 4, Y_LINE + 13);
	cout << "object. In Computer Mode, it's still not perfect. The";

	_Common::gotoXY(X_LINE + 4, Y_LINE + 15);
	cout << "computer only defense your move, so it's quite stupid.";

	_Common::gotoXY(X_LINE + 4, Y_LINE + 17);
	cout << "If you find any errors, please contact me. Thanks for";

	_Common::gotoXY(X_LINE + 4, Y_LINE + 19);
	cout << "playing my game. :)";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);

	_Common::gotoXY(X_LINE + 27, Y_LINE + 22);
	cout << "CONTACT";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
	_Common::gotoXY(X_LINE + 3, Y_LINE + 24);
	cout << "Phone: 0933925482";

	_Common::gotoXY(X_LINE + 23, Y_LINE + 24);
	cout << "Facebook:fb.com/luonganh.nguyenhuu.1";


	_Common::gotoXY(X_LINE + 22, Y_LINE + 27);
	cout << "Copyrights 2018 - 204A18,A.Dormitory ";

	_Common::gotoXY(X_LINE + 30, Y_LINE + 28);
	cout << "All Rights Reserved";
}

void _Game::setPointer(){
	if (_checkPointer == true){
		_Common::gotoXY(_x, _y - 1);
		cout << "  ";
		_Common::gotoXY(_x, _y);
		cout << "->";
		_Common::gotoXY(_x + 5, _y);
	}
	else
	{
		_Common::gotoXY(_x, _y + 1);
		cout << "  ";
		_Common::gotoXY(_x, _y);
		cout << "->";
		_Common::gotoXY(_x + 5, _y);
	}
}

void _Game::setColorMenu(int check){
	const int COLOR = 8;
	switch (check)
	{
	case 1:
		_Common::gotoXY(_x + 5, _y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "1. New Game";
		break;
	case 2:
		_Common::gotoXY(_x + 5, _y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "2. Load Game";
		break;
	case 3:
		_Common::gotoXY(_x + 5, _y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "3. About";
		break;
	case 4:
		_Common::gotoXY(_x + 5, _y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "4. Exit";
		break;
	default:
		break;
	}
}

void _Game::deleteColorMenu(int check){
	if (_checkPointer == true){
		switch (check)
		{
		case 2:
			_Common::gotoXY(_x + 5, _y - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "1. New Game";
			break;
		case 3:
			_Common::gotoXY(_x + 5, _y - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "2. Load Game";
			break;
		case 4:
			_Common::gotoXY(_x + 5, _y - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "3. About";
			break;
			
		default:
			break;
		}
	}
	else
	{
		switch (check)
		{
		case 1:
			_Common::gotoXY(_x + 5, _y + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "2. Load Game";
			break;
		case 2:
			_Common::gotoXY(_x + 5, _y + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "3. About";
			break;
		case 3:
			_Common::gotoXY(_x + 5, _y + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "4. Exit";
			break;
		default:
			break;
		}
	}
}

void _Game::nameGameXO(){
	const int X = 13;
	const int Y = 5;
	
	const int X_SHAPE_X = 13;
	const int Y_SHAPE_X = 15;

	const int X_SHAPE_O = 95;
	const int Y_SHAPE_O = 15;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x6);

	_Common::gotoXY(X, Y);
	cout << " ____________  __    _______     ____________    ___       _______    ____________   ________   ________ ";
	_Common::gotoXY(X, Y + 1);
	cout << "|_____  _____||  |  /  _____|   |_____  _____|  / _ \\     /  _____|  |_____  _____| /   __   \\ |   _____|      ";
	_Common::gotoXY(X, Y + 2);
	cout << "     |  |     |  | |  |              |  |      / / \\ \\   |  |             |  |     |   /  \\   ||  |__    ";
	_Common::gotoXY(X, Y + 3);
	cout << "     |  |     |  | |  |              |  |     /  ___  \\  |  |             |  |     |  |    |  ||   __| ";
	_Common::gotoXY(X, Y + 4);
	cout << "     |  |     |  | |  |_____         |  |    /  /   \\  \\ |  |_____        |  |     |   \\__/   ||  |_____      ";
	_Common::gotoXY(X, Y + 5);
	cout << "     |__|     |__|  \\_______|        |__|   /__/     \\__\\ \\_______|       |__|      \\________/ |________|";
	

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
	_Common::gotoXY(X_SHAPE_X,Y_SHAPE_X);
	cout << " ______        ______ ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X +1);
	cout << " \\     \\      /     /";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 2);
	cout << "  \\     \\    /     /";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 3);
	cout << "   \\     \\  /     /   ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 4);
	cout << "    \\     \\/     /    ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 5);
	cout << "     \\          /     ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 6);
	cout << "      \\        /      ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 7);
	cout << "       \\      /       ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 8);
	cout << "       /      \\       ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 9);
	cout << "      /        \\      ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 10);
	cout << "     /          \\     ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 11);
	cout << "    /     /\\     \\    ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 12);
	cout << "   /     /  \\     \\   ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 13);
	cout << "  /     /    \\     \\  ";
	_Common::gotoXY(X_SHAPE_X, Y_SHAPE_X + 14);
	cout << " /_____/      \\_____\\  ";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O);
	cout << "   ______________   ";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 1);
	cout << "  /              \\  ";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 2);
	cout << " /     ______     \\ ";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 3);
	cout << "|     /      \\     |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 4);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 5);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 6);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 7);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 8);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 9);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 10);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 11);
	cout << "|    |        |    |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 12);
	cout << "|     \\______/     |";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 13);
	cout << " \\                / ";
	_Common::gotoXY(X_SHAPE_O, Y_SHAPE_O + 14);
	cout << "  \\______________/  ";



	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
}

void _Game::settingGame(){
	displaySetting();
	bool cur = true;
	int check = 0;
	while (cur) {
		waitKeyBoard();
		switch (getCommand())
		{
		case 'W':
			if (check > 1)
			{
				moveMenuUp();
				setPointerSetting();
				check--;
				deleteColorSetting(check);
				setColorSetting(check);
			}
			break;
		case 'S':
			if (check < 2)
			{
				moveMenuDown();
				setPointerSetting();
				check++;
				deleteColorSetting(check);
				setColorSetting(check);
			}
			break;
		case 13:
			cur = false;
			if (check == 1)
				_checkPlayWithMan = true;
			if (check == 2)
				_checkPlayWithMan = false;
			break;
		case 27:
			cur = false;
			system("cls");
			break;
		default:
			break;
		}
	}
}

bool _Game::getCheckPlayWithMan(){
	return _checkPlayWithMan;
}

void _Game::setColorSetting(int check){
	const int COLOR = 8;
	switch (check)
	{
	case 1:
		_Common::gotoXY(_x + 4, _y + 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "Play with Man";
		break;
	case 2:
		_Common::gotoXY(_x + 4, _y + 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
		cout << "Play with Com";
		break;
	default:
		break;
	}
}

void _Game::deleteColorSetting(int check){
	if (_checkPointer == true){
		switch (check)
		{
		case 2:
			_Common::gotoXY(_x + 4, _y + 4 - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "Play with Man";
			break;
		default:
			break;
		}
	}
	else
	{
		switch (check)
		{
		case 1:
			_Common::gotoXY(_x + 4, _y + 4 + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "Play with Com";
			break;
		default:
			break;
		}
	}

}

void _Game::displaySetting(){
	_Common::gotoXY(_x + 4, _y + 5);
	cout << "Play with Man";
	_Common::gotoXY(_x + 4, _y + 6);
	cout << "Play with Com";
	_Common::gotoXY(_x + 3, _y + 4);
}

void _Game::setPointerSetting(){
	if (_checkPointer == true){
		_Common::gotoXY(_x, _y + 4 - 1);
		cout << "  ";
		_Common::gotoXY(_x, _y + 4);
		cout << "->";
		_Common::gotoXY(_x + 3, _y + 4);
	}
	else
	{
		_Common::gotoXY(_x, _y + 4 + 1);
		cout << "  ";
		_Common::gotoXY(_x, _y + 4);
		cout << "->";
		_Common::gotoXY(_x + 3, _y + 4);
	}
}

void _Game::setCom() {
	switch (_b->setBoardCom(_x, _y))
	{
	case 1 : case 0: 
		_count2++;
		_turn = false;
		break;

	default:
		break;
	}
}

bool _Game::processCheckBoardMan(){
	switch (_b->checkBoardMan(_x, _y)){
	case -1:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
		cout << "X";
		_count1++;
		break;
	case 0:
		return false;
	}
	return true;
}

void _Game::playGameWithCom(){
	while (isContinue()){
		waitKeyBoard();
		if (getCommand() == 27){
			setXY(85, 24);
			saveGame();
			exitGame();
		}
		else {
			switch (getCommand()){
			case 'A':
				moveLeft();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			case 'D':
				moveRight();
				break;
			case 'L':
				setXY(85, 24);
				saveGame();
				exitGame();
				break;
			case 'T':
				setXY(85, 24);
				loadGame();
				break;
			case 13:
				if (processCheckBoard()){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
					displayEffect();
					switch (processFinish()){
					case -1: case 1: case 0:
						if (askContinue() != 'Y')
							exitGame();
						else startGame();
					case 2:
						setCom();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
						displayEffect();
						switch (processFinish()){
						case -1: case 1: case 0:
							if (askContinue() != 'Y')
								exitGame();
							else startGame();
						case 2:
							_turn = true;
						}
					}
				}
			}
		}
	}
}



