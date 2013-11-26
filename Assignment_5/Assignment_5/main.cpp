//Assignment 5 main file: Gaddis Seventh Edition, chapter 16
//File: Main.cpp
//Author: John Palacios


#include "IntArray.h"
#include "Date.h"
#include "SearchableVector.h"
#include <iostream>
using namespace std;

void Menu();
int getN();
void def(int);
void problem1();
void dispValue(IntArray);
bool validateComm(string);
void dispSubMenu1();
void problem2();
void problem3();
template <class T>
void dispValue1(SimpleVector<T>);
void dispSubMenu2();
template <class T>
void mutateSeq(SimpleVector<T> &);
bool validateComm1(string);
void problem4();
template <class T>
void dispValue1(SearchableVector<T> &);
template <class T>
void mutateSeq(SearchableVector<T> &);
void dispSubMenu3();

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
    cout<<"Type 2 for problem 2: Gaddis Chapter 16, #1"<<endl;
    cout<<"Type 3 for problem 3: Gaddis Chapter 16, #8"<<endl;
    cout<<"Type 4 for problem 4: Gaddis Chapter 16, #9"<<endl;
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
	cout<<"In problem # 2: Gaddis Chapter 16, #1"<<endl<<endl;
	bool goodDate = false;
	string reply;
	int y;
	int m;
	int d;

	cout << "This option test drives a class which handles date\n"
		<< "storage and display in three formats. If an invalid\n"
		<< "day or month are entered; the object should throw an\n"
		<< "exception. Please follow the prompts as they appear,\n"
		<< "thank you.\n";
	do{
		do{
			cout << "Please enter an integral year: ";
			cin >> y;
			cout << "Please enter an integral month: ";
			cin >> m;
			cout << "Please enter an integral day: ";
			cin >> d;
			try {
				Date userDate(d, m, y);
				cout << "Numerical date format: ";
				userDate.dispNumDate();
				cout << "Month first format: ";
				userDate.dispMonDate();
				cout << "Day first format: ";
				userDate.dispDayDate();
			}
			catch(Date::InvalidDay){
				cout << "The day entered was not valid.\n";
			}
			catch(Date::InvalidMonth){
				cout << "The month entered was not valid.\n";
			}
			goodDate = true;
		} while (goodDate = false);
		cout << "Would you like to run this test again?\n"
			<< "Type anything starting with y to run again.\n";
			cin.ignore();
		getline(cin, reply);
	} while (tolower(reply[0]) == 'y');
}

void problem3(){
	cout<<"In problem # 3: Gaddis Chapter 16, #8"<<endl<<endl;
	int num;
	bool goodNum = true;
	string reply;

	cout << "This option drives a modified class template which emulates\n"
		<< "the behavior of the STL Vector class. Please follow the\n"
		<< "prompts as they appear, thank you.\n"
		<< "How many elements would you like to generate?\n";
		
		//Set up the SimpleVector object.
		do{
			cin >> num;
			if(num < 0){
				cout << "Please enter a value greater than zero.\n";
				goodNum = false;
			}
		} while (goodNum == false);

		//Initialize internal array with a recursively defined sequence.
		SimpleVector<int> list(num);
		for(int i = 0; i < num; i++){
			if(i == 0 || i == 1){
				list[i] = 1;
			}
			else
				list[i] = list[i - 1] + list[i - 2];
		}
		
		do{
		cout << "There are now " << list.size() << " integral values in your sequence.\n";

		//Give the user the oprotunity to cause an exception to be thrown and recover.
		dispValue1(list);
		//now to test pop_back and push_back.
		mutateSeq(list);
		cout << "Would you like to return to the main menu?\n"
			<< "Type anything starting with y to return to main menu.\n";
		getline(cin, reply);
		} while (tolower(reply[0]) != 'y');

		
}

template <class T>
void dispValue1(SimpleVector<T> sequence)
{
	int pos = 0;
	string command;
	char beep = 7;
	cin.ignore();

	do{
		try{
			cout << "Value at " << pos + 1 << " is: " << sequence[pos] << endl;
		}
		catch (SimpleVector<T>::OutOfBounds err)
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

		if(tolower(command[0]) == 'n'){
				pos++;
		}

		if(tolower(command[0]) == 'b'){
				pos--;
		}

		if(tolower(command[0]) == 'd'){
			cout << "You typed [" << command << "] to return to main menue.\n";
		} 
	}while (tolower(command[0]) != 'd');
}

template <class T>
void mutateSeq(SimpleVector<T> &sequence)
{
	string command;
	T val;
	do{
		do{
			dispSubMenu2();
			getline(cin, command);
		} while (validateComm1(command) == false);

		switch(tolower(command[0])){
		case 'r':
			sequence.pop_back();
			break;
		case 'a':
			cout << "Please enter the value you would like to push_back.\n";
			cin >> val;
			sequence.push_back(val);
			break;
		case 'd':
			cout << "You typed [" << command << "] to return to main menue.\n";
			break;
		}
	} while (tolower(command[0]) != 'd');

}

void dispSubMenu2()
{
	cout << "Type [remove] to pop_back last entry.\n"
	<< "Type [add] to push_back last entry.\n"
	<< "Type [done] when you would like to return to previous menue.\n";
}

bool validateComm1(string comm)
{
	bool goodComm = false;

	if(tolower(comm[0]) == 'r'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'a'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'd'){
		goodComm = true;
	}

	return goodComm;
}

void problem4(){
        cout<<"In problem # 4: Gaddis Chapter 16, #9"<<endl<<endl;
		int num;
		bool goodNum = true;
		string reply;

		cout << "This option tests an object of class SearchableVector.\n"
			<< "Please follow the prompts as they appear, thank you.\n"
			<< "How many elements would you like to generate?\n";
		
		//Set up the SearchableVector object.
		do{
			cin >> num;
			if(num < 0){
				cout << "Please enter a value greater than zero.\n";
				goodNum = false;
			}
		} while (goodNum == false);

		//Initialize internal array with a recursively defined sequence.
		SearchableVector<int> list(num);
		for(int i = 0; i < num; i++){
			if(i == 0 || i == 1){
				list[i] = 1;
			}
			else
				list[i] = list[i - 1] + list[i - 2];
		}
		for(int i = 0; i < list.size(); i++){
		cout << list[i] << " ";
	}
		do{
		cout << "There are now " << list.size() << " integral values in your sequence.\n";

		////Give the user the oprotunity to cause an exception to be thrown and recover.
		dispValue1(list);
		////now to test pop_back and push_back.
		mutateSeq(list);
		cout << "Would you like to return to the main menu?\n"
			<< "Type anything starting with y to return to main menu.\n";
		getline(cin, reply);
		} while (tolower(reply[0]) != 'y');
}

template <class T>
void dispValue1(SearchableVector<T> &sequence)
{
	int pos = 0;
	string command;
	char beep = 7;
	cin.ignore();

	do{
		try{
			cout << "Value at " << pos + 1 << " is: " << sequence[pos] << endl;
		}
		catch (SearchableVector<T>::OutOfBounds err)
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

		if(tolower(command[0]) == 'n'){
				pos++;
		}

		if(tolower(command[0]) == 'b'){
				pos--;
		}

		if(tolower(command[0]) == 'd'){
			cout << "You typed [" << command << "] to return to main menue.\n";
		} 
	}while (tolower(command[0]) != 'd');
}

template <class T>
void mutateSeq(SearchableVector<T> &sequence)
{
	string command;
	T val;
	do{
		do{
			dispSubMenu3();
			getline(cin, command);
		} while (validateComm2(command) == false);

		switch(tolower(command[0])){
		case 'r':
			sequence.pop_back();
			break;
		case 'a':
			cout << "Please enter the value you would like to push_back.\n";
			cin >> val;
			sequence.push_back(val);
			cin.ignore();
			break;
		case 'd':
			cout << "You typed [" << command << "] to return to main menue.\n";
			break;
		case 'f':
			cout << "Please enter the value you would like to find.\n";
			cin >> val;
			if(sequence.findItem(val) == -1){
				cout << "That item was not found...\n";
			}
			else
				cout << "Item found at index: " << sequence.findItem(val) << endl;
			cin.ignore();
			break;
		}
	} while (tolower(command[0]) != 'd');

}

void dispSubMenu3()
{
	cout << "Type [remove] to pop_back last entry.\n"
	<< "Type [add] to push_back last entry.\n"
	<< "Type [find] to find the index of an item.\n"
	<< "Type [done] when you would like to return to previous menue.\n";
}

bool validateComm2(string comm)
{
	bool goodComm = false;

	if(tolower(comm[0]) == 'r'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'a'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'f'){
		goodComm = true;
	}
	if(tolower(comm[0]) == 'd'){
		goodComm = true;
	}

	return goodComm;
}

void def(int inN){
        cout<<"You typed "<<inN<<" to exit the program"<<endl;
}