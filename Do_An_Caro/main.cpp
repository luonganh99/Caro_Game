#include <iostream>

#include "Common.h"
#include "Board.h"
#include "Point.h"
#include "Game.h"

using namespace std;

const int BOARD_SIZE = 18;
const int LEFT = 0;
const int TOP = 0;



int main(){
	_Common::fixConsoleWindow();
	_Game g(BOARD_SIZE, LEFT, TOP); 
	// Ve 2 hinh X va O
	g.nameGameXO();
	// Hien thi MENU
	g.displayMenu();
	//check kiem tra dang o vi tri nao o MENU
	int check = 0;
	//Dua ve vi tri dang hien MENU
	g.setXY(52, 17);
	//cur kiem tra nguoi dung bam enter hay chua
	bool cur = true;
	while (cur){
		g.waitKeyBoard();
		switch (g.getCommand())
		{
		case 'S':
			if (check < 4)
			{
				g.moveMenuDown();
				//chinh con tro di xuong
				g.setPointer();
				check++;
				//chinh mau chu khi di len xuong
				g.deleteColorMenu(check);
				g.setColorMenu(check);
			}
			break;
		case 'W':
			if (check > 1){
				g.moveMenuUp();
				g.setPointer();
				check--; 
				g.deleteColorMenu(check);
				g.setColorMenu(check);
			}
			break;
		case 13:
			cur = false;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			if (check == 1)
			{
				g.settingGame();
				g.startGame();
				// hien thi bang ban dau
				g.displayEffect();
				if (g.getCheckPlayWithMan() == true)
					g.playGame();
				else
					g.playGameWithCom();
			
			}
			if (check == 2){
				g.settingGame();
				g.setXY(50, 27);
				g.loadGame();
				if (g.getCheckPlayWithMan() == true)
					g.playGame();
				else
					g.playGameWithCom();
			}
			if (check == 3){
				system("cls");
				g.displayAbout();
				g.waitKeyBoard();
				if (g.getCommand()  == 'B')
				{
					system("cls");
					g.nameGameXO();
					g.displayMenu();
					check = 0;
					g.setXY(52, 17);
					cur = true;
				}
				break;
			}
			if (check == 4){
				system("cls");
			}
			break;
		case 27:
			cur = false;
			system("cls");
			break;
		default:
			break;
		}
	}
	
	return 0;
}