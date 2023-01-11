//PewPew Mark1.3
//peejaygal

//NOTES: Beta version. Press W and D to navigate ship, press space to shoot.

#include <iostream>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <conio.h>
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
int refreshRate(25); //Refresh rate of the game, lower number means faster gameplay
char resp; 

void goToRC(int r, int c);
void printBattlefield();
void getMove();
void resizeWindow();
void setColor(int value);
void artPewPew();
void artYouDied();
void generateEnemies();
bool shipIsAlive();
void resetBattlefield();
void panelTryAgain();

int main(){
	
	do{
		
		resizeWindow(); artPewPew(); srand((time(NULL))); resetBattlefield();
		cout << "\n=======================================================";
		board[14][5] = 'T';	gunPosition=5; goToRC(23,0); 
		cout << "=======================================================" << endl;
		cout << "Points: " << points;
		
		do{
		if (enemyNextSpawnTimer == enemySpawnRate) {
		enemyNextSpawnTimer=0;
		generateEnemies();	
		}
		getMove();
		printBattlefield();
		goToRC(24,0); cout << "Points: " << points;
		goToRC(25,0); cout << "                                       ";
		goToRC(25,0); cout << "EnemyNextSpawnTimer: " << enemyNextSpawnTimer;
		goToRC(26,0); cout << "EnemySpawnRate: " << enemySpawnRate;
	
		Sleep(refreshRate);	 	
		enemyNextSpawnTimer++;
		}while (shipIsAlive());	
		
		//Prompt for Try Again
		artYouDied();
		panelTryAgain();
		do{
		resp = getch();
		}while(!(resp=='Y' || resp=='y' || resp=='N' || resp=='n'));
		
	}while(resp=='Y' || resp=='y');


}

void goToRC (int r, int c){
    COORD coord; // coordinates
    coord.X = c; coord.Y = r; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printBattlefield(){
	int rowStart=8; int collumnStart=windowSizeX/2-((boardCollumn*2+2)/2);
	
	//Move bullets up
	for (int i=0; i<boardRow; i++){
		goToRC(rowStart, collumnStart);	cout << "|";	
		for (int j=0; j<boardCollumn; j++){	
			//If printing an enemy, change color
			if (board[i][j] == '*') {
				setColor(12); cout << board[i][j]; setColor(7); cout << " "; 
			} else cout << board[i][j] << " ";
			
			//If printing a bullet
			if (board[i][j] == '!') {
				//If an enemy is destroyed, beep and add points.
				if (board[i-1][j] == '*'){points++;}					
				board[i-1][j] = '!'; board[i][j] = ' ';
			} 
		}
		cout << "|"; rowStart++; cout << endl;
	}

	//Move enemies down
	for (int i=boardRow-1; i>=0; i--){
		goToRC(rowStart, collumnStart);
		for (int j=0; j<boardCollumn; j++){
			if (board[i][j] == '*') {
				if ((i+1)==boardRow){
				board[i][j] = ' ';	
				} else {
				board[i][j] = ' '; board[i+1][j] = '*';					
				}
		
			}
		}
	}	
}

void getMove(){
	//D+Space (Move right and shoot)
	if (GetAsyncKeyState('D') && GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';
		if(gunPosition+1 <boardCollumn){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition+1]);
		gunPosition++;			
		}
	} 
	//A+Space (Move left and shoot)	
	else if (GetAsyncKeyState('A') && GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';
		if(gunPosition-1 >=0){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition-1]);
		gunPosition--;			
		}
	} 
	//Space (Shoot)	
	else if (GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		board[boardRow-2][gunPosition] = '!';			
	}
	//A (Move left)
	else if (GetAsyncKeyState('A')) {
		if(gunPosition-1 >=0){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition-1]);
		gunPosition--;			
		}
	}
	//D (Move right)
	else if (GetAsyncKeyState('D')) {
		if(gunPosition+1 <boardCollumn){
		swap(board[boardRow-1][gunPosition], board[boardRow-1][gunPosition+1]);
		gunPosition++;			
		}
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

void resetBattlefield(){
	for (int i=0; i<boardRow-1; i++){
		for (int j=0; j<boardCollumn-1; j++){
			board[i][j]=' ';
		}
	}
}

void panelTryAgain(){
	goToRC(24,0); cout << "                                                       ";
	goToRC(25,0); cout << "                                                       ";
	goToRC(26,0); cout << "                                                       ";
	goToRC(27,0); cout << "                                                       ";
	goToRC(28,0); cout << "                                                       ";
	goToRC(29,0); cout << "                                                       ";
	
	goToRC(26,(windowSizeX/2)-5); cout << "Try Again?";
	goToRC(27,(windowSizeX/2)-8); cout << "[Y] Yes | [N] No";
}

void artYouDied(){
goToRC(13, (windowSizeX/2)-23); cout << " __ __ _____ _____    ____  _____ _____ ____  ";   
goToRC(14, (windowSizeX/2)-23); cout << "|  |  |     |  |  |  |    \\|     |   __|    \\ ";  
goToRC(15, (windowSizeX/2)-23); cout << "|_   _|  |  |  |  |  |  |  |-   -|   __|  |  |";  
goToRC(16, (windowSizeX/2)-23); cout << "  |_| |_____|_____|  |____/|_____|_____|____/";  
                   



 
                                              
}
