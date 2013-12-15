//Specification for problem 5 Employee class.

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
private:
	float tax(float);
	char   myName[20];      //Property
	char   jobTitle[20];    //Property
	float  hourlyRate;      //Property
	int    hoursWorked;     //Property
	float  grossPay;        //Property
	float  netPay;          //Property
public:
	Employee(char[],char[],float);  //Constructor
	float  calculatePay(float,int); //Procedure
	float  getGrossPay(float,int);  //Procedure
	float  getNetPay(float);				//Procedure
	void  toString();              //Procedure
	int  setHoursWorked(int);     //Procedure
	float  setHourlyRate(float);    //Procedure
};

#endif /* EMPLOYEE_H */