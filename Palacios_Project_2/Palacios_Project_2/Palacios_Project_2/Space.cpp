//Implementation of the Space class.
//File: Space.cpp
//Author: John Palacios.

#include "Space.h"
using namespace std;

Space::Space(char pos)
{
	owned = false;
	owner = pos;
}

Space::~Space()
{

}

void Space::setSpace(char num)
{
	owner = num;
}

void Space::flipSpace(char token)
{
	if(owned == false && (!isdigit(token))){
		owner = token;
		owned = true;
	}
	if(owned == false && isdigit(token)){
		setSpace(token);
	}
}