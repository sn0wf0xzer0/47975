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
	int root = 3;
	SearchableVector<Space> *testOne;
	testOne = new SearchableVector<Space> [root];
	/*for(int i = 0; i < root; i++){
		testOne[i] = SearchableVector<Space>(root);
		for(int j = 0; j < root; j++){
			cout << testOne[i].pop_back();
		}
	}
	cout << endl;*/
	for(int i = 0; i < root; i++){
		for(int j = 0; j < root; j++){
			if(j == 0)
			testOne[i].push_back(Space());
			else
				testOne[i].push_back(Space('X'));
		}
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		cout << testOne[i].operator[](j) << "|";
		}
		cout << endl;
	}
	cout << endl;
	testOne[0][0].flipSpace('H');
	testOne[1][0].flipSpace('J');
	testOne[2][0].flipSpace('K');
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		cout << testOne[i].operator[](j) << "|";
		}
		cout << endl;
	}
	//delete [] testOne;
	/*cout << "Test two contains...\n";
	Board testTwo(3);
	testTwo.showBoard();
	cout << "Test concluded.\n";*/
	//Game::play();
	return 0;
}