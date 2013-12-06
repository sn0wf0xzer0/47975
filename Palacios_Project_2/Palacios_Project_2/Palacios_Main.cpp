//This file simply calls Game's static play member. Currently in Alpha test phase of development.
//File: Palacios_Main.cpp
//Author: John Palacios
//

#include "Game.h"
//#include "SearchableRow.h"
#include <iostream>
using namespace std;

int main()
{
	//Space **field = new Space* [3];
	//for(int i = 0; i < 3; i++){
	//	field[i] = new Space [3];
	//}
	//for(int i = 0; i < 3; i++){
	//	for(int j = 0; j < 3; j++){
	//			field[i][j].flipSpace('X');
	//	}
	//}
	//for(int i = 0; i < 3; i++){
	//	for(int j = 0; j < 3; j++){
	//			cout << field[i][j];
	//	}
	//}
	//for(int i = 0; i < 3; i++){
	//	delete [] field[i];
	//}
	//delete [] field;
	//cout << endl << endl;

	//int root = 3;
	//SearchableRow<Space> *testOne;
	//testOne = new SearchableRow<Space> [root];
	//for(int i = 0; i < root; i++){
	//	for(int j = 0; j < root; j++){
	//		if(j == 0)
	//		testOne[i].push(Space());
	//		else
	//			testOne[i].push(Space('X'));
	//	}
	//}
	//for(int i = 0; i < 3; i++){
	//	for(int j = 0; j < 3; j++){
	//	cout << testOne[i].operator[](j) << "|";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//testOne[0][0].flipSpace('H');
	//testOne[1][0].flipSpace('J');
	//testOne[2][0].flipSpace('K');
	//for(int i = 0; i < 3; i++){
	//	for(int j = 0; j < 3; j++){
	//	cout << testOne[i][j] << "|";
	//	}
	//	cout << endl;
	//}
	//delete [] testOne;
	//cout << "Test two contains...\n";
	//Board testTwo(3);
	//testTwo.showBoard();
	//testTwo.flipSpace(7, 'J');  //Test flipspace f(x) with the SerchableVector<Space> member.
	//testTwo.flipSpace(5, 'J');
	//testTwo.flipSpace(3, 'P');
	//testTwo.showBoard();
	//testTwo.~Board();			//Now to see if the Board can safely delete the SerchableVector<Space> array.
	//cout << "Test concluded.\n"; //... and it cannot. must ask about this tomarrow. Now it is time for sleep for work tomarrow morning.
	Game::play();
	//Now to test my die classes.
	//Tetrahedron dieOne;
	//Decahedron dieTwo;
	//cout << "Die one: " << dieOne.checkDie() << "Die two: " << dieTwo.checkDie() << endl;
	//for(int i = 0; i < 10; i++){
	//	dieOne.roll();
	//	dieTwo.roll();
	//cout << "Die one: " << dieOne.checkDie() << " Die two: " << dieTwo.checkDie() << endl;
	//}
	return 0;
}