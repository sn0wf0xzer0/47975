//Implementation of the Board class.
//File: Board.cpp
//Author: John Palacios.

#include "Board.h"
#include "Space.h"
#include <iostream>
using namespace std;

Board::Board()
{
	int ch = 55;  //Interger base to assigned count character.

	//Default board is 3*3
	root = 3;						
	numSpaces = root * root;
	//creat rows of space objects.
	spaces = new Space* [root];		
						
	for(int i = 0; i < root; i++)
	{
		//creat collumns of space objects.
		spaces[i] = new Space[root];	
	}

	for(int i = 0; i < root; i++)
	{
		for(int j = 0; j < root; j++)
		{
			//Set spaces to thier respective positions
			//in the game field based on standard
			//num pad configuration.
			ch -= i * root;
			ch += j;
			spaces[i][j].flipSpace(ch);
			//Reset char base.
			ch = 55;						
		}
	}
}

Board::~Board()
{
	for(int i = 0; i < root; i++)
	{
	delete [] spaces[i];
	}

	delete [] spaces;
}

void Board::flipSpace(int pos, char token)
{
	int i;
	int j;
	if(pos >= numSpaces - 2 && pos <= numSpaces)
	{
		i = 0;
		j = pos - 7;
	}
	if(pos >= numSpaces - 5 && pos <= numSpaces - root)
	{
		i = 1;
		j = pos - 4;
	}
	if(pos >= numSpaces - 8 && pos <= numSpaces - (root*2))
	{
		i = 2;
		j = pos - 1;
	}
	spaces[i][j].flipSpace(token);
}

void Board::showBoard()
{	
	rightPos = 0;
	downPos = 0;

	for(int row = 0; row < root + 2; row++){
			cout << "\t";
		for(int col = 0; col < root + 2; col++){
			if(row % 2 == 0)
				printSpaces(col, row);
			else{
				printSeps(col);
			}
		}
		if(row % 2 == 1){
			downPos++;
		}
		rightPos = 0;
		cout << endl;
	}
	cout << endl;

}

void Board::printSeps(int col)
{
	char symb[2] = {205, 206};
	if(col % 2 == 0)
		cout << symb[0] << symb[0] << symb[0];
	else
		cout << symb[1];
}

void Board::printSpaces(int col, int row)
{
	char symb = 186;
	if(col % 2 == 0){
		cout << " " << spaces[downPos][rightPos] << " ";
		rightPos++;
	}
	else
		cout << symb;
}