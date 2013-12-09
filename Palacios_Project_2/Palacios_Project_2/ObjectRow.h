// ObjectRow class template
#ifndef OBJECTROW_H
#define OBJECTROW_H

//Since this object borrows memory from the free store; I should make sure it does so properly.
//This header contains the bad_alloc error class thrown by the new opperator.
#include <new>
using namespace std;

template <class T>
class ObjectRow
{
private:
	T *dynTArr;			//points to allocated array of T type
	int arrSize;		//Number of used elements in the array
	int capacity;		//Total Maximum number of elements available.

public:
	//Default constructor simply creates an instance of this class,
	//no objects of type T are created.
	ObjectRow()
	{ dynTArr = 0; arrSize = 0, capacity = 0;}
	//Creates instance of this class allong with s type T objects.
	ObjectRow(int);
	//Your standard copy constructor.
	ObjectRow(const ObjectRow &);
	//Your standard destructor.
	~ObjectRow();
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
	{ return arrSize; }
	//Returns value of element at position.
	T getElementAt(int position);
	// Overloaded [] operator.
	T &operator[](const int &);
	//Returns the actuall number of available elements.
	int getMax() const
	{ return capacity; }
	//adds object to end of array, allocating more memory
	//if necessary.
	void push(T);
	//Decrements the size of the array, returning
	//The last element.
	T pop();
};

template <class T>
ObjectRow<T>::ObjectRow(int s)
{
	arrSize = s;
	capacity = s;
	//Attempt to allocate mem.
	try
	{
		dynTArr = new T [s];
	}
	catch (bad_alloc)
	{
		//If fail, tell the program.
		throw AllocError();
	}
}

template <class T>
ObjectRow<T>::~ObjectRow()
{
	//If the object is initialized without argument, it has size zero; and no T objects pointed to by dynTArr.
	if (arrSize > 0){
		delete [] dynTArr;
		dynTArr = 0;
	}
}

template <class T>
ObjectRow<T>::ObjectRow(const ObjectRow &obj)
{
	arrSize = obj.arrSize;

	dynTArr = new T [arrSize];
	if (dynTArr == 0)
		throw AllocError();

	//Copy the elements of obj's array.
	for(int count = 0; count < arrSize; count++)
		*(dynTArr + count) = *(obj.dynTArr + count);
}

template <class T>
T ObjectRow<T>::getElementAt(int sub)
{
	//Prevent accessing memory outside of the array
	//Before the system complains and shuts down the
	//Program.
	if (sub < 0)
		throw OutOfBounds(false);
	if(sub >= arrSize){
		//This gives the program better understanding
		//Of what is happening and allows for finer
		//handling of such problems.
		throw OutOfBounds(true);
	}
	return dynTArr[sub];
}

template <class T>
T &ObjectRow<T>::operator[](const int &sub)
{
	//Prevent accessing memory outside of the array
	//Before the system complains and shuts down the
	//Program.
	if (sub < 0)
		throw OutOfBounds(false);
	if(sub >= arrSize){
		//This gives the program better understanding
		//Of what is happening and allows for finer
		//handling of such problems.
		throw OutOfBounds(true);
	}
	return dynTArr[sub];
}

template <class T>
void ObjectRow<T>::push(T val)
{
	//The object may be initialized with zero
	//elements, and have elements added at runtime.
	//Since there are 0 elements at this time, no
	//Need to copy dynTArr objects.
	if(arrSize == 0){
		dynTArr = new T;
		dynTArr[0] = val;
		arrSize = 1;
		capacity = 1;
	}
	else if(arrSize++ == capacity){
		capacity *= 2;
		T *temp = new T [capacity];
		for(int i = 0; i < arrSize - 1; i++){
			temp[i] = dynTArr[i];
		}
		temp[arrSize - 1] = val;
		if(capacity == 2){
			delete dynTArr;
		}
		else{
			delete [] dynTArr;
		}
		dynTArr = temp;
	}
	else{
		dynTArr[arrSize - 1] = val;
	}
}

template <class T>
T ObjectRow<T>::pop()
{
	//When objects are added to dynTArr, they will overwrite these
	//unindexed objects.
	arrSize--;
	return dynTArr[arrSize - 1];
}

#endif /* OBJECTROW_H */ 