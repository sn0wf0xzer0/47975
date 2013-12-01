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
	//Now to try some slightly dark arts...
	/*SearchableVector<Space> *testOne;
	testOne = new SearchableVector<Space> [root];
	for(int i = 0; i < root; i++){
		testOne[i] = SearchableVector<Space>(root);
		for(int j = 0; j < root; j++){
			cout << testOne[i].pop_back();
		}
	}
	for(int i = 0; i < root; i++){
		for(int j = 0; j < root; j++){
			testOne[i].push_back(Space(' '));
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		testOne[i].operator[](j).flipSpace(' ');
		}
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		cout << testOne[i].operator[](j) << "|";
		}
		cout << endl;
	}*/
	cout << "Test two contains...\n";
	Board testTwo(3);
	testTwo.showBoard();
	cout << "Test concluded.\n";
	//Game::play();
	return 0;
}