#include "Board.h"

int _Board::getSize(){ 
	return _size; 
}

int _Board::getLeft(){ 
	return _left; 
}

int _Board::getTop(){ 
	return _top; 
}

int _Board::getXAt(int i, int j){
	return _pArr[i][j].getX();
}

int _Board::getYAt(int i, int j){
	return _pArr[i][j].getY();
}

int _Board::getCheckAt(int i, int j){
	return _pArr[i][j].getCheck();
}

_Board::_Board(int pSize, int pX, int pY){
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point*[pSize];
	for (int i = 0; i < pSize; i++) 
		_pArr[i] = new _Point[pSize];
}

_Board::~_Board(){
	for (int i = 0; i < _size; i++) 
		delete[] _pArr[i];
	delete[] _pArr;
}

void _Board::resetData() {
	if (_size == 0) 
		return; 
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			_pArr[i][j].setX(4 * j + _left + 2); 
			_pArr[i][j].setY(2 * i + _top + 1); 
			_pArr[i][j].setCheck(0);
		}
	}
}

void _Board::drawBoard(){
	if (_pArr == NULL) 
		return; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int i = 0; i <= _size; i++){
		for (int j = 0; j <= _size; j++){
			_Common::gotoXY(_left + 4 * i, _top + 2 * j);
			cout << "+---+";
			_Common::gotoXY(_left + 4 * i, _top + 2 * j + 1);
			if (j < _size)
				cout << "|";
			if (i == _size){
				_Common::gotoXY(_left + 4 * i + 4, _top + 2 * j + 1);
				if (j < _size)
					cout << "|";
			}
		}
	}
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());
}

int _Board::checkBoard(int pX, int pY, bool pTurn){
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0){
				if (pTurn)
					_pArr[i][j].setCheck(-1);
				else _pArr[i][j].setCheck(1);
					return _pArr[i][j].getCheck();
				}
			}
		}
	return 0;
}

int _Board::checkBoardMan(int pX, int pY){
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0){
				_pArr[i][j].setCheck(-1);
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

int _Board::setBoardCom(int pX, int pY){
	
	//Chuyen tu toa do console ve toa do ban co
	int Col = (pX - 2) / 4;
	int Row = (pY - 1) / 2;


	// Thu
	// Kiem tra xem so lan X ke nhau lon hon hoac bang 3 hoac lon nhat thi danh O tai vi tri lien ke
	// Kiem tra theo hang ngang so lan X ke nhau

	int check = 0;
	int maxCheck = 3;
	int temp = 0;
	
	for (int j = Col; j < _size; j++){
		if (_pArr[Row][j].getCheck() == -1){
			check++; 
		} 
		else {
			if (_pArr[Row][j].getCheck() == 0)
				temp = j;	
			break;
		}
			
	}

	for (int j = Col - 1; j >= 0; j--){
		if (_pArr[Row][j].getCheck() == -1){
			check++;
		}
		else {
			if (_pArr[Row][j].getCheck() == 0)
				temp = j;
			break;
		}
	}
	
	if (check >= 3){
		_pArr[Row][temp].setCheck(1);
		_Common::gotoXY(4 * temp + 2, 2 * Row + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
		return 1;
	}

	
	//Kiem tra theo hang doc so lan X ke nhau
	check = 0;
	temp = 0;
	for (int i = Row; i < _size; i++){
		if (_pArr[i][Col].getCheck() == -1){
				check++;
		}
		else {
			if (_pArr[i][Col].getCheck() == 0)
				temp = i;
			break;
		}
	}

	for (int i = Row - 1; i >= 0; i--){
		if (_pArr[i][Col].getCheck() == -1){
				check++;
		}
		else {
			if (_pArr[i][Col].getCheck() == 0)
				temp = i;
			break;
		}
	}

	if (check >= 3){
		_pArr[temp][Col].setCheck(1);
		_Common::gotoXY(4 * Col + 2, 2 * temp + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
		return 1;
	}

	//Kiem tra theo hang cheo tu trai sang phai
	check = 0;
	int X = 0;
	int Y = 0;

	for (int i = Row, j = Col; i >= 0 && j < _size; i--, j++){
		if (_pArr[i][j].getCheck() == -1){
			check++;
		}
		else {
			if (_pArr[i][j].getCheck() == 0){
				X = i;
				Y = j;
			}
			break;
		}
	}
	for (int i = Row + 1, j = Col - 1; i < _size && j >= 0; i++, j--){
		if (_pArr[i][j].getCheck() == -1){
			check++;
		}
		else {
			if (_pArr[i][j].getCheck() == 0){
				X = i;
				Y = j;
			}
			break;
		}
	}
	if (check >= 3){
		_pArr[X][Y].setCheck(1);
		_Common::gotoXY(4 * Y + 2, 2 * X + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
		return 1;
	}

	//Kiem tra theo hang cheo tu phai sang trai
	check = 0;
	X = 0;
	Y = 0;

	for (int i = Row, j = Col; i < _size && j < _size; i++, j++){
		if (_pArr[i][j].getCheck() == -1){
			check++;
		}
		else {
			if (_pArr[i][j].getCheck() == 0){
				X = i;
				Y = j;
			}
			break;
		}
	}
	for (int i = Row - 1, j = Col - 1; i >= 0 && j >= 0; i--, j--){
		if (_pArr[i][j].getCheck() == -1){
			check++;
		}
		else {
			if (_pArr[i][j].getCheck() == 0){
				X = i;
				Y = j;
			}
			break;
		}
	}

	if (check >= 3){
		_pArr[X][Y].setCheck(1);
		_Common::gotoXY(4 * Y + 2, 2 * X + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
		return 1;
	}

	// Neu chuong trinh chay den day thi chua co X nao lon hon 3. Ta se xet neu X nho hon 3
	int checkRowX = 0;
	int checkRowO = 0;
	maxCheck = 3;
	temp = 0;
	int temp1 = 0;
	for (int j = Col; j < _size; j++){
		if (_pArr[Row][j].getCheck() == -1){
			checkRowX++;
		}
		else {
			if (_pArr[Row][j].getCheck() == 0){
				temp = j;
				break;
			}
			for (int m = j; m < _size; m++){
				if (_pArr[Row][m].getCheck() == 1){
					checkRowO++;
				}
				else
				{
					if (_pArr[Row][j].getCheck() == 0){
						temp1 = m;
					}
					break;
				}
			}
			break;
		}
	}

	for (int j = Col - 1; j >= 0; j--){
		if (_pArr[Row][j].getCheck() == -1){
			checkRowX++;
		}
		else {
			if (_pArr[Row][j].getCheck() == 0){
				temp = j;
				break;
			}
			for (int m = j; m < _size; m++){
				if (_pArr[Row][m].getCheck() == 1){
					checkRowO++;
				}
				else
				{
					if (_pArr[Row][j].getCheck() == 0){
						temp1 = m;
					}
					break;
				}
			}
			break;
		}
	}

	if (checkRowX < 3){
		if (checkRowO >= 2){
			_pArr[Row][temp1].setCheck(1);
			_Common::gotoXY(4 * temp1 + 2, 2 * Row + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
			cout << "O";
			return 1;
		}
		_pArr[Row][temp].setCheck(1);
		_Common::gotoXY(4 * temp + 2, 2 * Row + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
		return 1;
	} 




}

int _Board::testBoard(int pX, int pY){
	//Chuyen tu toa do console sang toa do ban co
	int Col = (pX - 2) / 4;
	int Row = (pY - 1) / 2;

	if (_pArr[Row][Col].getCheck() == 0)
		return 2;

	// Kiem tra theo hang ngang
	int count = 0;
	// Kiem tra de chan 2 dau
	int check = 0;


	for (int j = Col; j < _size; j++){
		if (_pArr[Row][j].getCheck() != _pArr[Row][Col].getCheck())
		{
			if (_pArr[Row][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[Row][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
			{
				check++;
			}
			break;
		}
		else
			count++;
	}

	for (int j = Col - 1; j >= 0; j--){
		if (_pArr[Row][j].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[Row][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[Row][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1)){
				check++;
			}
			break;
		}
		else
			count++;
	}


	if (count >= 5 && check != 2) {
		if (_pArr[Row][Col].getCheck() == -1)
			return -1;
		else
			return 1;
	} 



	//Kiem tra theo cot
	count = 0;
	check = 0;
	for (int i = Row; i < _size; i++){
		if (_pArr[i][Col].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][Col].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][Col].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}

	for (int i = Row - 1; i >= 0; i--){
		if (_pArr[i][Col].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][Col].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][Col].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}

	if (count >= 5 && check != 2) {
		if (_pArr[Row][Col].getCheck() == -1)
			return -1;
		else
			return 1;
	}


	// Kiem tra theo hang cheo tu trai sang phai
	count = 0;
	check = 0;
	for (int i = Row, j = Col; i >= 0 && j < _size; i--, j++){
		if (_pArr[i][j].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}
	for (int i = Row + 1, j = Col - 1; i < _size && j >= 0; i++, j--){
		if (_pArr[i][j].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}

	if (count >= 5 && check != 2) {
		if (_pArr[Row][Col].getCheck() == -1)
			return -1;
		else
			return 1;
	}

	// Kiem tra theo hang cheo tu phai sang trai
	count = 0;
	check = 0;
	for (int i = Row, j = Col; i < _size && j < _size; i++, j++){
		if (_pArr[i][j].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}
	for (int i = Row - 1, j = Col - 1; i >= 0 && j >= 0; i--, j--){
		if (_pArr[i][j].getCheck() != _pArr[Row][Col].getCheck()){
			if (_pArr[i][j].getCheck() == 1 && _pArr[Row][Col].getCheck() == -1 || (_pArr[i][j].getCheck() == -1 && _pArr[Row][Col].getCheck() == 1))
				check++;
			break;
		}
		else count++;
	}

	if (count >= 5 && check != 2) {
		if (_pArr[Row][Col].getCheck() == -1)
			return -1;
		else
			return 1;
	}


	int countSize = 0;
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			countSize++;
			if (_pArr[i][j].getCheck() == 0)
				return 2;
		}
	}


	int area = _size*_size;
	if (countSize == area)
		return 0;

	return 2;
} 

void _Board::setCheckBoard(int i, int j, int check){
	_pArr[i][j].setCheck(check);
}

void _Board::loadBoard(int i, int j){
	if (_pArr[i][j].getCheck() == -1){
		_Common::gotoXY(_pArr[i][j].getX(), _pArr[i][j].getY());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
		cout << "X";
	}
	else if (_pArr[i][j].getCheck() == 1){
		_Common::gotoXY(_pArr[i][j].getX(), _pArr[i][j].getY());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3);
		cout << "O";
	}
}