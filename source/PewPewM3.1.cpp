#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>
using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); //This code is not mine. Source: http://mycodecollection.blogspot.com/2015/01/c-console-change-font-size.html

char battleField[40][24]; int rowSize=39; int colSize=24;
int level=1;
int windowSizeX=50;
int windowSizeY=50;
int score;
int highScore;
int health;
int gunPosition = 3;
int enemyNextSpawnTimer;
char response;

void artMedkit(int r, int c);
void artShip(int r, int c);
void artEnemy(int r, int c);
void goToRC(int r, int c);
void artFill(int r, int c);
void setColor(int value);
void artBorder(int r, int c);
void drawBattlefield(int r, int c);
void generateEnemies(int level);
void resizeWindow(int sizeX, int sizeY);
void resizeFont(int a, int b);
void getMove();
void artBullet(int r, int c);
void letters (char input, int r, int c);
bool shipIsAlive();
void resetBattlefield();
void generateMedkit();
void gamePause();


int main(){
	resizeFont(9,8); resizeWindow(70, 62);
	do{
	system("CLS");
	resetBattlefield(); battleField[rowSize-3][gunPosition]='T'; health=10; enemyNextSpawnTimer=0; score=0; level=1;
	letters('P', 2, 11); letters('E', 2, 19); letters('W', 2, 27); letters('P', 2, 35); letters('E', 2, 43); letters('W', 2, 51); artBorder(8,0); 
	
		do{ 
		getMove(); if (enemyNextSpawnTimer==20){generateEnemies(1); enemyNextSpawnTimer=0;}	cout << endl;
		generateMedkit(); drawBattlefield(9, 4); 	
		enemyNextSpawnTimer++;
		Sleep(0);
		if (!shipIsAlive()){drawBattlefield(9,4); break;}
		}while(true);
	
		letters('A', 24, 12); letters('G', 24, 20); letters('A', 24, 28); letters('I', 24, 36); letters('N', 24, 44); letters('?', 24, 52); //Print "AGAIN?"
		letters('y', 31, 24); letters('/', 31, 32); letters('n', 31, 40); //Print Y/N
		do{
			response = getch();	
		}while (!(response == 'Y' || response == 'y' || response == 'N' || response == 'n' ));
	}while(response == 'Y' || response == 'y');
		
		

}

void drawBattlefield(int rowPointer, int collumnPointer){
	int originalCollumnPointer=collumnPointer;
	
	//Move entities up
	for (int i=0; i<rowSize-2; i=i+3){
		collumnPointer=originalCollumnPointer;
		for (int j=0; j<colSize; j=j+3){	
				
			//Printing Process
			if (battleField[i][j] == '*') {artEnemy(rowPointer, collumnPointer);} //)
			else if (battleField[i][j] == '@'){artMedkit(rowPointer, collumnPointer);}
			else if (battleField[i][j] == '!'){artBullet(rowPointer, collumnPointer);} //r)
			else if (battleField[i][j] == 'T'){artShip(rowPointer, collumnPointer);} //)
			else {artFill(rowPointer,collumnPointer);}

			
			//If printing a bullet
			if (battleField[i][j] == '!') {
				//If an enemy is destroyed, beep and add points.
				if (battleField[i-3][j] == '*'){}					
				battleField[i-3][j] = '!'; battleField[i][j] = ' ';
			} 

		collumnPointer=collumnPointer+8;
		}
		
		cout << endl;
		rowPointer=rowPointer+4;
	}

	//Move entities down
	for (int i=rowSize; i>=0; i--){
		//goToRC(rowPointer, collumnPointer);
		for (int j=0; j<colSize; j=j+3){
			//Function for printing enemies
			if (battleField[i][j] == '*') {
				if ((i+3)==rowSize){
				battleField[i][j] = ' ';
				health--;
				} else {
				battleField[i][j] = ' '; battleField[i+3][j] = '*';					
				}
			}
			//Function for printing medkit
			if (battleField[i][j] == '@') {
				if ((i+3)==rowSize || battleField[i+3][j]=='T'){
				battleField[i][j] = ' ';
				health=10;
				} else {
				battleField[i][j] = ' '; battleField[i+3][j] = '@';					
				}
			}			
		}
	}	
}

void generateEnemies(int level){
	for (int i=1; i<=level; i++){
		do{
		int random;	
		random = rand()%colSize; 
			if (random%3==0 || random==1){
			battleField[0][random] = '*';
			break;	
			}
				
		}while (true);
	}
}

void generateMedkit(){
	int random, chance;
	
	chance = rand()%100;
	random = rand()%colSize;
	
	if (chance==1 || chance==50){
		battleField[0][random] = '@';
	}
}


void artBorder(int r, int c){
	setColor(2);
	for (int i=0; i<=53; i++){
		goToRC(r,c);
		if (i == 0 || i == 53){
			for (int j=0; j<35; j++){
			cout << char(219) << char(219);
			}	
		} else {
			cout << char(219) << char(219);	
			for (int j=0; j<33; j++){
			cout << "  ";
			}	
			cout << char(219) << char(219);			
		}
		r++;
	}
}

void artMedkit(int r, int c){
	goToRC(r,c); 	setColor(10); cout << char(219) << char(219); setColor(15); cout << char(219) << char(219); setColor(10); cout << char(219) << char(219);
	goToRC(r+1,c);	setColor(15); cout << char(219) << char(219); setColor(15); cout << char(219) << char(219); setColor(15); cout << char(219) << char(219);
	goToRC(r+2,c);	setColor(10); cout << char(219) << char(219); setColor(15); cout << char(219) << char(219); setColor(10); cout << char(219) << char(219);	
}

void artShip(int r, int c){
	goToRC(r,c); 	setColor(14); cout << " " << " ";			  setColor(14); cout << char(219) << char(219); setColor(14); cout << " " << " " ;	
	goToRC(r+1,c);	setColor(6 ); cout << char(219) << char(219); setColor(6 ); cout << char(219) << char(219); setColor(6 ); cout << char(219) << char(219);
	goToRC(r+2,c);	setColor(14); cout << char(219) << char(219); setColor(6 ); cout << char(219) << char(219); setColor(14); cout << char(219) << char(219);	
}

void artEnemy(int r, int c){
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " "; 			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << " " << " "; 			  setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
}

void artFill(int r, int c){
	goToRC(r,c); 	cout << "        "; 
	goToRC(r+1,c);	cout << "        ";
	goToRC(r+2,c);	cout << "        ";	
}

void artBullet(int r, int c){
	goToRC(r,c); 	setColor(12); cout << " " << " "; setColor(1); cout << char(219) << char(219); setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";	 
	goToRC(r+1,c);	setColor(12); cout << " " << " "; setColor(1); cout << char(219) << char(219); setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << " " << " "; setColor(1); cout << char(219) << char(219);	setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";	
}

void goToRC (int r, int c){
    COORD coord; // coordinates
    coord.X = c; coord.Y = r; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

void resizeWindow(int sizeX, int sizeY){
	windowSizeX = (sizeX);
	windowSizeY = (sizeY);
	stringstream screenSize;
	screenSize << "mode " << windowSizeX << "," << windowSizeY;
	system(screenSize.str().c_str());

}

//This code is not mine. Source: http://mycodecollection.blogspot.com/2015/01/c-console-change-font-size.html
 void resizeFont(int a, int b){  
  PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
  lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
  GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
  lpConsoleCurrentFontEx->dwFontSize.X = a;  
  lpConsoleCurrentFontEx->dwFontSize.Y = b;  
  SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
 } 
 
 void getMove(){

	//D+Space (Move right and shoot)
	if (GetAsyncKeyState('D') && GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		battleField[rowSize-6][gunPosition] = '!';
		if(gunPosition+3 <colSize){
		swap(battleField[rowSize-3][gunPosition], battleField[rowSize-3][gunPosition+3]);
		gunPosition=gunPosition+3;			
		}
	} 
	//A+Space (Move left and shoot)	
	else if (GetAsyncKeyState('A') && GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		battleField[rowSize-6][gunPosition] = '!';
		if(gunPosition-3 >=0){
		swap(battleField[rowSize-3][gunPosition], battleField[rowSize-3][gunPosition-3]);
		gunPosition=gunPosition-3;			
		}
	} 
	//Space (Shoot)	
	else if (GetAsyncKeyState(VK_SPACE)) {
		//Beep(1500,20);
		battleField[rowSize-6][gunPosition] = '!';			
	}
	//A (Move left)
	else if (GetAsyncKeyState('A')) {
		if(gunPosition-3 >=0){
		swap(battleField[rowSize-3][gunPosition], battleField[rowSize-3][gunPosition-3]);
		gunPosition=gunPosition-3;			
		}
	}
	//D (Move right)
	else if (GetAsyncKeyState('D')) {
		if(gunPosition+3 <colSize){
		swap(battleField[rowSize-3][gunPosition], battleField[rowSize-3][gunPosition+3]);
		gunPosition=gunPosition+3;				
		}
	}
	//P (Pause)
	else if (GetAsyncKeyState('P')) {
		gamePause();			
	}		
}

bool shipIsAlive(){
	for (int i=0; i<colSize; i++){
		if (battleField[rowSize-3][i] == 'T'){
			return true;
		}
	}
	return false;
}

void resetBattlefield(){
	for (int i=0; i<rowSize-1; i++){
		for (int j=0; j<colSize-1; j++){
			battleField[i][j]=' ';
		}
	}
}

void gamePause(){
	char unpause;
	letters('|', 27, 28); letters('|', 27, 36); 
	do{
	 unpause = getch();
	}while (!(unpause=='Y' || unpause=='y'));
	system("CLS");
	letters('P', 2, 11); letters('E', 2, 19); letters('W', 2, 27); letters('P', 2, 35); letters('E', 2, 43); letters('W', 2, 51); artBorder(8,0); 
	
}


void letters (char input, int r, int c){
	switch(input){
	case 'P':
	goToRC(r,c); 	setColor(26); cout << char(219) << char(219); setColor(26); cout << char(219) << char(219);	setColor(26); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(26); cout << char(219) << char(219); setColor(26); cout << " " << " ";				setColor(26); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(26); cout << char(219) << char(219); setColor(26); cout << char(219) << char(219);	setColor(26); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(26); cout << char(219) << char(219); setColor(26); cout << " " << " "; 			setColor(26); cout << " " << " " ;			  setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(26); cout << char(219) << char(219); setColor(26); cout << " " << " ";				setColor(26); cout << " " << " " ;			  setColor(12); cout << " " << " ";	
	break;
	
	case 'E':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " "; 			setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case 'W':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12);	cout << " " << " " ;			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case 'A':
	goToRC(r,c); 	setColor(12); cout << " " << " ";			  setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12);	cout << " " << " " ;			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case 'G':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12);	cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case 'I':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << " " << " ";			  setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << " " << " ";			  setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << " " << " ";	     	  setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12);	cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case 'N':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " " ;			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " " ;			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12);	cout << " " << " " ;			setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case '?':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << " " << " " ;			  setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " " ;			setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " ";	
	goToRC(r+4,c);	setColor(12); cout << " " << " " ;			  setColor(12);	cout << char(219) << char(219);	setColor(12); cout << " " << " " ;			  setColor(12); cout << " " << " ";	
	break;
	
	case 'y':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << " " << " ";			  setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";	
	break;
	
	case 'n':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	break;
	
	case '/':
	goToRC(r,c); 	setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";				setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";	
	goToRC(r+1,c);	setColor(12); cout << " " << " ";			  setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << " " << " ";				setColor(12); cout << " " << " ";			  setColor(12); cout << " " << " ";	
	break;
	
	case '|':
	goToRC(r,c); 	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+1,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+3,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+4,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+5,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	goToRC(r+6,c);	setColor(12); cout << char(219) << char(219); setColor(12); cout << char(219) << char(219);	setColor(12); cout << " " << " ";
	break;
	}	
	
}
