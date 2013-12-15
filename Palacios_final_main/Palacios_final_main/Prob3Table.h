//Header file for templated class Prob3Table.

#include <fstream>
using namespace std;

#ifndef PROB3TABLE_H
#define PROB3TABLE_H

template <class T>
class Prob3Table
{
protected:
	int rows;
	int cols;
	T *rowSum;
	T *colSum;
	T **table;
	T grandTotal;
	void calcTable();
public:
	Prob3Table(char *, int, int);
	~Prob3Table();
	int getRows()
	{ return rows; }
	int getCols()
	{ return cols; }
	const T **getTable()
	{ return table; }
	const T *getRowSum()
	{ return rowSum; }
	const T *getColSum()
	{ return colSum; }
	T getGrandTotal()
	{ return grandTotal; }
};

template <class T>
Prob3Table<T>::Prob3Table(char *fileName, int numRows, int numCols)
{
	rows = numRows;
	cols = numCols;
	int r = 0;
	int c = 0;
	rowSum = new T [rows];
	colSum = new T [cols];
	T value;
	
	table = new T* [rows];
	for(int i = 0; i < rows; i++){
		table[i] = new T [cols];
	}
	ifstream infile;
	infile.open(fileName, ios::in);
	while(infile >> value && r < rows){
		table[r][c] = value;
		c++;
		if(c == cols){
			r++;
			c = 0;
		}
	}
	infile.close();
	this->calcTable();
}

template <class  T>
void Prob3Table<T>::calcTable()
{
	grandTotal = static_cast<T>(0);
	T sumR = static_cast<T>(0);
	T sumC = static_cast<T>(0);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			sumR += table[i][j];
		}
		rowSum[i] = sumR;
		sumR = static_cast<T>(0);
	}

	for(int i = 0; i < cols; i++){
		for(int j = 0; j < rows; j++){
			sumC += table[j][i];
		}
		colSum[i] = sumC;
		sumC = static_cast<T>(0);
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			grandTotal += table[i][j];
		}
	}

}

template <class T>
Prob3Table<T>::~Prob3Table()
{
	for(int i = 0; i < rows; i++){
		delete [] table[i];
	}
	delete [] table;
	delete [] rowSum;
	delete [] colSum;
	table = 0;
	rowSum = 0;
	colSum = 0;
}
#endif /* PROB3TABLE_H */