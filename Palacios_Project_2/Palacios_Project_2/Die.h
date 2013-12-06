//This abstract base class represents the concept of a die; a real world random number generator.
//File: die.h
//Author: John Palacios

#include <ctime>
#include <cstdlib>
using namespace std;

#ifndef DIE_H
#define DIE_H

class Die
{
private:
	int showing;
public:
	Die()
	{ showing = this->roll(), srand(time(0)); }
	//Default constructor.
	checkDie();
	{ return showing; }
	//Check to see which number is showing.
	void setDie(int num)
	{showing = num; }
	//set side showing to the number given.
	int roll() = 0;
	//Generates a random number and sets showing.
};

#endif /* DIE_H */