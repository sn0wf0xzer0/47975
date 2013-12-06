//The Game class; this class orchestrates the constituant Board and Space objects that make up a game.
//Author: John Palacios

#include "Space.h"
#include "Board.h"
#include "Player.h"
#include "Victory.h"
#include "Tetrahedron.h"
#include "Decahedron.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef GAME_H
#define GAME_H

class Game
{
private:
	Player ex;				//Structure storing player x's name and token character.
	Player oh;				//Structure storing player o's name and token character.
	Player victor;			//The winner's details will be stored here.
	Victory winner;			//Data storage struct.
	Board *field;			//Pointer to a two dimensional array of space objects.
	int root;				//root value of Board object. used in a number of calclulations.
	int numSpaces;			//number of spaces on board, used in a number of calculations.
	int turnNum;			//Used to determine a cat's game.
	int numMoves;			//The number of spaces minus spaces owned by a player.
	char *availMoves;		//A pointer to a char array used to display the available moves.
	bool fatlady;			//End of game flag. True when a player wins or cat's game.
	bool victory;			//player wins flag. True when a player wins.
	bool catsGame;			//Draw flag. True when no one wins.
	bool exTurn;			//Player alternation flag. True when it is player X's turn.
public:
	Game();													
	//Default constructor.
	Game(Player, Player);									
	//Named player overloaded constructor.
	~Game();												
	//Destructor.
	void displayField();									
	//Calls Board object's showBoard() f(x).
	void cap(int, Player);									
	//Calls Board object's flipSpace() f(x).
	void checkStatus(Player);								
	//Reviews Board for victory conditions.
	void saveGame();										
	//Called when a player wins; dumps Victory struct into dat file.
	bool getExTurn() const
	{ return exTurn;}
	//Determine's turn.
	void playerXturn();										
	//Human Player x's turn protocall.
	void playerOturn();										
	//Human Player o's turn protocall.
	void systemRandTurn();
	//Random AI player's turn.
	void systemCatTurn();
	//AI actively seeks a cats's game.
	void catTurnOne();
	//AI first turn.
	void catTurnTwo();
	//AI second turn.
	bool validateMove(char);								
	//Check move selection against available moves.
	char *getAvailableMoves();								
	//Audit's field for unowned spaces; returns char array with thos chars.
	static void displayMenu();								
	//Main Menu system implementation.
	static Victory *getVictories(int &);					
	//creates array of victory structs and fills it with binary data from dat file.
	static void printVictory(Victory [], int);				
	//prints entry from victories array.
	static void dispVictories();							
	//Secondary Menu system implementation: browse victories array.
	static bool validateComm(char);							
	//validates user command in secondary Menu system.
	static int getChoice();									
	//Processes user choice in main menue system.
	static bool validateName(string);						
	//Ensures name will fit in victory struct member player name.
	static void play();										
	//Runs Main menu, sets up games, runs games, handls victory review.
	
};

#endif /* GAME_H */