//Implementation of Date class, nothing fancy.
//File: Date.cpp
//Author: John Palacios

#include "Date.h"
#include <iostream>
using namespace std;

Date::~Date()
{
	//destructor does nothing.
}

void Date::setDay(int d)
{
	if(d < 1 || d > 31){
		throw InvalidDay();
	}
	else
	day = d;
}

void Date::setMonth(int m)
{
	if(m < 1 || m > 12){
		throw InvalidMonth();
	}
	else
		month = m;
	nameMonth(m);
}

void Date::setYear(int y)
{
	if(y < 1){
		year = 1;
	}
	else
		year = y;
}

void Date::nameMonth(int m)
{
	char s = m + 48;
	switch(s){
		case '1':
			synodic = "January";
		case '2':
			synodic = "Febuary";
		case '3':
			synodic = "March";
		case '4':
			synodic = "April";
		case '5':
			synodic = "May";
		case '6':
			synodic = "June";
		case '7':
			synodic = "July";
		case '8':
			synodic = "August";
		case '9':
			synodic = "September";
		case ':':
			synodic = "October";
		case ';':
			synodic = "November";
		case '<':
			synodic = "December";
	}
}

void Date::dispNumDate()
{
	cout << day << "/" << month << "/" << year << endl;
}

void Date::dispMonDate()
{
	cout << synodic << " " << day << ", " << year << endl;
}

void Date::dispDayDate()
{
	cout << day << " " << synodic << " " << year << endl;
}