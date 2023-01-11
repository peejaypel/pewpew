# pewpew
## A simple C++ game

Changes throughout:
### PewPew [Mark 1] (2425 4DEC19)
- beta stage
- added left and right movements
- added firing gun
- moved board printing to printBoard() function

### PewPew [Mark 1.1] (2443 4DEC19)
screenshots/1.1.png
- added goToRC(), setColor();
- included <windows.h> library for windows commands
- moved movements to getMove() function
- added ability to fire and move at the same time
- larger and longer  battlefield size
- added semi-modular battlefield function
- included <sstream> library for modular window size
- aligned battlefield to middle(medyo haha)
- added PewPew art (artPewPew())
- added test enemies (spawn using 'P') button
- bullets now destroy enemies
- enemies now destroy battleship
- added beep for shoot sound [BUGGY-BEEP DELAY CAUSES GAME TO SLOW]
- added point system, +points for every enemy killed
END-OF-MARK-1.1-(0236 4DEC19)

### PewPew [Mark 1.2] (1312 4DEC19)
- added function generateEnemies() to generate enemy on a random collumn on row 0
- included <ctime> for srand to use machine time
- added timer for next enemy to spawn, added spawnrate as timer cap 
- FOUND BUG: letting an enemy pass through will break the game 
- added function bool shipIsAlive() to check if there is still a ship in the battlefield
- lol nag crash
END-OF-MARK-1.2-(1338 4DEC19)
//managed to recover file
//fixed bug: letting an enemy pass through will no longer break the game
END-OF-MARK-1.2.1-(1346 4DEC19)

### PewPew [Mark 1.3] (1558 4DEC19)
- included <conio.h> for getch();
- added try again functionality
- added panelTryAgain() to print Try Again message on the bottom panel
- added resetBattlefield() function for game restart
- commented all beep sounds because of lag
- changed enemy color to red
- added global variable 'refreshRate' to change game speed
- removed spawn enemies using 'P' button
- added "YOU DIED" art on defeat
END-OF-MARK-1.3-(1725 4DEC19)

### PewPew [Mark2.0] (1116 5DEC19)
- LEVELS PATCH
- made battlefield longer (preparation for more enemies);
- added levels, level number means number of enemies 
- added comments for global variables
- added changeLevel function, will change level if player gets 20(level1), 30(level2), 40(level3), 50(level4) points, level 5 is 51points and up.
- added health
- enemies that reach the lowest border will now consume 1 health
- added printHealthbar() function to print healthbar //note, still manual printing.
- added highscore on try again prompt
END-OF-MARK-2.0-(1213 5DEC19)

### PewPew [Mark2.1] (1125 6DEC19)
- move healthbar to middle
- larger healthbar, health count still 10
- moved score
- added highscore
- mvoed level counter 
- added generateMedKit() function
- modular printHealthBar();
- added feature to reset health to 10 whenever a medkit is acquired by the ship
- added printRules() function, this function prints rules lol
- added gamePause() function
- added pause art and pause feature: Press P to pause, press Y to continues
END-OF-MARK-2.1-(1303 6DEC19)

### PewPew 2 [Mark3.0] (1524 8DEC19)
- VISUAL UPDATE/OVERHAUL
- created sprites for ship, enemy, and medkit
- new functions: artBorder(); artEnemy(); artMedKit();
- changed matrix variable char board[][] to battleField[]
- changed variable boardRow and boardCollumn to rowSize, colSize;
- readded enemies
- enemies now in pixels
- enemies now go down
//A LOT MORE TO FIX, UNPLAYABLE MARK
END-OF-MARK-3.0 (1956 8DEC19)

### PewPew 2 [Mark3.1] (0058 11DEC19)
- readded getmove
- added resizeFont function (code not mine)
- readded bullet function
- bullets now in pixels
- readded the ship
- ship now in pixels
- added rate of spawn for enemy
- added letters() function
- PEWPEW text now in pixels
- readded bool shipIsAlive() function
- readded try again function 
- Again? Y/N prompt now in pixels
- added artBorder() art function. prints border
- Again?, Y/N, PEWPEW pixels now centered (fixed position, not modular)
- readded medkit
- medkits now in pixels
- readded gamePause() function. "Press 'p' to pause, press 'y' to continue"
- pause now in pixels
- added more colors
//known bug: game restart/pause continue sometimes makes the game very laggy
//NOW A PLAYABLE MARK
END-OF-MARK-3.1 (0519 11DEC19)

### PewPew 2 [Mark3.2] (0605 13DEC19)
- changed letters() function to artAlphaNumeric();
- added function artDictionary();
- added more letters to artAlphaNumeric();
- added numbers to artAlphaNumeric();
- added artDictionary();
- added score
- added highscore
- added pixel scoreboard on right side
- improved border
- added healthbar (with heart pixel art)
- moved preliminary statements to gamePreparation() function
- readded healing function from medkit
- added levels, changeLevel() function
- added designed logo- added artPewPew() function
END-OF-MARK-3.2 (0932 13DEC19)
