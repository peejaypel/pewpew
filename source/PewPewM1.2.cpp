//PewPew Mark1.2
//peejaygal

//NOTES: Beta version. Press W and D to navigate ship, press space to shoot.

#include <iostream>
#include <windows.h>
#include <sstream>
#include <ctime>
using namespace std;

int boardRow=15;
int boardCollumn=11;
char board[15][11];
int gunPosition=5;
int colorGlobal=63;
int windowSizeX=55;
int windowSizeY=30;
int points=0;
int enemyNextSpawnTimer;
int enemySpawnRate=20;

void goToRC(int r, int c);
void printBoard();
void getMove();
void resizeWindow();
void setColor(int value);
void artPewPew();
void generateEnemies();
bool shipIsAlive();

int main(){
	resizeWindow();
	artPewPew();
	srand((time(NULL)));
	cout << "\n=======================================================";
	board[14][5] = 'T';	goToRC(23,0); 
	cout << "=======================================================" << endl;
	cout << "Points: " << points;
	
	do{
	if (enemyNextSpawnTimer == enemySpawnRate) {
	enemyNextSpawnTimer=0;
	generateEnemies();	
	}
	getMove();
	printBoard();
	goToRC(24,0); cout << "Points: " << points;
	goToRC(25,0); cout << "                                       ";
	goToRC(25,0); cout << "EnemyNextSpawnTimer: " << enemyNextSpawnTimer;
	goToRC(26,0); cout << "EnemySpawnRate: " << enemySpawnRate;

	Sleep(50);		
	enemyNextSpawnTimer++;
	}while (shipIsAlive());


}

void goToRC (int r, int c){
    COORD coord; // coordinates
    coord.X = c; coord.Y = r; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printBoard(){
	int rowStart=8; int collumnStart=windowSizeX/2-((boardCollumn*2+2)/2);
	
	//Move bullets up
	for (int i=0; i<boardRow; i++){
		goToRC(rowStart, collumnStart);	cout << "|";
		
		for (int j=0; j<boardCollumn; j++){
		cout << board[i][j] << " ";
			if (board[i][j] == '!') {
				//If an enemy is destroyed, beep and add points.
				if (board[i-1][j] == '*'){
					Beep(750,100);
					points++;
				}					
				board[i-1][j] = '!';
				board[i][j] = ' ';
			} 
		}
		cout << "|";
		rowStart++;
		cout << endl;
	}

	//Move enemies down
	for (int i=boardRow-1; i>=0; i--){
		goToRC(rowStart, collumnStart);
		for (int j=0; j<boardCollumn; j++){
			if (board[i][j] == '*') {
				if ((i+1)==boardRow){
				board[i][j] = ' ';	
				} else {
				board[i+1][j] = '*';
				board[i][j] = ' ';						
				}
		
			}
		}
	}
	
}

void getMove(){
	if (GetAsyncKeyState('D') && GetAsyncKeyState(VK_SPACE)) {
		Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';
		if(gunPosition+1 <boardCollumn){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition+1]);
		gunPosition++;			
		}
	} 
	
	else if (GetAsyncKeyState('A') && GetAsyncKeyState(VK_SPACE)) {
		Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';
		if(gunPosition-1 >=0){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition-1]);
		gunPosition--;			
		}
	} else if (GetAsyncKeyState(VK_SPACE)) {
		Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';			
	} else if (GetAsyncKeyState('A')) {
		if(gunPosition-1 >=0){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition-1]);
		gunPosition--;			
		}
	} else if (GetAsyncKeyState('D')) {
		if(gunPosition+1 <boardCollumn){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition+1]);
		gunPosition++;			
		}
	} else if (GetAsyncKeyState('P')){
		board[0][1] = '*';
	}	
}

void resizeWindow(){
	//setColor(colorGlobal);
	stringstream screenSize;
	screenSize << "mode " << windowSizeX << "," << windowSizeY;
	system(screenSize.str().c_str());

}

void setColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

void artPewPew(){
	goToRC(0, windowSizeX/2-27); cout << " _______  _______  _     _  _______  _______  _     _ ";
	goToRC(1, windowSizeX/2-27); cout << "|       ||       || | _ | ||       ||       || | _ | |";
	goToRC(2, windowSizeX/2-27); cout << "|    _  ||    ___|| || || ||    _  ||    ___|| || || |";
	goToRC(3, windowSizeX/2-27); cout << "|    ___||    ___||       ||    ___||    ___||       |";
	goToRC(4, windowSizeX/2-27); cout << "|   |    |   |___ |   _   ||   |    |   |___ |   _   |";
	goToRC(5, windowSizeX/2-27); cout << "|   |    |   |___ |   _   ||   |    |   |___ |   _   |";
	goToRC(6, windowSizeX/2-27); cout << "|___|    |_______||__| |__||___|    |_______||__| |__|";

}

void generateEnemies(){
	int random;
	random = rand()%boardCollumn;
	
	board[0][random] = '*';
}

bool shipIsAlive(){
	for (int i=0; i<boardCollumn; i++){
		if (board[boardRow-1][i] == 'T'){
			return true;
		}
	}
	return false;
}
