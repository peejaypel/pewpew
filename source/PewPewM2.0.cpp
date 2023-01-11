//PewPew Mark1.3
//peejaygal

//NOTES: Beta version. Press W and D to navigate ship, press space to shoot.

#include <iostream>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <conio.h>
using namespace std;

int boardRow=25;			//This is the number of rows, modular variable for all loops
int boardCollumn=11;		//This is the number of collunns, modular variable for all loops
char board[25][11];			//The matrix of the battlefield
int gunPosition=5;			//Position of the gun (in collumn)
int colorGlobal=63;			//Global color lol
int windowSizeX=55;			//Size of window in terms of x axis
int windowSizeY=40;			//Size of window in terms of x axis
int points=0;				//Points counter
int enemyNextSpawnTimer;	//Timer till next enemy spawn. Will spawn a new enemy if it reaches enemySpawnRate
int enemySpawnRate=20;		//Cap for next enemy spawn. 
int refreshRate=30; 		//Refresh rate of the game, lower number means faster gameplay
char resp; 					//Variable for try again
int level=1;
int health=10; 					//Number of level is the same as number of enemies.

void goToRC(int r, int c);
void printBattlefield();
void getMove();
void resizeWindow();
void setColor(int value);
void artPewPew();
void artYouDied();
void generateEnemies(int level);
bool shipIsAlive();
void resetBattlefield();
void panelTryAgain();
void changeLevel();
void printHealthbar();

int main(){
	
	do{
		
		resizeWindow(); artPewPew(); srand((time(NULL))); resetBattlefield();
		cout << "\n=======================================================";
		board[boardRow-1][5] = 'T';	gunPosition=5; health=10; points=0; goToRC(33,0); 
		cout << "=======================================================" << endl;
		
		do{
		changeLevel();
		if (enemyNextSpawnTimer == enemySpawnRate) {enemyNextSpawnTimer=0; generateEnemies(level);}
			getMove(); printBattlefield();
			
			goToRC(34,0); cout << "Level: " << level << "     " << "Health: " << health; 
			goToRC(35,0); cout << "Points: " << points;
			goToRC(36,0); cout << "EnemyNextSpawnTimer: " << enemyNextSpawnTimer;
			goToRC(37,0); cout << "EnemySpawnRate: " << enemySpawnRate;
			
			printHealthbar(); enemyNextSpawnTimer++; Sleep(refreshRate);
		
		}while (shipIsAlive() && !(health<=0));	
		
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
				health--;
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

void generateEnemies(int level){
	for (int i=1; i<=level; i++){
		int random;	
		random = rand()%boardCollumn; 
		board[0][random] = '*';
	}
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
	for (int i=0; i<boardRow; i++){
		for (int j=0; j<boardCollumn; j++){
			board[i][j]=' ';
		}
	}
}

void panelTryAgain(){
	goToRC(34,0); cout << "                                                       ";
	goToRC(35,0); cout << "                                                       ";
	goToRC(36,0); cout << "                                                       ";
	goToRC(37,0); cout << "                                                       ";
	goToRC(3839,0); cout << "                                                       ";
	goToRC(29,0); cout << "                                                       ";
	goToRC(35,(windowSizeX/2)-6); cout << "Highscore: " << points;
	goToRC(36,(windowSizeX/2)-5); cout << "Try Again?";
	goToRC(37,(windowSizeX/2)-8); cout << "[Y] Yes | [N] No";
}

void artYouDied(){
goToRC(18, (windowSizeX/2)-23); cout << " __ __ _____ _____    ____  _____ _____ ____  ";   
goToRC(19, (windowSizeX/2)-23); cout << "|  |  |     |  |  |  |    \\|     |   __|    \\ ";  
goToRC(20, (windowSizeX/2)-23); cout << "|_   _|  |  |  |  |  |  |  |-   -|   __|  |  |";  
goToRC(21, (windowSizeX/2)-23); cout << "  |_| |_____|_____|  |____/|_____|_____|____/";  
}

void changeLevel(){
	if (points >=0 && points <= 20) {
	level=1; refreshRate=30;	
	}
	else if (points >=21 && points <= 30){
	level=2; refreshRate=25;	
	} 
	else if (points >=31 && points <= 40){
	level=3; refreshRate=22;	
	} 
	else if (points >=41 && points <= 50){
	level=4; refreshRate=19;	
	} 
	else {
	level=5; refreshRate=15;	
	}	
}

void printHealthbar(){
	goToRC(38,0); 
	switch (health){
		case 10: cout << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 9: cout << char(176) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 8: cout << char(176) << char(176) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 7: cout << char(176) << char(176) << char(176) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 6: cout << char(176) << char(176) << char(176) << char(176) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 5: cout << char(176) << char(176) << char(176) << char(176) << char(176) << char(178) << char(178) << char(178) << char(178) << char(178); break;
		case 4: cout << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(178) << char(178) << char(178) << char(178); break;
		case 3: cout << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(178) << char(178) << char(178); break;
		case 2: cout << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(178) << char(178); break;
		case 1: cout << char(176) << char(178) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(178); break;
		case 0: cout << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176); break;
	}
}
