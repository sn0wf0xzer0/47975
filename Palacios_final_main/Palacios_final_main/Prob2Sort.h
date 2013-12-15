//Prob2Sort header file.

#ifndef PROB2SORT_H
#define PROB2SORT_H

template <class T>
class Prob2Sort
{
private:
	int *index;
public:
	Prob2Sort(){ index = NULL; }
	~Prob2Sort(){ delete [] index; }
	T *sortArray(const T*, int, bool);
	T **sortArray(const T*, int, int, int, bool);
};

template <class T>
T *Prob2Sort<T>::sortArray(const T *arr, int size, bool ascend)
{
	int startScan;			//This is the current index to place sorted value
	int srtdIndex;			//thie is the index of the current extrema value
	T extremaValue;			//this is the current extrema value.

	T *srtedArr = new T [size];
	for(int i = 0; i < size; i++){
		srtedArr[i] = arr[i];
	}

	if(!ascend){
		for (startScan = 0; startScan < (size - 1); startScan++)
		{
			srtdIndex = startScan;
			extremaValue = srtedArr[startScan];

			for (int i = startScan + 1; i < size; i++)
			{
				if (srtedArr[i] < extremaValue)
				{
					extremaValue = srtedArr[i];
					srtdIndex = i;
				}
			}
			srtedArr[srtdIndex] = srtedArr[startScan];
			srtedArr[startScan] = extremaValue;
		}
	}
	else{
		for (startScan = 0; startScan < (size - 1); startScan++)
		{
			srtdIndex = startScan;
			extremaValue = srtedArr[startScan];

			for (int i = startScan + 1; i < size; i++)
			{
				if (srtedArr[i] > extremaValue)
				{
					extremaValue = srtedArr[i];
					srtdIndex = i;
				}
			}
			srtedArr[srtdIndex] = srtedArr[startScan];
			srtedArr[startScan] = extremaValue;
		}
	}

	return srtedArr;
}

template <class T>
T **Prob2Sort<T>::sortArray(const T *arr, int rows, int cols, int swingCol, bool ascend)
{
	int startScan;			//This is the current index to place sorted value
	int srtdIndex;			//thie is the index of the current extrema value
	T *extremaValue;		//this is the current extrema value array.
	int swing = swingCol - 1;

	T **srtedArr = new T* [rows];
	for(int i = 0; i < rows; i++){
		srtedArr[i] = new T [cols];
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			srtedArr[i][j] = arr[i * cols + j];
		}
	}

	if(!ascend){
		for (startScan = 0; startScan < (rows - 1); startScan++)
		{
			srtdIndex = startScan;
			extremaValue = srtedArr[startScan];

			for (int i = startScan + 1; i < rows; i++)
			{
				if(srtedArr[i][swing] < extremaValue[swing])
				{
					extremaValue = srtedArr[i];
					srtdIndex = i;
				}
				if(srtedArr[i][swing] == extremaValue[swing]){
					if(swing > 0){
						if(srtedArr[i][swing - 1] < extremaValue[swing - 1]){
							extremaValue = srtedArr[i];
							srtdIndex = i;
						}
					}
					else if(swing < cols){
						if(srtedArr[i][swing + 1] < extremaValue[swing + 1]){
							extremaValue = srtedArr[i];
							srtdIndex = i;
						}
					}
				}
			}
			srtedArr[srtdIndex] = srtedArr[startScan];
			srtedArr[startScan] = extremaValue;
		}
	}
	else{
		for (startScan = 0; startScan < (rows - 1); startScan++)
		{
			srtdIndex = startScan;
			extremaValue = srtedArr[startScan];

			for (int i = startScan + 1; i < rows; i++)
			{
				if(srtedArr[i][swing] > extremaValue[swing])
				{
					extremaValue = srtedArr[i];
					srtdIndex = i;
				}
				if(srtedArr[i][swing] == extremaValue[swing]){
					if(swing > 0){
						if(srtedArr[i][swing - 1] > extremaValue[swing - 1]){
							extremaValue = srtedArr[i];
							srtdIndex = i;
						}
					}
					else if(swing < cols){
						if(srtedArr[i][swing + 1] > extremaValue[swing + 1]){
							extremaValue = srtedArr[i];
							srtdIndex = i;
						}
					}
				}
			}
			srtedArr[srtdIndex] = srtedArr[startScan];
			srtedArr[startScan] = extremaValue;
		}
	}

	return srtedArr;

}
#endif /* PROB2SORT_H */