//Assignment 5 main file: Gaddis Seventh Edition, chapter 16
//File: Main.cpp
//Author: John Palacios


#include "IntArray.h"
#include <string>
#include <iostream>
using namespace std;

void Menu();
int getN();
void def(int);
void problem1();
void dispValue(IntArray sequence);
bool validateComm(string comm);
void dispSubMenu1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();

int main(int argv,char *argc[]){
    int inN;
    do{
        Menu();
        inN=getN();
        switch(inN){
        case 1:    problem1();break;
        case 2:    problem2();break;
        case 3:    problem3();break;
        case 4:    problem4();break;
        default:   def(inN);}
    }while(inN>=1&&inN<=6);
    return 0;
}

void Menu(){
    cout<<"Menu for Assignment 5"<<endl;
	cout<<"Type 1 for problem 1: Gaddis Chapter 16, #6"<<endl;
    cout<<"Type 2 for problem 2: Gaddis Chapter 16, #"<<endl;
    cout<<"Type 3 for problem 3: Gaddis Chapter 16, #"<<endl;
    cout<<"Type 4 for problem 4: Gaddis Chapter 16, #"<<endl;
    cout<<"Type anything else to exit \n"<<endl;
}

int getN(){
        int inN;
        cin>>inN;
        return inN;
}

void problem1(){
        cout<<"In problem # 1: Gaddis Chapter 16, #6"<<endl<<endl;
		int num;					//arraySize passed to IntArray object.
		bool goodNum = true;		//Minimal user input validation flag.

		cout << "This program drives a class which mimics an array with built\n"
			<< "in \"bounds checking\" capability; an object of this class will\n"
			<< "Throw an exception if an element is accessed which is outside\n"
			<< "The size of the array. Please follow the prompts as they appear,\n"
			<< "Thank you.\n\n"
			<< "How many elements would you like to generate?\n";
		
		//Set up the IntArray object.
		do{
			cin >> num;
			if(num < 0){
				cout << "Please enter a value greater than zero.\n";
				goodNum = false;
			}
		} while (goodNum == false);

		//Initialize internal array with a recursively defined sequence.
		IntArray list(num);
		for(int i = 0; i < num; i++){
			if(i == 0 || i == 1){
				list[i] = 1;
			}
			else
				list[i] = list[i - 1] + list[i - 2];
		}

		cout << "There are now " << num << " integral values in your sequence.\n";

		//Give the user the oprotunity to cause an exception to be thrown and recover.
		dispValue(list);

}

void dispValue(IntArray sequence)
{
	int pos = 0;
	string command;
	char beep = 7;
	cin.ignore();

	do{
		try{
			cout << "Value at " << pos + 1 << " is: " << sequence[pos] << endl;
		}
		catch (IntArray::OutOfBounds err)
		{
			if(err.getDir()){
				cout << beep << "There are no more entries this way, please type [back] to see\n"
					<< "next entry or [done] if done.\n";
			}
			else{
				cout << beep << "There are no more entries this way, please type [next] to see\n"
					<< "next entry or [done] if done.\n";
			}
				
		}
		do{
			dispSubMenu1();
			getline(cin, command);
		} while (validateComm(command) == false);

		if(tolower(command[0] == 'n')){
				pos++;
		}

		if(tolower(command[0] == 'b')){
				pos--;
		}

		if(tolower(command[0] == 'd')){
			cout << "You typed [" << command << "] to return to main menue.\n";
		} 
	}while (tolower(command[0] != 'd'));
}

bool validateComm(string comm)
{
	bool goodComm = false;

	if(tolower(comm[0]) == 'b'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'n'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'd'){
		goodComm = true;
	}

	return goodComm;
}

void dispSubMenu1()
{
	cout << "Type [back] to see the previous entry.\n"
		<< "Type [next] to see the next entry.\n"
		<< "Type [done] when you would like to return to the main menue.\n";
}

void problem2(){
        cout<<"In problem # 2"<<endl<<endl;
}

void problem3(){
        cout<<"In problem # 3"<<endl<<endl;
}

void problem4(){
        cout<<"In problem # 4"<<endl<<endl;
}

void def(int inN){
        cout<<"You typed "<<inN<<" to exit the program"<<endl;
}