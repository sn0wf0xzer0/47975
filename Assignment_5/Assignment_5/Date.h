//Date class: stores and displays the day, month, and year in several formats. Throws an exception if
//File: Date.h
//Author: John Palacios

#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date
{
private:
	int day;
	int month;
	string synodic;
	int year;
	void nameMonth(int);
public:
	Date()
	{ day = 1, month = 1, year = 1;}
	Date(int d, int m, int y)
	{ setDay(d), setMonth(m), setYear(y);}
	~Date();
	class InvalidDay
	{};
	class InvalidMonth
	{};
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	//date in form: mm/dd/yyyy.
	void dispNumDate();
	//date in form: month day, year.
	void dispMonDate();
	//date in form: day month year.
	void dispDayDate();
};

#endif /* DATE_H */