//
//
//
//

#include "Game.h"
#include "SearchableVector.h"
#include <iostream>
using namespace std;

int main()
{
	//Now to try some slightly dark arts...
	int count = 0;
	SearchableVector<Space> *testOne[3] =
	{
		new SearchableVector<Space>(3),
		new SearchableVector<Space>(3),
		new SearchableVector<Space>(3)
	};

	cout << "Test one contains...\n";
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		testOne[i]->operator[](j).flipSpace(49 + count);
		count++;
		}
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		cout << testOne[i]->operator[](j) << " ";
		}
		cout << endl;
	}
	cout << "Test concluded.\n";
	//Game::play();
	return 0;
}