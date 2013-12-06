//class derived from the abstract base class Die. This die has 10 sides.
//File: Decahedron.h
//Author: John Palacios

#ifndef DECAHEDRON_H
#define DECAHEDRON_H

#include "Die.h"

class Decahedron : public Die
{
private:
	int numSides;
public:
	Decahedron() : Die()
	{ numSides = 10; }
	//default constructor.
	int roll();
	//f(x) from abstract base class which must be defined.
	int cheat(int);
	//Standard sheater f(x).
};

#endif /* DECAHEDRON_H */