//Header file for the Board class; an integral part of the Game class.
//Author: John Palacios.

#include "Space.h"
#include "SearchableRow.h"
//using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
	int root;			//The root of the number of spaces, used for victory determination.
	int numSpaces;		//The total number of spaces.
	int rightPos;		//Keeps track of the element position when printing board.
	int downPos;		//Keeps track of the element position when printing board.
protected:
	SearchableRow<Space> *spaces;	//Spaces now stored in a dynamic array of SearchableRow<Space>
									//Template objects.
	//Space **spaces;		//pointer to two dimensional dynamic array of space objects.
public:
	Board();						
	//Default constructor.
	Board(int);
	//Constructor for different sized boards.
	~Board();						
	//Destructor.
	int getRoot() const				
	{ return root;}	
	//returns the square root of the number of spaces.			
	int getNumSpaces() const		
	{ return numSpaces;}
	//Tells the game how many spaces there are.
	void flipSpace(int, char);		
	//Change the owner and possibly state of the space obj.
	void showBoard();				
	//Prints the current familiar hash style playing field to the screen.
	void printSeps(int);			
	//prints the horizontal seperation characters.
	void printSpaces(int, int);		
	//Alternately prints space obj owner character or pipe char.
	friend class Game;				
	//Game has a Board, and Game needs to acces all of board's members.
};

#endif /* BOARD_H */