//Implementation file for the Employee class.

#include "Employee.h"
#include <iostream>
using namespace std;

Employee::Employee(char n[], char t[], float rate)
{
	int liu = 0;
	for(int i = 0; i < 20; i++){
		myName[i] = n[i];
		liu++;
	}
	myName[liu + 1] = '\0';
	liu = 0;

	for(int i = 0; i < 20; i++){
		jobTitle[i] = t[i];
		liu++;
	}
	myName[liu + 1] = '\0';

	setHourlyRate(rate);
	hoursWorked = 0;
	grossPay = 0;
	netPay = 0;
}

int Employee::setHoursWorked(int hrs)
{
	if(hrs > 0 && hrs < 84){
		hoursWorked = hrs;
		return hrs;
	}
	else{
		cout << "Unacceptable Hours Worked.\n";
		hoursWorked = 0;
		return hrs;
	}
}

float Employee::setHourlyRate(float rate)
{
	if(rate > 0 && rate < 200.00){
		hourlyRate = rate;
		return hourlyRate;
	}
	else{
		cout << "Unacceptable Hourly Rate.\n";
		hourlyRate = 0;
		return hourlyRate;
	}
}

float Employee::getGrossPay(float rate, int hrs)
{
	if(hrs <= 40){
		grossPay = hrs * rate;
		return grossPay;
	}
	if(hrs < 40 && hrs <= 50){
		grossPay = 1.5 * (hrs * rate);
		return grossPay;
	}
	if(hrs > 50){
		grossPay = 2 * (hrs * rate);
		return grossPay;
	}
	else
		cout << "Bad hours.\n";
	return 0;
}

float Employee::tax(float grsPay)
{
	if(grsPay <= 500.0){
		return 0.1 * grsPay;
	}
	if(grsPay > 500 && grsPay <= 1000.0){
		return 0.2 * grsPay;
	}
	if(grsPay > 1000.0){
		return 0.3 * grsPay;
	}
}

void Employee::toString()
{
	int i = 0;
	cout << "Employee name: ";
		while(myName[i] != '\0'){
		cout << myName[i];
		i++;
		};
		i = 0;
		cout << " Job title: ";
		while(jobTitle[i] != '\0'){
			cout << jobTitle[i];
			i++;
		};
		cout << "\nHourly rate: " << hourlyRate
		<< " Hours worked: " << hoursWorked
		<< " Gross Pay: " << grossPay
		<< " Net pay: " << netPay << endl;
}

float Employee::getNetPay(float gros)
{
	return getGrossPay(hourlyRate, hoursWorked) - tax(gros);
}

float Employee::calculatePay(float x, int y)
{
	return getNetPay(getGrossPay(setHourlyRate(x),setHoursWorked(y)));
}