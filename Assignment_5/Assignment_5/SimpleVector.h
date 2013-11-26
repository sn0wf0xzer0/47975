// SimpleVector class template
#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H
#include <new>       //Needed for bad_alloc exception
using namespace std;

template <class T>
class SimpleVector
{
private:
   T *aptr;         //points to allocated array of T type
   int arraySize;   //Number of elements in the array
   int maxSize;		//Total Maximum number of elements available.

public:
   SimpleVector()
      { aptr = 0; arraySize = 0;}
   SimpleVector(int);
   //Copy constructor.
   SimpleVector(const SimpleVector &);
   ~SimpleVector();
   //Memory allocation exception class.
   class AllocError
   { };
	//Array bounds checking exception class.
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
   int size() const
      { return arraySize; }
   //Returns value of element at position.
   T getElementAt(int position);
   // Overloaded [] operator.
   T &operator[](const int &);
   void push_back(T);
   void pop_back();
};

template <class T>
SimpleVector<T>::SimpleVector(int s)
{
   arraySize = s;
   maxSize = s;
   //Attempt to allocate mem.
   try
   {
      aptr = new T [s];
   }
   catch (bad_alloc)
   {
	   //If fail, tell the program.
      throw AllocError();
   }

   //Initialize the array with something boring but safe.
   for (int count = 0; count < arraySize; count++)
      *(aptr + count) = 0;
}

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
   arraySize = obj.arraySize;

   aptr = new T [arraySize];
   if (aptr == 0)
      throw AllocError();
      
   //Copy the elements of obj's array.
   for(int count = 0; count < arraySize; count++)
      *(aptr + count) = *(obj.aptr + count);
}

template <class T>
SimpleVector<T>::~SimpleVector()
{
   if (arraySize > 0)
      delete [] aptr;
}

template <class T>
T SimpleVector<T>::getElementAt(int sub)
{
	//Prevent accessing memory outside of the array
	//Before the system complains and shuts down the
	//Program.
   if (sub < 0)
      throw OutOfBounds(false);
   if(sub >= arraySize)
	   throw OutOfBounds(true);

   return aptr[sub];
}

template <class T>
T &SimpleVector<T>::operator[](const int &sub)
{
	//Prevent accessing memory outside of the array
	//Before the system complains and shuts down the
	//Program.
  if (sub < 0)
      throw OutOfBounds(false);
   if(sub >= arraySize)
	   throw OutOfBounds(true);

   return aptr[sub];
}

template <class T>
void SimpleVector<T>::push_back(T val)
{
	if(arraySize++ == maxSize){
	T *temp;

	temp = new T [arraySize];

	for(int i = 0; i < arraySize; i++){
		*(temp + i) = *(aptr + i);
	}
	
	delete [] aptr;
	
	maxSize *= 2;

	aptr = new T [maxSize];
	for(int i = 0; i < arraySize - 1; i++){
		*(aptr + i) = *(temp + i);
	}
	aptr[arraySize - 1] = val;

	delete [] temp;
	}
	else{
		aptr[arraySize - 1] = val;
	}
}

template <class T>
void SimpleVector<T>::pop_back()
{
	--arraySize;
}

#endif /* SIMPLEVECTOR_H */ 