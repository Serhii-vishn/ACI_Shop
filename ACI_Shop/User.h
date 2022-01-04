#pragma once
#include "Receipt.h"
#include "Storage.h"

class User : public receipt, public Storage
{
public:
	//Constructors
	User();
	User(std::string name, float quantity); //parameters for Product, receipt, Storage
	User(const User&);
	~User();

	//Methods
	void getdata();//Method of get data from the user
	void showdata();//Show the list of purchased goods
	void safe_pf();//Save the list of purchased goods to a file

	//Exclusion
	class quantity_error {};
	class prod_absent {};
	class file_error {};
};