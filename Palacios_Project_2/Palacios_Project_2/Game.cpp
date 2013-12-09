//Implementation of the Game class.
//File: Game.cpp
//Author: John Palacios.

#include "Space.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Victory.h"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game()
{
	ex.playerName = "Player X";
	ex.playerToken = 'X';
	oh.playerName = "Player O";
	oh.playerToken = 'O';
	field = new Board;
	root = field->getRoot();
	numSpaces = field->getNumSpaces();
	turnNum = 1;
	numMoves = numSpaces;
	fatlady = false;
	victory = false;
	catsGame = false;
	srand(static_cast<unsigned>(time(0)));
	compStrat.blkOpYeX	= false;
	compStrat.blkYeEx	= false;
	compStrat.blkUndef	= false;
	compStrat.blkConst	= false;
	compStrat.constBlkd = -1;
	compStrat.undefBlkd = -1;
	compStrat.posConst	= -1;
	compStrat.posUndef	= -1;
	compStrat.nextMoveX = -1;
	compStrat.nextMoveY = -1;
}

Game::Game(Player eX, Player oH)
{
	ex = eX;
	oh = oH;
	field = new Board;
	root = field->getRoot();
	numSpaces = field->getNumSpaces();
	turnNum = 1;
	numMoves = numSpaces;
	fatlady = false;
	victory = false;
	catsGame = false;
	srand(static_cast<unsigned>(time(0)));
	compStrat.blkOpYeX	= false;
	compStrat.blkYeEx	= false;
	compStrat.blkUndef	= false;
	compStrat.blkConst	= false;
	compStrat.constBlkd = -1;
	compStrat.undefBlkd = -1;
	compStrat.posConst	= -1;
	compStrat.posUndef	= -1;
	compStrat.nextMoveX = -1;
	compStrat.nextMoveY = -1;
}

Game::~Game()
{
	field->~Board();
	delete [] availMoves;
}

void Game::displayField()
{
	field->showBoard();
}

void Game::cap(int pos, Player act)
{
	field->flipSpace(pos, act.playerToken);

	if(turnNum > 2 * root + 1 && victory == false)
	{
		cout << "Looks like no one wins this game.\n";
		fatlady = true;
		catsGame = true;
	}

	else if(turnNum >= root)
	{
		checkStatus(act);
	}
}

void Game::checkStatus(Player act)
{
	int numOpYeX = 0;				//Number of spaces captured by act in line y = -x.
	int numYeqEx = 0;				//Number of spaces captured by act in line y = x.
	int numConst = 0;				//Number of spaces captured by act in line y = some constant.
	int numUndef = 0;				//Number of spaces captured by act in line x = some constant.
	compStrat.numOpYeX = false;		//set/reset conditional human play flags.
	compStrat.numYeqEx = false;
	compStrat.numConst = false;
	compStrat.numUndef = false;
	

	//Show me what victory looks like!
	//diagonal left to right
	for(int pos = 0; pos < root; pos++){
		if(field->spaces[pos][pos].owner == act.playerToken){
			numOpYeX++;
			if(numOpYeX == root - 1 && act.playerToken == 'X'){
				compStrat.numOpYeX = true;
			}
			if(numOpYeX == root){
				for(int i = 0; i < root; i++){
						cout << static_cast<char>(7);
					}
				cout << act.playerName << " wins!\n";
				victor = act;
				victory = true;
				fatlady = true;
			}
		}
	}

	//diagonal right to left
	for(int row = 0, col = root - 1; row < root; row++, col--){
		if(field->spaces[row][col].owner == act.playerToken){
			numYeqEx++;
			if(numYeqEx == root - 1 && act.playerToken == 'X'){
				compStrat.numYeqEx = true;
			}
			if(numYeqEx == root){
				for(int i = 0; i < root; i++){
						cout << static_cast<char>(7);
					}
				cout << act.playerName << " wins!\n";
				victor = act;
				victory = true;
				fatlady = true;
			}
		}
	}

	//accross.
	for(int i = 0; i < root; i++){
		numConst = 0;
		for(int j = 0; j < root; j++){
			if(field->spaces[i][j].owner == act.playerToken){
				numConst++;
				if(numConst == root - 1 && act.playerToken == 'X'){
					compStrat.numConst = true;
					compStrat.posConst = i;
				}
				if(numConst == root){
					for(int i = 0; i < root; i++){
						cout << static_cast<char>(7);
					}
					cout << act.playerName << " wins!\n";
					victor = act;
					victory = true;
					fatlady = true;
				}
			}
		}
	}

	//down.
	for(int i = 0; i < root; i++){
		numUndef = 0;
		for(int j = 0; j < root; j++){
			if(field->spaces[j][i].owner == act.playerToken){
				numUndef++;
				if(numUndef == root - 1 && act.playerToken == 'X'){
					compStrat.numUndef = true;
					compStrat.posUndef = i;
				}
				if(numUndef == root){
					for(int i = 0; i < root; i++){
						cout << static_cast<char>(7);
					}
					cout << act.playerName << " wins!\n";
					victor = act;
					victory = true;
					fatlady = true;
				}
			}
		}
	}
}

void Game::saveGame()
{
	fstream dataFile;
	int j = 0;

	winner.nameLength = victor.nameLength;
	for(int i = 0; i < victor.nameLength; i++){
		winner.player[i] = victor.playerName[i];
	}
	
	for(int row = 0; row < root; row++){
		for(int col = 0; col < root; col++){
			winner.board[j] = field->spaces[row][col].owner;
			j++;
		}
	}

	dataFile.open("victories.dat", ios::app | ios::binary);
	dataFile.write(reinterpret_cast<char *>(&winner), sizeof(winner));
	dataFile.close();
}

void Game::displayMenu()
{
	cout << "type [help] to learn how to navigate game menues.\n"
		<< "type [rules] to learn how you play this version of Tic-Tac-Toe.\n"
		<< "type [play] to play a game of Tic-Tac-Toe!\n"
		<< "type [fast play] to play a fast game of Tic-Tac-Toe.\n"
		<< "type [single] to play a fast game against an easey AI.\n"
		<< "type [cat] to play a fast game against a challenging AI.\n"
		<< "Type [victories] to see past victories.\n"
		<< "type [exit] to exit game.\n";
}

Victory *Game::getVictories(int &numEntries)
{
	fstream dataFile;
	Victory *entries;

	dataFile.open("victories.dat", ios::in | ios::binary);

	if(dataFile.fail()){
		cout << "Error oppening victories.dat.";
		exit(1);
	}

	dataFile.seekg(0L, ios::end);
	numEntries = dataFile.tellg() / sizeof(Victory);
	dataFile.seekg(0L, ios::beg);

	entries = new Victory [numEntries];

	for(int i = 0; i < numEntries; i++){
		dataFile.seekg(i * sizeof(Victory), ios::beg);
		dataFile.read(reinterpret_cast<char *>(&entries[i]), sizeof(Victory));
	}
	dataFile.close();
	return entries;
}

void Game::printVictory(Victory entries[], int pos)
{
	int count = 0;
	char symb[] = {186, 205, 206};
	
	cout << "Winner: ";
	for(int i = 0; i < entries[pos].nameLength; i++){
	cout << entries[pos].player[i];
	}
	cout << "\nWho's board looked like:\n";
	for(int i = 0; i < 5; i++){
		cout << "\t";
		for(int j = 0; j < 5; j++){
			if(i % 2 == 0){
				if(j % 2 == 0){
					cout << " " << entries[pos].board[count] << " ";
					count++;
				}
				if(j % 2 == 1){
					cout << symb[0];
				}
			}
			if(i % 2 == 1){
				if(j % 2 == 0){
					cout << symb[1] << symb[1] << symb[1];
				}
				if(j % 2 == 1){
					cout << symb[2];
				}
			}

		}
		cout << endl;
	}
}

void Game::dispVictories()
{
	int pos = 0;
	int numEntries;
	string command;
	Victory *victories;
	victories = getVictories(numEntries);
	cout << "~Hall of fame~\n"
		<< "Here you will find the Tic-tac-toe champions of days gone bye;\n"
		<< "you may browse this list of victories at your leasure.\n";
	do
	{
		do
		{
			printVictory(victories, pos);
			cout << endl;
			cout << "This is entry " << pos + 1 << " of " << numEntries << endl;
			cout << "Type [back] to see the previous entry.\n"
				<< "Type [next] to see the next entry.\n"
				<< "Type [done] when you would like to return to the main menue.\n";
			
			getline(cin, command);
		} while(validateComm(tolower(command[0])) == false);
		if(tolower(command[0]) == 'b' && pos == 0){
			cout << static_cast<char>(7) << "\nNo more entries this way; type [next] to see next entry.\n";
		}
		if(tolower(command[0]) == 'b' && pos > 0){
			pos--;
		}
		if(tolower(command[0]) == 'n' && pos == numEntries - 1){
			cout << static_cast<char>(7) << "\nNo more entries this way; type [back] to see next entry.\n";
		}
		if(tolower(command[0]) == 'n' && pos < numEntries - 1){
			pos++;
		}
		if(tolower(command[0]) == 'd'){
			cout << "You typed [" << command << "]. Exiting hall of fame...\n";
		}
	}while(tolower(command[0]) != 'd');
	delete [] victories;
}

bool Game::validateComm(char comm)
{
	bool goodComm = false;

	if(tolower(comm) == 'b'){
		goodComm = true;
	}
	if(tolower(comm) == 'n'){
		goodComm = true;
	}
	if(tolower(comm) == 'd'){
		goodComm = true;
	}

	return goodComm;
}

int Game::getChoice()
{
	string choice;
	int num = 0;
	char option;
	getline(cin, choice);
	option = tolower(choice[0]);

	switch (option){
		case 'h':
			num = 1;
			break;
		case 'r':
			num = 2;
			break;
		case 'p':
			num = 3;
			break;
		case 'f':
			num = 4;
			break;
		case 's':
			num = 5;
			break;
		case 'c':
			num = 6;
			break;
		case 'v':
			num = 7;
			break;
		case 'e':
			num = 8;
			break;
		default:
			cout << "[" << choice << "] was not an option, please try again.\n";
			break;
	}
	return num;
}

bool Game::validateName(string name)
{
	bool goodName = true;		//input validity flag
	if(name.size() > 21){
		goodName = false;
	}
	return goodName;
}

void Game::playerXturn()
{
	string move;

	cout << "Turn number " << turnNum << endl;
	cout << ex.playerName << "'s turn.\n";
	availMoves = getAvailableMoves();
	displayField();
	cout << "Available moves: ";
	for(int i = 0; i < numMoves; i++){
		cout << availMoves[i] << " ";
	}
	cout << endl;
	do{
		cout << "Please select an available move.\n";
		getline(cin, move);
	} while (validateMove(move[0]) == false);
	cap(move[0] - 48, ex);
	turnNum++;
	exTurn = false;
}

void Game::playerOturn()
{
	string move;

	cout << "Turn number " << turnNum << endl;
	cout << oh.playerName << "'s turn.\n";
	availMoves = getAvailableMoves();
	displayField();
	cout << "Available moves: ";
	for(int i = 0; i < numMoves; i++){
		cout << availMoves[i] << " ";
	}
	cout << endl;
	do{
		cout << "Please select an available move.\n";
		getline(cin, move);
	} while (validateMove(move[0]) == false);
	cap(move[0] - 48, oh);
	turnNum++;
	exTurn = true;
}

void Game::systemRandTurn()
{
	cout << "Turn number " << turnNum << endl;
	cout << "system's turn.\n";
	availMoves = getAvailableMoves();
	displayField();
	cout << "Available moves: ";
	for(int i = 0; i < numMoves; i++){
		cout << availMoves[i] << " ";
	}
	cout << endl;
	int move = rand() % numMoves;
		cout << "Your system chooses: " << availMoves[move] << "\n";
	cap(availMoves[move] - 48, oh);
	turnNum++;
	exTurn = true;
}

void Game::systemCatTurn()
{
	int move;
	cout << "Turn number " << turnNum << endl;
	cout << "Cat's turn.\n";
	availMoves = getAvailableMoves();
	displayField();
	cout << "Available moves: ";
	for(int i = 0; i < numMoves; i++){
		cout << availMoves[i] << " ";
	}
	cout << endl;
	if(turnNum == 2){
		for(int i = 0; i < root; i++){
			if(field->spaces[i].linSearch(Space('X')) != -1){
			compStrat.humanFstX = field->spaces[i].linSearch(Space('X'));
			compStrat.humanFstY = i;
			}
		}
		catTurnOne();
	}
	else if(turnNum == 4){
		catTurnTwo();
	}
	else if(turnNum == 6){
		catTurnThree();
	}
	else{
	move = rand() % numMoves;
	cout << "Cat chooses: " << availMoves[move] << "\n";
	cap(availMoves[move] - 48, oh);
	}
	turnNum++;
	exTurn = true;
}

void Game::catTurnOne()
{
	bool corner = false;
	bool center = false;
	Tetrahedron oneD4;
	Decahedron oneD10;
	int roll;
	//look at the corners of the board.
	for(int i = 0; i < root; i += 2){
		for(int j = 0; j < root; j += 2){
			if(field->spaces[i][j].owner == 'X'){
				//compStrat.humanFstY = i;
				//compStrat.humanFstX = j;
				compStrat.opener = 'A';
				corner = true;
			}
		}
	}
	//look at the center of the board.
	if(field->spaces[1][1].owner == 'X'){
		compStrat.opener = 'B';
		center = true;
	}
	//Smart first move by player ex, time to limit thier next move.
	if(corner == true){
		compStrat.fstPlayY = 1;
		compStrat.fstPlayX = 1;
		cap(5,oh);
	}
	else if(center == true){
		oneD4.roll();
		roll = oneD4.checkDie();
		switch(roll){
			case 1:
				compStrat.fstPlayY = 0;
				compStrat.fstPlayX = 0;
				cap(7, oh);
				break;
			case 2:
				compStrat.fstPlayY = 0;
				compStrat.fstPlayX = 2;
				cap(9, oh);
				break;
			case 3:
				compStrat.fstPlayY = 2;
				compStrat.fstPlayX = 0;
				cap(1, oh);
				break;
			case 4:
				compStrat.fstPlayY = 2;
				compStrat.fstPlayX = 2;
				cap(3, oh);
				break;
			default:
				cout << "Cat says, \"I think my d 4 is broken :C.\"\n"
					<< "Default case in catTurnOne.\n";
				break;
		}
	}
	else{
		compStrat.opener = 'C'; 
		oneD10.roll();
		roll = oneD10.checkDie() / 2;
		if(roll == 0){
			roll = 1;
		}
		switch(roll){
			case 1:
				compStrat.fstPlayY = 0;
				compStrat.fstPlayX = 0;
				cap(7, oh);
				break;
			case 2:
				compStrat.fstPlayY = 0;
				compStrat.fstPlayX = 2;
				cap(9, oh);
				break;
			case 3:
				compStrat.fstPlayY = 2;
				compStrat.fstPlayX = 0;
				cap(1, oh);
				break;
			case 4:
				compStrat.fstPlayY = 2;
				compStrat.fstPlayX = 2;
				cap(3, oh);
				break;
			case 5:
				compStrat.fstPlayY = 1;
				compStrat.fstPlayX = 1;
				cap(5, oh);
				break;
			default:
				cout << "Cat says, \"I think my d 10 is broken :C.\"\n"
					<< "Default case in catTurnOne.\n";
				break;
		}
	}
	if(compStrat.opener == 'A'){
		cout << "Cat says, \"I see that you've played this game before.\"\n";
	}
	if(compStrat.opener == 'B'){
		cout << "Cat says, \"A decent first move for an amature.\"\n";
	}
	if(compStrat.opener == 'C'){
		cout << "Cat says, \"Perhaps you should try taking the center,\n"
			<< "or a corner as your first move next time.\"\n";
	}
}

void Game::catTurnTwo()
{
	Tetrahedron oneD4;
	//Player opened with the center capture...
	if(compStrat.opener == 'B'){
		if(compStrat.numConst){
			for(int i = 0; i < root; i++){
				for(int j = 0; j < root; j += 2){
					if(field->spaces[1][i].owned == false){
						field->spaces[1][i].flipSpace('O');
						compStrat.blkConst = true;
						compStrat.constBlkd = 1;
						cout << "\n";
						if(field->spaces[compStrat.fstPlayY][i].owned == false){
							compStrat.nextMoveX = i;
							compStrat.nextMoveY = compStrat.fstPlayY;
							
						}
						else{
							compStrat.nextMoveX = 2 - i;
							compStrat.nextMoveY = 2 - compStrat.fstPlayY;
						}
						break;
					}
					break;
				}
			}
		}
		if(compStrat.numUndef){
			for(int i = 0; i < root; i++){
				if(field->spaces[i][2].owned == false){
					cap(8 - root * i, oh);
					compStrat.blkUndef = true;
					compStrat.undefBlkd = 2;
					if(field->spaces[0][0].owned == false){
						compStrat.nextMoveX = 0;
						compStrat.nextMoveY = 0;
					}
					else{
						compStrat.nextMoveX = 2;
						compStrat.nextMoveY = 0;
					}
					cout << "\n";
				}
			}
		}
		//player is moving in line y=x.
		else if(compStrat.numYeqEx){
			compStrat.blkYeEx = true;
			//check/cap available space in line y = x.
			if(compStrat.fstPlayY == 0 && compStrat.fstPlayX == 2){
				cap(7, oh);
				compStrat.nextMoveX = 0;
				compStrat.nextMoveY = 1;
			}
			else if(compStrat.fstPlayY == 2 && compStrat.fstPlayX == 0){
				cap(3, oh);
				compStrat.nextMoveX = 1;
				compStrat.nextMoveY = 2;
			}
			else{
				if(field->spaces[2][0].owned == false){
					cap(1, oh);
					compStrat.nextMoveX = 2;
					compStrat.nextMoveY = 2;
				}
				else
				{
					cap(9, oh);
					compStrat.nextMoveX = 0;
					compStrat.nextMoveY = 0;
				}
			}
		}
		//The player is moving in line -y=x
		else if(compStrat.numOpYeX){
			compStrat.blkOpYeX = true;
			//Check/cap available space in line y = -x.
			if(compStrat.fstPlayY == 2 && compStrat.fstPlayX == 2){
				cap(6, oh);
			}
			else if(compStrat.fstPlayY == 0 && compStrat.fstPlayX == 0){
				cap(4, oh);
			}
			else{
				if(field->spaces[2][2].owned == false){
					cap(3, oh);
				}
				else
					cap(7, oh);
			}	
		}

	}

	if(compStrat.opener == 'A'){
		//If the player started in a corner and is going diagonal left to right
		//The player is attempting to fork the game, take an edge to block one
		//fork now.
		if(compStrat.numOpYeX == true){
			//This line is now blocked.
			compStrat.blkOpYeX = true;
			oneD4.roll();
			cap(oneD4.checkDie() * 2, oh);
			cout << "\n";
			switch(oneD4.checkDie()){
				case 1:
					compStrat.nextMoveX = 1;
					compStrat.nextMoveY = 0;
					break;
				case 2:
					compStrat.nextMoveX = 2;
					compStrat.nextMoveY = 1;
					break;
				case 3:
					compStrat.nextMoveX = 0;
					compStrat.nextMoveY = 1;
					break;
				case 4:
					compStrat.nextMoveX = 1;
					compStrat.nextMoveY = 2;
					break;
			}
		}
		//Now to check y = x.
		if(compStrat.numYeqEx == true){
			//This line is now blocked.
			compStrat.blkYeEx = true;
			oneD4.roll();
			cap(oneD4.checkDie() * 2, oh);
			cout << "\n";
			switch(oneD4.checkDie()){
				case 1:
					compStrat.nextMoveX = 1;
					compStrat.nextMoveY = 0;
					break;
				case 2:
					compStrat.nextMoveX = 2;
					compStrat.nextMoveY = 1;
					break;
				case 3:
					compStrat.nextMoveX = 0;
					compStrat.nextMoveY = 1;
					break;
				case 4:
					compStrat.nextMoveX = 1;
					compStrat.nextMoveY = 2;
					break;
			}
		}
		//Now to check x = some constant.
		if(compStrat.numUndef == true){
			for(int j = 0; j < root; j++){
				if(field->spaces[j][compStrat.humanFstX].owned == false){
					compStrat.blkUndef = true;
					compStrat.undefBlkd = compStrat.humanFstX;
					cap((7 - root * j) + compStrat.humanFstX, oh);
					compStrat.nextMoveX = 2 - compStrat.humanFstX;
					compStrat.nextMoveY = j;
				}
			}
		}
		//Player must be in y = constant.
		if(compStrat.numConst){
			for(int j = 0; j < root; j++){
				if(field->spaces[compStrat.humanFstY][j].owned == false){
					compStrat.blkConst = true;
					compStrat.constBlkd = compStrat.humanFstY;
					cap((7 - compStrat.humanFstY * root) + j, oh);
					compStrat.nextMoveX = 2 - j;
					compStrat.nextMoveY = 2 - compStrat.humanFstY;
				}
			}
		}
	}
	//Need to check for players who started on the edges.
	if(compStrat.opener == 'C'){
		//player is attempting to capture in line with undefined slope.
		if(compStrat.numUndef){
			for(int i = 0; i < root; i++){
				if(field->spaces[i].linSearch(Space('X')) == -1){
					//We know that the undefined line first marked by x is now blocked.
					compStrat.blkUndef = true;
					compStrat.undefBlkd = compStrat.humanFstX;
					if(field->spaces[i][compStrat.humanFstX].owned == false){
					cap((7 - i * root) + compStrat.humanFstX, oh);
					compStrat.nextMoveY = i;
					compStrat.nextMoveX = (compStrat.humanFstX + 1) % 3;
					}
					else{
						oneD4.roll();
						switch(oneD4.checkDie()){
							case 1:
								cap(7, oh);
								compStrat.nextMoveX = 2;
								compStrat.nextMoveY = 2;
								break;
							case 2:
								cap(9, oh);
								compStrat.nextMoveX = 0;
								compStrat.nextMoveY = 2;
								break;
							case 3:
								cap(1, oh);
								compStrat.nextMoveX = 2;
								compStrat.nextMoveY = 0;
								break;
							case 4:
								cap(3, oh);
								compStrat.nextMoveX = 0;
								compStrat.nextMoveY = 0;
								break;
							default:
								cout << "Cat says, \"I think my d 4 is broken :C.\"\n"
									<< "Error catTurnTwo, case C.\n";
								break;
						}
					}
				}
			}
		}
		//The player is attempting to complete three accross.
		if(compStrat.numConst){
			for(int i = 0; i < root; i++){
				//Cat only needs to check those searchable rows containing spaces
				//Captured by x. To trip numConst flag, both x's will be in a row.
				if(field->spaces[i].linSearch(Space('X')) != -1){
					//Now line y = i is blocked.
					compStrat.blkConst = true;
					compStrat.constBlkd = i;
					for(int j = 0; j < root; j++){
						if(field->spaces[i][j].owned == false){
							cap((7 - root * i) + j, oh);
							cout << "\n";
						}
					}
				}
			}
		}
	}
}

void Game::catTurnThree()
{
	bool goodIndex = false;
	bool capd = false;
	int move;

	//Ignore blocked lines with two player marks.
	if(compStrat.blkYeEx)
		compStrat.numYeqEx = false;
	if(compStrat.blkOpYeX)
		compStrat.numOpYeX = false;
	do{
		try{
			//Move in to victory or take next move.
			if(field->spaces[compStrat.nextMoveY][compStrat.nextMoveX].owned == false){
				cap((7 - compStrat.nextMoveY * root) + compStrat.nextMoveX, oh);
				capd = true;
			}
			goodIndex = true;	
		}
		catch(ObjectRow<Space>::OutOfBounds err){
			if(err.getDir()){
				compStrat.nextMoveY--;
				compStrat.nextMoveX--;
			}
			else{
				compStrat.nextMoveY++;
				compStrat.nextMoveX++;
			}

		}
	}while(goodIndex == false);
	if(capd == false){
		//Check for threats from the player.
		if(compStrat.numYeqEx && compStrat.blkYeEx == false){
			//This is not a false alarm. player threatens y = x.
			for(int row = 2, col = 0; col < root; row--, col++){
				if(field->spaces[row][col].owned == false){
					cap((7 - row * root) + col, oh);
					capd = true;
				}
			}
		}
		if(compStrat.numOpYeX && compStrat.blkOpYeX == false){
			//Player threatens y = -x.
			for(int i = 0; i < root; i++){
				if(field->spaces[i][i].owned == false){
					cap((7 - i * root) + i, oh);
					capd = true;
				}
			}
		}
		if(compStrat.numConst && compStrat.constBlkd != compStrat.posConst){
			for(int i = 0; i < root; i++){
				if(field->spaces[compStrat.posConst][i].owned == false){
					cap((7 - compStrat.posConst * root) + i, oh);
					capd = true;
				}
				else{
					cap(availMoves[rand() % numMoves], oh);
					capd = true;
				}
			}
		}
		if(compStrat.numUndef && compStrat.undefBlkd != compStrat.posUndef){
			for(int i = 0; i < root; i++){
				if(field->spaces[i][compStrat.posUndef].owned == false){
					cap((7 - i * root) + compStrat.posUndef, oh);
					capd = true;
				}
			}
		}
		else if(capd == false){
			move = rand() % numMoves;
			cap(availMoves[move], oh);
		}
	}
}

bool Game::validateMove(char move)
{
	bool goodMove = false;

	for(int i = 0; i < numMoves; i++){
		if(move == availMoves[i]){
			goodMove = true;
		}
	}
	return goodMove;
}

char *Game::getAvailableMoves()
{
	int moves = 0;
	char *availableMoves;
	availableMoves = new char[numMoves];

	for(int row = 0; row < root; row++){
		for(int col = 0; col < root; col++){
			if(field->spaces[row][col].owned == false){
				availableMoves[moves] = field->spaces[row][col].owner;
				moves++;
			}
		}
	}
	numMoves = moves;
	return availableMoves;
}

void Game::play()
{
	bool replay = false;
	int choice;
	string move;
	string name;
	string set;
	Player eX;
	Player oH;
	char symb[3] = {186, 205, 206};

	cout << "Welcome to Tic-Tac-Toe! The clasic strategy edition.\n"
		<< "The object of the game is to get three of your tokens in\n"
		<< "a row while preventing your opponent from doing the same!\n\n";

	do
	{
		do
		{
			displayMenu();
			choice = getChoice();
		}while (choice == 0);

		switch (choice)
		{
		case 1:
			cout << "This menue system allows you to make selections by typeing the first or more\n"
				<< "letters of the word appearing in brackets in the menu. Example:\n"
				<< "The text: \"type [next] to see the next entry.\" means that you should type\n"
				<< "the letter \"n\" and then hit enter to see the next entry. But you may also\n"
				<< "type the letters \"n\" \"e\" \"x\" \"t\" and then hit enter to accomplish the\n"
				<< "same task- infact, you could type any combination of letters so long as the\n"
				<< "first one is \"n\" to see the next entry.\n"
				<< "	->Option Details<-\n"
				<< "In the main menu, you have the option for this message, rules, play, fast play,\n"
				<< "single, cat, victories, and exit. Here's a quick description of each.\n"
				<< "rules:	This option gives you a simple run down of the rules of tic-tac-toe and\n"
				<< "	how to select a space for capture during game play in either play or\n"
				<< "	fastplay modes.\n"
				<< "play:	This option allows you to enter your name and your opponents name. This\n"
				<< "	game is identical to the fast play game option of tic-tac-toe, but the\n"
				<< "	winner's name and the board configureation will be saved, for later\n"
				<< "	viewing using the [victories] option in the main menu.\n"
				<< "fast play:\n"
				<< "	This option allows you and an opponent to play a fast game of \n"
				<< "	tic-tac-toe. Names do not need to be entered and the board will not be\n"
				<< "	saved when a player wins.\n"
				<< "single:\n"
				<< "	This option is a low dificulty one player game; the system is player Oh\n"
				<< "	whom will chose it's moves randomly... so you can't be sure if you will\n"
				<< "	win or get a cat's game.\n"
				<< "cat:\n"
				<< "	This option is a more difficult one player game; the system is\n"
				<< "	player oh who will actively try to block you.\n"
				<< "victories:\n"
				<< "	This option allows you to view saved victoriesin the following format:\n"
				<< "	Winner: Beck	<-- This is the name of the winning player.\n"
				<< "	Who's Board looked like:\n"
				<< "		 7 " << symb[0] << " 8 "<< symb[0] << " X\n"
				<< "		" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "		 4 " << symb[0] << " X "<< symb[0] << " O	<- This is what Beck's board looked like.\n"	
				<< "		" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "		 x " << symb[0] << " 2 "<< symb[0] << " O\n"
				<< "		This is entry 1 of 5	<- *This means that there are five\n"
				<< "		entries availablefor viewing and you are looking at the\n"
				<< "		first one.*\n"
				<< "		Type [back] to see the previous entry. \n"
				<< "		Type [next] to see the next entry.	\n"
				<< "		Type [done] when you would like to return to the main menue.\n"
				<< "		*To view another entry; simply choose one of the above options*\n"
				<< "		*If you try to tpye back here, you will hear a beep and see\n"
				<< "		a messagetelling you that there are no more options in that\n"
				<< "		direction: simply type next instad.*\n";
			break;

		case 2:
			cout << "Turn number 1\n"
				<< "Player X's turn\n"
				<< "\t 7 " << symb[0] << " 8 "<< symb[0] << " 9         type one of these numbers\n"
				<< "\t" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "\t 4 " << symb[0] << " 5 "<< symb[0] << " 6         <-to capture that space!\n"
				<< "\t" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "\t 1 " << symb[0] << " 2 "<< symb[0] << " 3    \n"
				<< "Available Moves: 7 8 9 4 5 6 1 2 3\n"
				<< "Please select an available move.\n"
				<< "[type a number, then press enter]\n\n"
				<< "you may choose any space displayed that\n"
				<< "does not belong to another player. here's\n"
				<< "an example of such a condition:\n"
				<< "Turn number 6\n"
				<< "Player X's turn\n"
				<< "\t X " << symb[0] << " 8 "<< symb[0] << " O         type one of these numbers\n"
				<< "\t" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "\t 4 " << symb[0] << " X "<< symb[0] << " 6         <-to capture that space!\n"
				<< "\t" << symb[1] << symb[1] << symb[1]<< symb[2] << symb[1] << symb[1]<< symb[1] << symb[2] << symb[1]<< symb[1] << symb[1] << endl
				<< "\t 1 " << symb[0] << " 2 "<< symb[0] << " O    \n"
				<< "Available Moves: 8 4 6 1 2\n"
				<< "Please select an available move.\n"
				<< "[type a number, then press enter]\n\n"
				<< "The spaces 3 and 9 have been captured by\n"
				<< "player Oh; therefore player eX may not take\n"
				<< "Those spaces, nor spaces marked with thier own\n"
				<< "token \"X\" this game.\n\n"
				<< "Once a player has achieved victory or the game\n"
				<< "is a cat's game, you will be asked if you would\n"
				<< "like to play again.\n"
				<< "If you manage to win, your name and the board\n"
				<< "Configureation will be saved and you may use it\n"
				<< "to brag to your friends later.\n"
				<< "*Tip: turn on your speakers.\n\n";
			break;

		case 3:
			do
			{
				cout << "Setting up new game...\n";
				do
				{
					cout << "Please enter the name of player eX:\n"
						<< "(up to twenty characters long)\n";
					getline(cin, name);
				}while (validateName(name) == false);
				eX.nameLength = static_cast<int>(name.length());
				eX.playerName = name.c_str();
				name.clear();

				do
				{
					cout << "Please enter the name of player oH:\n"
						<< "(up to twenty characters long)\n";
					getline(cin, name);
				}while (validateName(name) == false);
				oH.nameLength = static_cast<int>(name.length());;
				oH.playerName = name.c_str();
				name.clear();

				eX.playerToken = 'X';
				oH.playerToken = 'O';
				Game *newGame;
				newGame = new Game(eX, oH);
				cout << static_cast<char>(7);
				do
				{
					if(newGame->getExTurn()){
						newGame->playerXturn();
					}
					else
						newGame->playerOturn();

				} while (newGame->fatlady == false);

				if(newGame->victory){
					newGame->saveGame();
				}

				move.clear();
				cout << "would you like to play again?\n";
				getline(cin, move);
				if(tolower(move[0]) == 'y'){
					newGame->~Game();
					replay = true;
				}
				else{
					delete newGame;
					replay = false;
				}

			} while (replay == true);
			break;

		case 4:
			do
			{
				Game *newGame;
				newGame = new Game();
				cout << static_cast<char>(7);
				do
				{
					if(newGame->getExTurn()){
						newGame->playerXturn();
					}
					else
						newGame->playerOturn();

				} while (newGame->fatlady == false);

				move.clear();
				cout << "would you like to play again?\n";
				getline(cin, move);
				if(tolower(move[0]) == 'y'){
					newGame->~Game();
					replay = true;
				}
				else{
					replay = false;
					newGame->~Game();
				}
			} while (replay == true);
			break;

		case 5:
			do
			{
				Game *newGame;
				newGame = new Game();
				cout << static_cast<char>(7);
				do
				{
					if(newGame->getExTurn()){
						newGame->playerXturn();
					}
					else
						newGame->systemRandTurn();

				} while (newGame->fatlady == false);

				move.clear();
				cout << "would you like to play again?\n";
				getline(cin, move);
				if(tolower(move[0]) == 'y'){
					newGame->~Game();
					replay = true;
				}
				else{
					replay = false;
					newGame->~Game();
				}
			} while (replay == true);
			break;
		case 6:
			do
			{
				Game *newGame;
				newGame = new Game();
				cout << static_cast<char>(7);
				do
				{
					if(newGame->getExTurn()){
						newGame->playerXturn();
					}
					else
						newGame->systemCatTurn();

				} while (newGame->fatlady == false);

				move.clear();
				cout << "would you like to play again?\n";
				getline(cin, move);
				if(tolower(move[0]) == 'y'){
					newGame->~Game();
					replay = true;
				}
				else{
					replay = false;
					newGame->~Game();
				}
			} while (replay == true);
			break;

		case 7:
			dispVictories();
			break;

		case 8:
			cout << "Good bye.\n";
			break;
		} 
	}while(choice != 5);
}