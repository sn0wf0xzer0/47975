//Implementation file for the Decahedron class.
//File: Decahedron.cpp
//Author: John Palacios

#include "Decahedron.h"

void Decahedron::roll()
{
	result = rand() % numSides + 1;
	setDie(result);
	return checkDie();
}

void Decahedron::cheat(int num)
{
	if(num > 0 && num < numSides){
		setDie(num);
	}
	else{
		setDie(0);
}