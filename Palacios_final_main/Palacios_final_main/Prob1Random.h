//Prob1Random header file.
//File: Prob1Random.h
//Author: John Palacios. (Origional header written by Dr. Lehr.)

#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef PROB1RANDOM_H
#define PROB1RANDOM_H

template <class T>
class Prob1Random
{
	private:
		T *set;						//The set of numbers to draw random numbers from
		int nset;					//The number of variables in the sequence
		int *freq;					//Frequency of all the random numbers returned
		int numRand;				//The total number of times the random number function is called
	public:
		Prob1Random(const char,T *);		//Constructor
		~Prob1Random();						//Destructor
		T randFromSet();					//Returns a random number from the set
		int *getFreq() const;				//Returns the frequency histogram
		T *getSet() const;					//Returns the set used
		int getNumRand() const;				//Gets the number of times randFromSet has been called
};

template <class T>
Prob1Random<T>::Prob1Random(const char num, T *vals)
{
	numRand = 0;
	nset = num;
	freq = new int [nset];
	set = new T [nset];
	srand(static_cast<unsigned>(time(0)));

	for(int i = 0; i < nset; i++){
		freq[i] = 0;
		set[i] = vals[i];
	}
}

template <class T>
Prob1Random<T>::~Prob1Random()
{
	delete [] set;
	delete [] freq;
	set = 0;
	freq = 0;
}

template <class T>
T Prob1Random<T>::randFromSet()
{
	numRand++;
	int pos = rand() % nset;
	freq[pos]++;
	return set[pos];
}

template <class T>
int *Prob1Random<T>::getFreq() const
{
	return freq;
}

template <class T>
T *Prob1Random<T>::getSet() const
{
	return set;
}

template <class T>
int Prob1Random<T>::getNumRand() const
{
	return numRand;
}

#endif /* PROB1RANDOM_H */