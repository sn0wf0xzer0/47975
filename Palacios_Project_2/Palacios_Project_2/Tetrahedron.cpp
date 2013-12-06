//Implementation file for the Tetrahedron class.
//File: Tetrahedron.cpp
//Author: John Palacios

#include "Tetrahedron.h"

void Tetrahedron::roll()
{
	result = rand() % numSides + 1;
	setDie(result);
	return checkDie();
}

void Tetrahedron::cheat(int num)
{
	if(num > 0 && num < numSides){
		setDie(num);
	}
	else{
		setDie(0);
}