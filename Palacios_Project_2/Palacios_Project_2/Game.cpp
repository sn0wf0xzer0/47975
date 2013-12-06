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
	srand(time(0));
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
	srand(time(0));
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

	//Show me what victory looks like!
	//diagonal left to right
	for(int pos = 0; pos < root; pos++){
		if(field->spaces[pos][pos].owner == act.playerToken){
			numOpYeX++;
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
		<< "type [derpy] to play a fast game against an easey AI.\n"
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
		case 'd':
			num = 5;
			break;
		case 'v':
			num = 6;
			break;
		case 'e':
			num = 7;
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
		catTurnOne();
	}
	else if(turnNum == 4){
		move = catTurnTwo();
	}
	else{
	move = rand() % numMoves;
	}
		cout << "Cat chooses: " << availMoves[move] << "\n";
	cap(availMoves[move] - 48, oh);
	turnNum++;
	exTurn = true;
}

int Game::catTurnOne()
{
	bool corner = false;
	bool center = false;
	int move;
	//look at the corners of the board.
	for(int i = 0; i < root; i += 2){
		for(int j = 0; j < root; j += 2){
			if(field->spaces[i][j].owner == 'X'){
				corner = true;
			}
		}
	}
	//look at the center of the board.
	if(field->spaces[1][1].owner == 'X'){
		center = true;
	}
	
	if(corner == true){
		cap(5,oh);
	}
	else if(center == true){
		switch(
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
				<< "derp, victories, and exit. Here's a quick description of each.\n"
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
				<< "derp:\n"
				<< "	This option is a low dificulty one player game; the system is player Oh\n"
				<< "	whom will chose it's moves randomly... so you can't be sure if you will\n"
				<< "	win or get a cat's game.\n"
				<< "Victories:\n"
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
			dispVictories();
			break;

		case 7:
			cout << "Good bye.\n";
			break;
		} 
	}while(choice != 5);
}