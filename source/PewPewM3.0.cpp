#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

char battleField[15][24]; int rowSize=15; int colSize=24;
int level=1;
int windowSizeX=50;
int windowSizeY=50;
int score;
int health;

void artMedkit(int r, int c);
void artShip(int r, int c);
void artEnemy(int r, int c);
void goToRC(int r, int c);
void artFill(int r, int c);
void setColor(int value);
void artBorder();
void drawBattlefield();
void generateEnemies(int level);


int main(){
	do{
	system("CLS");
	generateEnemies(1);
	drawBattlefield();	
	Sleep(50);
//	goToRC(0,0); artEnemy(0,0);	
	}while(true);

}

void drawBattlefield(){
	int rowPointer=5; int collumnPointer=5; //windowSizeX/2-((colSize*2+2)/2);
	
	//Move entities up
	for (int i=0; i<rowSize; i=i+3){
		cout << "|";
		collumnPointer=5;
		for (int j=0; j<=colSize; j=j+3){			
			//If printing an enemy, change color
			if (battleField[i][j] == '*') {
				artEnemy(rowPointer, collumnPointer);
				//artEnemy(rowPointer,collumnPointer);
			} else 
			if (battleField[i][j] == '@'){
				setColor(10); cout << battleField[i][j]; setColor(7); cout << " ";
			} 
			else {
				artFill(rowPointer,collumnPointer);	
			}
			
			//If printing a bullet
			if (battleField[i][j] == '!') {
				//If an enemy is destroyed, beep and add score.
				if (battleField[i-1][j] == '*'){score++;}						
				battleField[i-1][j] = '!'; battleField[i][j] = ' ';
			} 
		collumnPointer=collumnPointer+8;
		}
		cout << endl;
		rowPointer=rowPointer+4;
	}

	//Move entities down
	for (int i=rowSize-1; i>=0; i--){
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
//			//Function for printing medkit
//			if (battleField[i][j] == '@') {
//				if ((i+1)==rowSize || battleField[i+1][j]=='T'){
//				battleField[i][j] = ' ';
//				health=10;
//				} else {
//				battleField[i][j] = ' '; rowSize[i+1][j] = '@';					
//				}
//			}			
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

//void drawBattlefield(){
//	int rowPointer=0; int colPointer=0;
//	for (int r=0; r<rowSize; r++){
//		for (int c=0; c<=colSize; c=c+3){
//			if (battleField[r][c]=='*'){
//				cout << "enm ";
//			} else cout << "XXX ";
//		}
//	cout << endl;
//	}
//}

void artBorder(){
	
}

void artMedKit(int r, int c){
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
	goToRC(r,c); 	setColor(12); cout << " " << " "; setColor(12); cout << " " << " "; setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";	 
	goToRC(r+1,c);	setColor(12); cout << " " << " "; setColor(12); cout << " " << " "; setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";
	goToRC(r+2,c);	setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";	setColor(12); cout << " " << " "; setColor(12); cout << " " << " ";		
}

void goToRC (int r, int c){
    COORD coord; // coordinates
    coord.X = c; coord.Y = r; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}
