//Implementation file for the SavingsAccount class utilized in problem 4.

#include "SavingsAccount.h"
#include <iostream>
#include <string>
using namespace std;

SavingsAccount::SavingsAccount(float init)
{
	if(init > 0){
		balance = init;
	}
	else{
		balance = 0;
	}
	freqWithDraw = 0;
	freqDeposit = 0;
}

float SavingsAccount::deposit(float amt)
{
	freqDeposit++;
	return amt;
}

float SavingsAccount::withdraw(float amt)
{	
	if(fabs(amt) > balance){
		cout << "Withdraw Not Allowed\n";
		return 0.0;
	}
	else{
	freqWithDraw++;
	return amt;
	}
}

void SavingsAccount::transaction(float amt)
{
	if(amt == 0){
		
	}
	if(amt > 0){
		balance += deposit(amt);
	}
	if(amt < 0){
		balance += withdraw(amt);
	}
}

void SavingsAccount::toString()
{
	cout << "Balance:   $" << balance << endl;
	cout << "Withdraws: " << freqWithDraw << endl;
	cout << "Deposits:  " << freqDeposit << endl;
}

float SavingsAccount::total(float rate, int years)
{
	float interest = 1;
	for(int i = 0; i < years; i++){
		interest *= (1 + rate);		//test value (0.1, 7) = 1.94871717;
	}
	return balance * interest;
}

float SavingsAccount::totalRecursive(float rate, int yrs)
{
	/*if(rate < 1) rate += 1;
	if(yrs == 1){
		return balance *= (1 + rate);
	}
	else{
		rate *= totalRecursive(rate, --yrs); 
	} out of time*/
	return 0.0;
}