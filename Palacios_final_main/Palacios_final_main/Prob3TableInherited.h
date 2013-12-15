//Templated class inherited from Prob3Table class.

#ifndef PROB3TABLEINHERITED_H
#define PROB3TABLEINHERITED_H

#include "Prob3Table.h"

template <class T>
class Prob3TableInherited : public Prob3Table<T>
{
protected:
	T **augTable;
public:
	Prob3TableInherited(char *, int, int);
	~Prob3TableInherited();
	T **getAugTable() const
	{ return  augTable; }
};

template <class T>
Prob3TableInherited<T>::Prob3TableInherited(char *fileName, int rows, int cols) : Prob3Table<T>(fileName, rows, cols)
{
	augTable = new T* [rows + 1];
	for(int i = 0; i < rows + 1; i++){
		augTable[i] = new T [cols + 1];
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			augTable[i][j] = this->table[i][j];
		}
		augTable[i][cols] = this ->rowSum[i];
	}
	for(int k = 0; k < cols; k++){
		augTable[rows][k] = this ->colSum[k];
	}
	augTable[rows][cols] = this ->getGrandTotal();
}

template <class T>
Prob3TableInherited<T>::~Prob3TableInherited()
{
	for(int i = 0; i < rows + 1; i++){
		delete [] augTable[i];
	}
	delete [] augTable;
	augTable = 0;
}
#endif /* PROB3TABLEINHERITED_H */