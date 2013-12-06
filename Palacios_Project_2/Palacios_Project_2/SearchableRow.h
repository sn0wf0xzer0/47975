//The searchable functionality may be useful for making AI moves...

#ifndef SEARCHABLEROW_H
#define SEARCHABLEROW_H
#include "ObjectRow.h"

template <class T>
class SearchableRow : public ObjectRow<T>
{
private:
	//creates a copy of ObjectRow::dynTArr, returning a pointer to that
	//array.
	T *copyArray();
	//Sorts array to facilitate binary search.
	T *sortArray();
public:
	//Just using base class constructor.
	SearchableRow() : ObjectRow<T>()
	{ }
	//Just passing the size to the base class constructor.
	SearchableRow(int size) : ObjectRow<T>(size)
	{ }
	//Copy constructor
	SearchableRow(const SearchableRow &);
	//find item using binary search, returns -1 when unsuccessful.
	//Does not rearange elements, not useful for finding actuall index of object.
	int binSearch(const T) const;
	//Find item using linear search, returns -1 when unsuccessful.
	//Does not rearange elements.
	int linSearch(const T);
};

template <class T>
SearchableRow<T>::SearchableRow(const SearchableRow &obj) :
ObjectRow<T>(obj.size())
{
	for(int count = 0; count < this->size(); count++)
		this->operator[](count) = obj[count];
}

template <class T>
int SearchableRow<T>::binSearch(const T item) const
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
T *SearchableRow<T>::copyArray()
{
	T *copy;
	copy = new T [this->size()];

	for(int i = 0; i < this->size(); i++){
		*(copy + i) = this->operator [](i);
	}

	return copy;
}

template <class T>
T *SearchableRow<T>::sortArray()
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

template <class T>
int SearchableRow<T>::linSearch(const T item)
{
	for (int i = 0; i < this->size(); i++){
		if (getElementAt(i) == item){
			return i;
		}
	}
	return -1;
}
#endif /* SEARCHABLEROW_H */