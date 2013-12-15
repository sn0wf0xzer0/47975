//Specification file for the SavingsAccount class.

#include <cmath>
using namespace std;

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

class SavingsAccount
{
private:
	int   freqWithDraw;                  //Property
	int   freqDeposit;                   //Property
	float balance;                       //Property
	float withdraw(float);               //Utility Procedure
	float deposit(float);                //Utility Procedure
public:
	SavingsAccount(float);               //Constructor
	void  transaction(float);            //Procedure
	float total(float=0,int=0);	         //Savings Procedure
	float totalRecursive(float=0,int=0);
	void toString();             //Output Properties by way of returning a 2d char array.
};

#endif /* SAVINGSACCOUNT_H */