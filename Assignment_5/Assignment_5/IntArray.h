// Modified IntArray header file; now throws an exception instead of simply aborting the program.
//
#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray
{
private:
   int *aptr;                     // Pointer to the array
   int arraySize;                 // Holds the array size
public:
	//Exception class.
	class OutOfBounds
	{
	private:
		bool upper;		//If out of bounds above array size, true.
	public:
		OutOfBounds(bool dir)
		{ upper = dir; }
		bool getDir()
		{ return upper; }
	};
   IntArray(int);                 
   IntArray(const IntArray &);    
   ~IntArray();                   
   int size() const               
      { return arraySize; }
   int &operator[](const int &); 
};
#endif