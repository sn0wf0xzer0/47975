//Header file for the Space class: an integral part of the Board class.
//Author: John Palacios.

#include <iostream>
using namespace std;

#ifndef SPACE_H
#define SPACE_H

class Space;
	ostream &operator << (ostream &, const Space &);		//Forward declaration of overloaded stream extraction operator.

class Space
{
private:
	bool owned;						//Spaces state in respect to being owned.
	char owner;						//owner's character if owned, or location if not owned.
	void setSpace(char);			//Used as initial set up of board.
public:
	Space()
	{owned = false; owner = ' ';}
	//Default constructor.
	Space(char);
	//Test constructor.
	~Space();
	//destructor.
	void flipSpace(char);
	//Sets the owner and ownership based on alpha numeric character passed into this function.
	friend ostream &operator << (ostream & stream, const Space &instanceOf)
	{
		stream << instanceOf.owner; 
		return stream;
	}
	//Overloaded ostream sream extraction operator used to display owner's character to screen.
	/*friend class Board;*/
	//Because the Board contains a dynamic array of this class, Board must be able to manipulate space objects.
	friend class Game;
	//The Game obj. must manipulate the Board obj, which must manipulate space objects.
};

#endif /* SPACE_H */