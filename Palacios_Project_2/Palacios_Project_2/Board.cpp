//Implementation of the Board class.
//File: Board.cpp
//Author: John Palacios.

#include "Board.h"
#include "Space.h"
#include "SearchableRow.h"
#include <string>
#include <iostream>
using namespace std;

Board::Board()
{
	bool retry = false;
	int ch = 55;  //Interger base to assigned count character.
	root = 3;
	numSpaces = root * root;
	//I could use a two dimensional array of space objects;
	//But the SearchableRow takes care of some tasks
	//Related to dynamic alocation.
	spaces = new SearchableRow<Space> [root];
	do{
		//This process may be repeated should the system cause
		//my vector object to throw a memory allocation error
		//Class for some temporary reason.
		try{
			for(int i = 0; i < root; i++){
				for(int j = 0; j < root; j++){
			//Now to set each space to designate it's
			//Key to be pressed to capture it.
			ch -= i * root;
			ch += j;
			spaces[i].push(Space(ch));
		ch = 55;
		}
	}
		}
		catch(ObjectRow<Space>::AllocError){
			string reply;
			cout << "It would seem that there is not enough\n"
				<< "available memory on your system to play\n"
				<< "this game, or something has gone terribly\n"
				<< "wrong. Not to pannic; I can try again, type\n"
				<< "[yes] to try again.\n";
			getline(cin, reply);
			if(tolower(reply[0]) == 'y'){
				retry = true;
			}
			else{
				cout << "Okay, exiting program- please inspect your\n"
					<< "System. Good bye.\n";
				exit(1);
			}
		}
	}while(retry == true);
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
	bool retry = false;
	int ch = 55;  //Interger base to assigned count character.
	root = base;
	numSpaces = root * root;
	//I could use a two dimensional array of space objects;
	//But the SearchableRow takes care of some tasks
	//Related to dynamic alocation.
	spaces = new SearchableRow<Space> [root];
	do{
		//This process may be repeated should the system cause
		//my vector object to throw a memory allocation error
		//Class for some temporary reason.
		try{
			for(int i = 0; i < root; i++){
				for(int j = 0; j < root; j++){
			//Now to set each space to designate it's
			//Key to be pressed to capture it.
			ch -= i * root;
			ch += j;
			spaces[i].push(Space(ch));
		ch = 55;
		}
	}
		}
		catch(ObjectRow<Space>::AllocError){
			string reply;
			cout << "It would seem that there is not enough\n"
				<< "available memory on your system to play\n"
				<< "this game, or something has gone terribly\n"
				<< "wrong. Not to pannic; I can try again, type\n"
				<< "[yes] to try again.\n";
			getline(cin, reply);
			if(tolower(reply[0]) == 'y'){
				retry = true;
			}
			else{
				cout << "Okay, exiting program- please inspect your\n"
					<< "System. Good bye.\n";
				exit(1);
			}
		}
	}while(retry == true);

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
	delete [] spaces;
	spaces = 0;			//<--Propblem: system is calling this f(x) in addition to the once I am calling it.
						//Grounding the pointer fixes this problem.
}

void Board::flipSpace(int pos, char token)
{
	//This algorythem will only work on a 3 by three board.
	int i;
	int j;
	if(pos >= numSpaces - (root - 1) && pos <= numSpaces)
	{
		//Top row.
		i = 0;
		j = pos - 7;	//This statement = 0, 1, or 2.
	}
	if(pos >= numSpaces - (2 * root -1)  && pos <= numSpaces - root)
	{
		//Middle row.
		i = 1;
		j = pos - 4;	//The index of the dynTArr pointer.
	}
	if(pos >= numSpaces - (3 * root -1) && pos <= numSpaces - (root*2))
	{
		//Bottom row.
		i = 2;
		j = pos - 1;
	}
	spaces[i][j].flipSpace(token);
	//spaces[i][j].flipSpace(token); <-- this is identical to the old code.
}

void Board::showBoard()
{	
	rightPos = 0;
	downPos = 0;
	//This was fun to work out.
	for(int row = 0; row < root + 2; row++){
			cout << "\t";
			//Based on evenness of outer for loop counter,
			//Call either the space containing row print f(x)
			//Or the seperation printing f(x);
		for(int col = 0; col < root + 2; col++){
			if(row % 2 == 0)
				printSpaces(col, row);
			else{
				printSeps(col);
			}
		}
		//Each time f(x) printSpaces is called,
		//The first index of the SearchableRow
		//Array must be incremented so as to work with
		//The next object.
		if(row % 2 == 1){
			downPos++;
		}
		//Each row starts at index 0.
		rightPos = 0;
		cout << endl;
	}
	cout << endl;

}

void Board::printSeps(int col)
{
	//These look like +	& = except more visually appealing.
	char symb[2] = {205, 206};
	if(col % 2 == 0)
		cout << symb[0] << symb[0] << symb[0];
	else
		cout << symb[1];
}

void Board::printSpaces(int col, int row)
{
	//This is the || symbol; connects with the + symbol of
	//The printSeps f(x) for a coherent looking board.
	char symb = 186;
	if(col % 2 == 0){
		cout << " " << spaces[downPos][rightPos] << " ";
		rightPos++;
	}
	else
		cout << symb;
}