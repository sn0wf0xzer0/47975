//CSC 17A 47975 final.
//File: main
//Author: John Palacios

#include "Prob1Random.h"
#include "Prob2Sort.h"
#include "Prob3TableInherited.h"
#include "SavingsAccount.h"
#include "Employee.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void Menu();
int getN();
void def(int);
void problem1();
void problem2();
void problem3();
void problem4();
void problem5();

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
        case 5:    problem5();break;
        default:   def(inN);}
    }while(inN>=1&&inN<=6);
    return 0;
}

void Menu(){
    cout<<"Menu for the Final"<<endl;
    cout<<"Type 1 for problem 1"<<endl;
    cout<<"Type 2 for problem 2"<<endl;
    cout<<"Type 3 for problem 3"<<endl;
    cout<<"Type 4 for problem 4"<<endl;
    cout<<"Type 5 for problem 5"<<endl;
    cout<<"Type anything else to exit.\n"<<endl;
}

int getN(){
        int inN;
        cin>>inN;
        return inN;
}

void problem1(){
        cout<<"In problem # 1"<<endl<<endl;
		string reply;
		cin.ignore();
		cout << "This option utilizes a templated class to return a random element\n"
			<< "from a given array of any primitive type. Would you like to\n"
			<< "continue? Type 'y' to continue.\n";
		getline(cin, reply);
		if(tolower(reply[0]) == 'y'){
		int *frequency;
		char *mirrorSet;
		char n = 5;
		char randomSequence [] = {16, 34, 57, 79, 122};
		int steps = 100000;
		Prob1Random<char> a(n,randomSequence);

		for(int i = 0; i < steps; i++){
			a.randFromSet();
		}

		frequency = a.getFreq();
		mirrorSet = a.getSet();
		
		cout << "Statistical data concerning performance of object:\n";
		for(int i = 0; i < n; i++){
			cout << static_cast<int>(mirrorSet[i]) << " occured " << frequency[i] << " times.\n";
		}

		cout << "The total number of random numbers is " << a.getNumRand() << endl;
		}
		else
			cout << "Returning to main menu...\n";
}

void problem2(){
        cout<<"In problem # 2"<<endl<<endl;
		cout << "Problem 2 utilizes an object of the templated class\n"
			<< "Prob2Sort<char> to sort a list of char arrays given some\n"
			<< "index to sort by and ascending or decending order. This\n"
			<< "solution also takes equal values for char arrays at the\n"
			<< "given index into consideration and then checks the next\n"
			<< "value to determine if there is a better way to arrange\n"
			<< "The values at output, and as a result; the lists are better\n"
			<< "sorted.\n";

	Prob2Sort<char> rc;
	bool ascending=true;
	ifstream infile;
	infile.open("Problem2.txt",ios::in);
	char *ch2=new char[10*16];
	char *ch2p=ch2;
	while(infile.get(*ch2)){cout<<*ch2;ch2++;}
	infile.close();
	cout<<endl;
	cout<<"Sorting on which column?"<<endl;
	int column;
	cin>>column;
	char **zc=rc.sortArray(ch2p,10,16,column,ascending);
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++){
			cout<<zc[i][j];
		}
		cout << endl;
	}
	for(int i = 0; i < 10; i++){
		delete [] zc[i];
	}
	delete []zc;
	zc = 0;
	cout<<endl;
}

void problem3(){
        cout<<"In problem # 3"<<endl<<endl;
		cout << "This solution utilizes an inherited templated class to create\n"
			<< "a table of values of the given type. I am using a two dimensional\n"
			<< "dynamic array to represent the base table and the augmented table\n"
			<< "because it allows for intuitive interaction with the data construct\n"
			<< "and minimizes the appearance of arcane code.\n";
		int rows = 5;
		int cols = 6;
		Prob3TableInherited<int> table("Problem3.txt", rows, cols);
		int **sheet = table.getAugTable();
		for(int i = 0; i < rows + 1; i++){
			for(int j = 0; j < cols + 1; j++){
				cout << sheet[i][j] << " ";
			}
			cout << endl;
		}
}

void problem4(){
        cout<<"In problem # 4"<<endl<<endl;
		cout << "Problem 4 tests a class that is to emulated a savings\n"
			<< "acount. Transactions of zero dollars or that would result\n"
			<< "in a negative balance are not counted in deposits or\n"
			<< "withdraws.\n";
		srand(static_cast<unsigned>(time(0)));
		SavingsAccount test(float(rand() % 500) * (rand() % 3 - 1));
		for(int i = 0; i < 100; i++){
			test.transaction(float(rand() % 500) * (rand() % 3 - 1));
		}
		test.toString();
		cout << setprecision(2) << fixed
			<< "Balance after 7 years given 10% interest is: " << test.total(0.1f, 7) << endl;
}

void problem5(){
        cout<<"In problem # 5"<<endl<<endl;
	Employee Mark("Mark","Boss",215.50);
	Mark.setHoursWorked(-3);
	Mark.toString();
	Mark.calculatePay(Mark.setHourlyRate(20.0),
		Mark.setHoursWorked(25));
	Mark.toString();
	Mark.calculatePay(Mark.setHourlyRate(40.0),
		Mark.setHoursWorked(25));
	Mark.toString();
	Mark.calculatePay(Mark.setHourlyRate(60.0),
		Mark.setHoursWorked(25));
	Mark.toString();

	Employee Mary("Mary","VP",50.0);
	Mary.toString();
	Mary.calculatePay(Mary.setHourlyRate(50.0),
		Mary.setHoursWorked(40));
	Mary.toString();
	Mary.calculatePay(Mary.setHourlyRate(50.0),
		Mary.setHoursWorked(50));
	Mary.toString();
	Mary.calculatePay(Mary.setHourlyRate(50.0),
		Mary.setHoursWorked(60));
	Mary.toString();
	//And now I am out of time...
}

void def(int inN){
        cout<<"You typed "<<inN<<" to exit the program"<<endl;
}