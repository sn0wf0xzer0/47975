//class derived from the abstract base class Die. This die has 4 sides.
//File: Tetrahedron.h
//Author: John Palacios

#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "Die.h"

class Tetrahedron : public Die
{
private:
	int numSides;
public:
	Tetrahedron() : Die()
	{ numSides = 4; }
	//default constructor.
	int roll();
	//f(x) from abstract base class which must be defined.
	int cheat(int);
	//Standard sheater f(x).
};

#endif /* TETRAHEDRON_H */