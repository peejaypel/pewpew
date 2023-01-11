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
int score; int highscore; int lastscore;
int health;
int gunPosition = 3;
int enemyNextSpawnTimer;
int gameSpeed = 25;
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
void artAlphaNumeric (char input, int colorInput, int r, int c);
bool shipIsAlive();
void resetBattlefield();
void generateMedkit();
void gamePause();
void artDictionary(string input, int colorInput, int r, int c);
void scoreboard(int r, int c);
void gamePreparation();
void drawHealth(int r, int c);
void changeLevel();
void artPewPew(int r, int c);


int main(){
	resizeFont(9,8); resizeWindow(150, 62);
	do{
	gamePreparation();	
		do{
		if (enemyNextSpawnTimer==20){generateEnemies(level); enemyNextSpawnTimer=0;} cout << endl; 	
		changeLevel(); lastscore=score; generateMedkit(); drawBattlefield(9, 4); getMove(); 
			
		enemyNextSpawnTimer++; Sleep(gameSpeed);
		
	 if (!shipIsAlive() || health==0){drawBattlefield(9,4); break;}
		}while(true);
		
		//Try Again Propmt
		artDictionary("AGAIN?", 7, 24, 12); artDictionary ("y/n", 8, 31, 24);
		do{
			response = getch();	
		}while (!(response == 'Y' || response == 'y' || response == 'N' || response == 'n' ));
	}while(response == 'Y' || response == 'y');
		
		

}

void gamePreparation(){
	system("CLS");
	resetBattlefield(); battleField[rowSize-3][gunPosition]='T'; health=6; enemyNextSpawnTimer=0; score=0; level=1; score=0;
	artPewPew(2, 50); artBorder(8,0);	scoreboard(11, 122); drawHealth(25, 75);
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
				if (battleField[i-3][j] == '*'){ score++; if (score > highscore){highscore = score;} scoreboard(11, 122);}
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
				drawHealth(25, 75);
				} else {
				battleField[i][j] = ' '; battleField[i+3][j] = '*';					
				}
			}
			//Function for printing medkit
			if (battleField[i][j] == '@') {
				if ((i+3)==rowSize || battleField[i+3][j]=='T'){
				battleField[i][j] = ' ';
				health++;
				drawHealth(25, 75);
				} else {
				battleField[i][j] = ' '; battleField[i+3][j] = '@';					
				}
			}			
		}
	}	
}

void scoreboard(int r, int c){
	artDictionary("SCORE:", 12, 11, 76); artDictionary("HIGH:", 12, 18, 76); 
	char firstDigit = '0' + score%10; char secondDigit = '0' + (score%100-score%10)/10; char thirdDigit = '0' + (score%1000-(score%100-score%10))/100;
	char firstHighDigit = '0' + highscore%10; char secondHighDigit = '0' + (highscore%100-highscore%10)/10; char thirdHighDigit = '0' + (highscore%1000-(highscore%100-highscore%10))/100;
	
	if (thirdDigit == 0) {artAlphaNumeric(' ', 15, r, c);} else {artAlphaNumeric(thirdDigit, 14, r, c);	}
	if (secondDigit == 0) {artAlphaNumeric(' ', 15, r, c+8);} else {artAlphaNumeric(secondDigit, 14, r, c+8);}
	if (firstDigit == 0) {artAlphaNumeric(' ', 15, r, c+8+8);} else {artAlphaNumeric(firstDigit, 14, r, c+8+8);	}
	
	if (thirdHighDigit == 0) {artAlphaNumeric(' ', 15, r+7, c);} else {artAlphaNumeric(thirdHighDigit, 14, r+7, c);	}
	if (secondHighDigit == 0) {artAlphaNumeric(' ', 15, r+7, c+8);} else {artAlphaNumeric(secondHighDigit, 14, r+7, c+8);}
	if (firstHighDigit == 0) {artAlphaNumeric(' ', 15, r+7, c+8+8);} else {artAlphaNumeric(firstHighDigit, 14, r+7, c+8+8);	}
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

void changeLevel(){
	if (score >=0 && score <= 20) {
	level=1; gameSpeed=30;	
	}
	else if (score >=21 && score <= 30){
	level=2; gameSpeed=20;	
	} 
	else if (score >=31 && score <= 40){
	level=3; gameSpeed=15;	
	} 
	else if (score >=41 && score <= 50){
	level=4; gameSpeed=7;	
	} 
	else {
	level=5; gameSpeed=0;	
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
	for (int i=0; i<=53; i++){
		goToRC(r,c);
		if (i == 0 || i == 53){
			for (int j=0; j<35; j++){
			setColor(2); cout << char(219) << char(219);
			}
			for (int j=0; j<40; j++){
			setColor(15); cout << char(219) << char(219); setColor(2);
			}	
		} else {
			cout << char(219) << char(219);	
			for (int j=0; j<33; j++){
			cout << "  ";
			}
			cout << char(219) << char(219);	
			setColor(15); cout << char(219) << char(219);				
			for (int j=0; j<38; j++){
			cout << "  ";
			}				
			setColor(15); cout << char(219) << char(219); setColor(2);		
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
	artAlphaNumeric('|', 12, 27, 28); artAlphaNumeric('|', 12, 27, 36); 
	do{
	 unpause = getch();
	}while (!(unpause=='Y' || unpause=='y'));
	gamePreparation();
	//artAlphaNumeric('P', 15, 2, 11); artAlphaNumeric('E', 12, 2, 19); artAlphaNumeric('W', 12, 2, 27); artAlphaNumeric('P', 15, 2, 35); artAlphaNumeric('E', 12, 2, 43); artAlphaNumeric('W', 12, 2, 51);
	
}


void artAlphaNumeric (char input, int colorInput, int r, int c){
	switch(input){
	case 'P':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'S':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " "; 			  setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'C':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";  			setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'O':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";  			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;	
	
	case 'R':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";  			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'H':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;				
	
	case 'E':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " "; 			setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'W':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'A':
	goToRC(r,c); 	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'G':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'I':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " ";	     	  setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'N':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;

	case '0':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '1':
	goToRC(r,c); 	setColor(colorInput); cout << " " << " ";	 setColor(colorInput); cout << " " << " ";	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";	 setColor(colorInput); cout << " " << " ";	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " ";	 setColor(colorInput); cout << " " << " " ;	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " ";	 setColor(colorInput); cout << " " << " " ;	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " ";	 setColor(colorInput); cout << " " << " " ;	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '2':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); 		cout << " " << " ";		setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); 		cout << " " << " " ;	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '3':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " ";		 	  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '4':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '5':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '6':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " " ;		 	  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '7':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " " ;				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '8':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '9':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " " ; 			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput);	cout << " " << " " ;			setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '?':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " " ;			setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";	
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput);	cout << char(219) << char(219);	setColor(colorInput); cout << " " << " " ;			  setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'y':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	break;
	
	case 'n':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	break;
	
	case '/':
	goToRC(r,c); 	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";	
	goToRC(r+1,c);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << " " << " ";	
	break;
	
	case '|':
	goToRC(r,c); 	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+3,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+4,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+5,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	goToRC(r+6,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";
	break;
	
	case ':':
	goToRC(r,c); 	setColor(colorInput); cout << " " << " "; 			  setColor(colorInput);	setColor(colorInput); cout << " " << " ";
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	setColor(colorInput); cout << " " << " ";
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " "; 	 		  setColor(colorInput);	setColor(colorInput); cout << " " << " ";
	goToRC(r+3,c);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput);	setColor(colorInput); cout << " " << " ";
	goToRC(r+4,c);	setColor(colorInput); cout << " " << " "; 	  		  setColor(colorInput);	setColor(colorInput); cout << " " << " ";
	break;
	
	case '@':
	goToRC(r,c); 	setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << " " << " ";			  setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+1,c);	setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(15); 		cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219);
	goToRC(r+2,c);	setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << char(219) << char(219);	setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";
	goToRC(r+3,c); 	setColor(colorInput); cout << " " << " ";	 			setColor(colorInput); cout << " " << " " ;				setColor(colorInput); cout << char(219) << char(219); setColor(colorInput); cout << " " << " ";				setColor(colorInput); cout << " " << " ";
	break;	
	}
}
void drawHealth(int r, int c){
	if (health >=6) {artAlphaNumeric('@', 12, r, c);} else {artAlphaNumeric('@', 8, r, c);}
	if (health >=5) {artAlphaNumeric('@', 12, r, c+12);} else {artAlphaNumeric('@', 8, r, c+12);}
	if (health >=4) {artAlphaNumeric('@', 12, r, c+12+12);} else {artAlphaNumeric('@', 8, r, c+12+12);}
	if (health >=3) {artAlphaNumeric('@', 12, r, c+12+12+12);} else {artAlphaNumeric('@', 8, r, c+12+12+12);}
	if (health >=2) {artAlphaNumeric('@', 12, r, c+12+12+12+12);} else {artAlphaNumeric('@', 8, r, c+12+12+12+12);}
	if (health >=1) {artAlphaNumeric('@', 12, r, c+12+12+12+12+12);} else {artAlphaNumeric('@', 8, r, c+12+12+12+12+12);}	
}

void artDictionary(string input, int colorInput, int r, int c){
	if (input == "PEWPEW"){
	 artAlphaNumeric('P', colorInput, r, c); artAlphaNumeric('E', colorInput, r, c+8); artAlphaNumeric('W', colorInput, r, c+8+8); artAlphaNumeric('P', colorInput, r, c+8+8+8); artAlphaNumeric('E', colorInput, r, c+8+8+8+8); artAlphaNumeric('W', colorInput, r, c+8+8+8+8+8); 	
	} else if (input == "AGAIN?"){
	 artAlphaNumeric('A', colorInput, r, c); artAlphaNumeric('G', colorInput, r, c+8); artAlphaNumeric('A', colorInput, r, c+8+8); artAlphaNumeric('I', colorInput, r, c+8+8+8); artAlphaNumeric('N', colorInput, r, c+8+8+8+8); artAlphaNumeric('?', colorInput, r, c+8+8+8+8+8);
	} else if (input == "y/n"){
	 artAlphaNumeric('y', colorInput, r, c); artAlphaNumeric('/', colorInput, r, c+8); artAlphaNumeric('n', colorInput, r, c+8+8); 
	} else if (input == "SCORE:"){
	 artAlphaNumeric('S', colorInput, r, c); artAlphaNumeric('C', colorInput, r, c+8); artAlphaNumeric('O', colorInput, r, c+8+8); artAlphaNumeric('R', colorInput, r, c+8+8+8); artAlphaNumeric('E', colorInput, r, c+8+8+8+8); artAlphaNumeric(':', colorInput, r, c+8+8+8+8+8); 
	} else if (input == "HIGH:"){
	 artAlphaNumeric('H', colorInput, r, c); artAlphaNumeric('I', colorInput, r, c+8); artAlphaNumeric('G', colorInput, r, c+8+8); artAlphaNumeric('H', colorInput, r, c+8+8+8); artAlphaNumeric(':', colorInput, r, c+8+8+8+8);  
	}
}

void artPewPew(int r, int c){
	artAlphaNumeric('P', 154, r, c); artAlphaNumeric('E', 23, r, c+8); artAlphaNumeric('W', 23, r, c+8+8); artAlphaNumeric('P', 154, r, c+8+8+8); artAlphaNumeric('E', 23, r, c+8+8+8+8); artAlphaNumeric('W', 23, r, c+8+8+8+8+8); 	
	goToRC(r+2, c-46); for (int i=0; i<=20; i++){setColor(162); cout <<char(219); setColor(155); cout << char(219);}
	goToRC(r+2, c+52); for (int i=0; i<=20; i++){setColor(155); cout <<char(219); setColor(162); cout << char(219);}
	
}
