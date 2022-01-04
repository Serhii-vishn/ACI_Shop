#pragma once
#include <conio.h>
#include <locale>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#pragma warning(disable : 4996)//Directive to allow robots to function in the current time

class product//Base class for the Receirt class
{
protected:
	float quantity; //Quantity of products
	int code; //Product code
	std::string name;//Product name
	float cost;//Cost
	float amount;//Price*quantity
public:
	//Constructor
	product();
	//Initialization constructor
	product(float quantity, std::string name, float cost);
	product(std::string n, float q);
	//Copy constructor
	product(const product&);
	//Destructor
	~product();

	//Overload
	float operator + (float s);

	//Methods
	virtual void showdata();//Overridden data output method
	virtual void getdata();//Overridden data acquisition method
	virtual void save_pf();//Standard method for saving data to a file

	//Exclusion
	class quantity_null {};//Quantity check
};