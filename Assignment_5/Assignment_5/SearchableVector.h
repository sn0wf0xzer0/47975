#ifndef SEARCHABLEVECTOR_H
#define SEARCHABLEVECTOR_H
#include "SimpleVector.h"

template <class T>
class SearchableVector : public SimpleVector<T>
{
private:
	T *copyArray();
	T *sortArray();
public:
   // Default constructor
   SearchableVector() : SimpleVector<T>()
      {}
   
   // Constructor
   SearchableVector(int size) : SimpleVector<T>(size)
      { }
   
   // Copy constructor
   SearchableVector(const SearchableVector &);

   // Accessor to find an item
   int findItem(const T);
};

//*******************************************************
// Copy constructor                                     *
//*******************************************************

template <class T>
SearchableVector<T>::SearchableVector(const SearchableVector &obj) :
                     SimpleVector<T>(obj.size())
{
   for(int count = 0; count < this->size(); count++)
      this->operator[](count) = obj[count];
}

//*******************************************************
// findItem function                                    *
// This function searches for item. If item is found    *
// the subscript is returned. Otherwise -1 is returned. *
//*******************************************************

template <class T>
int SearchableVector<T>::findItem(const T item)
{
	T *srtdArr = sortArray();
	int first = 0,					//First element
       last = this->size() - 1,     //Last element
       middle,						//Mid point of search
       position = -1;				//Position of search value
   bool found = false;				//Flag

   while (!found && first <= last)
   {
      middle = (first + last) / 2;
      if (srtdArr[middle] == item)
      {
         found = true;
         position = middle;
      }
	  //Item value > than middle value?
      else if (srtdArr[middle] > item)
         last = middle - 1;
      else
         first = middle + 1;
   }
   return position;
}

template <class T>
T *SearchableVector<T>::copyArray()
{
	T *copy;
	copy = new T [this->size()];
	
	for(int i = 0; i < this->arraySize; i++){
		*(copy + i) = this->aptr[i];
	}

	return copy;
}

template <class T>
T *SearchableVector<T>::sortArray()
{
	T *srtdArr = this->copyArray();
	int size = this->size();
	int startScan;			//This is the current index to place smallest value
	int minIndex;			//thie is the index of the current smallest value
	int minValue;			//this is the current smallest value

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		minValue = srtdArr[startScan];

		for (int i = startScan + 1; i < size; i++)
		{
			if (srtdArr[i] < minValue)
			{
				minValue = srtdArr[i];
				minIndex = i;
			}
		}
		srtdArr[minIndex] = srtdArr[startScan];
		srtdArr[startScan] = minValue;
	}
	return srtdArr;
}
#endif