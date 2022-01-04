#pragma once
#include <conio.h>
#include <locale>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

int get_index(std::string);

class Storage//Base class for User class
{
protected:
	std::string f_name;//Invoice file name
	std::string f_name_cache;//Cache file name
	std::string inv_name;//Product name
	float inv_cost;//Price
	float inv_quantity;//Quantity in stock
	int inv_index;//Product code
public:
	Storage();
	Storage(std::string, std::string, std::string, float, float, int);//Name, price, quantity in stock, product code
	~Storage();

	//Methods
	void EditUser(int, float);//Data editing method (purchase of goods)
	std::string GetName(int);//Method that returns the name of the product in the warehouse for a given product code
	float GetCost(int);//Method that returns the price for a given product code
	float GetQuantity(int);//Method that returns the quantity in the warehouse for a given product code
	bool Find(int);//The method that returns the availability of goods in the warehouse for a given product code
	//virtual methods
	virtual void Delete(int);//Removal method
	virtual void New();//Method for creating a new field
	virtual void Read();//Method to read from the invoice file

	//Exclusion
	class file_error {};//Error handling with file opening
	class index_error {};//Error handling with incorrect data retrieval
	class storage_error {};//Processing of the situation when the order exceeds quantity of the goods in the consignment note
};