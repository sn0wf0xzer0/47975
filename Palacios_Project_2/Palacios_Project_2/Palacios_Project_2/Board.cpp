//Implementation of the Board class.
//File: Board.cpp
//Author: John Palacios.

#include "Board.h"
#include "Space.h"
#include "SearchableVector.h"
#include <iostream>
using namespace std;

Board::Board()
{
	int ch = 55;  //Interger base to assigned count character.
	root = 3;
	numSpaces = root * root;
	spaces = new SearchableVector<Space> [root];
	for(int i = 0; i < root; i++){
		for(int j = 0; j < root; j++){
			spaces[i].push_back(Space());
		}
	}
	for(int i = 0; i < root; i++){
		for(int j = 0; j < root; j++){
			ch -= i * root;
			ch += j;
		spaces[i].operator[](j).flipSpace(ch);
		ch = 55;
		}
	}
	//Default board is 3*3
							
	
	//creat rows of space objects.
	//spaces = new Space* [root];		
	//					
	//for(int i = 0; i < root; i++)
	//{
	//	//creat collumns of space objects.
	//	spaces[i] = new Space[root];	
	//}

	//for(int i = 0; i < root; i++)
	//{
	//	for(int j = 0; j < root; j++)
	//	{
	//		//Set spaces to thier respective positions
	//		//in the game field based on standard
	//		//num pad configuration.
	//		ch -= i * root;
	//		ch += j;
	//		spaces[i][j].flipSpace(ch);
	//		//Reset char base.
	//		ch = 55;						
	//	}
	//}
}

Board::Board(int base)
{
	int ch = 55;  //Interger base to assigned count character.

	//Default board is 3*3
	root = base;
	numSpaces = root * root;
	spaces = new SearchableVector<Space>[root];
	//for(int i = 0; i < root; i++){
	//	for(int j = 0; j < root; j++){
	//		spaces[i].push_back(Space(' '));
	//	}
	//}
	for(int i = 0; i < root; i++){
		for(int j = 0; j < root; j++){
			ch -= i * root;
			ch += j;
			spaces[i].push_back(Space(ch));
		//spaces[i][j].flipSpace(ch);
		ch = 55;
		}
	}

	//creat rows of space objects.
	//spaces = new Space* [root];		
	//					
	//for(int i = 0; i < root; i++)
	//{
	//	//creat collumns of space objects.
	//	spaces[i] = new Space[root];	
	//}

	//for(int i = 0; i < root; i++)
	//{
	//	for(int j = 0; j < root; j++)
	//	{
	//		//Set spaces to thier respective positions
	//		//in the game field based on standard
	//		//num pad configuration.
	//		ch -= i * root;
	//		ch += j;
	//		spaces[i][j].flipSpace(ch);
	//		//Reset char base.
	//		ch = 55;						
	//	}
	//}
}

Board::~Board()
{
	for(int i = 0; i < root; i++){
		for(int j = 0; j < spaces[i].size(); j++){
			spaces[i].operator [](j).~Space();
		}
	}
	delete [] spaces;
}

void Board::flipSpace(int pos, char token)
{
	int i;
	int j;
	if(pos >= numSpaces - (root - 1) && pos <= numSpaces)
	{
		i = 0;
		j = pos - 7;
	}
	if(pos >= numSpaces - (2 * root -1)  && pos <= numSpaces - root)
	{
		i = 1;
		j = pos - 4;
	}
	if(pos >= numSpaces - (3 * root -1) && pos <= numSpaces - (root*2))
	{
		i = 2;
		j = pos - 1;
	}
	spaces[i].operator[](j).flipSpace(token);
	//spaces[i][j].flipSpace(token);
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