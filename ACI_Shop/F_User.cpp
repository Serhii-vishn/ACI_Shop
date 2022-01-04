#include "User.h"

//Constructors: initialization, copy, destructor
User::User() : receipt()
{}

User::User(std::string name, float quantity) : receipt(name, quantity)
{}

User::User(const User& g) : receipt(g)
{}

User::~User()
{}

//Method of get data from the user
void User::getdata()
{
	std::cout << "Please enter the product code: "; std::cin >> code;
	if (Find(code) == 1)
	{
		std::cout << "\nEnter quantity (weight):  "; std::cin >> quantity;
		if (GetQuantity(code) >= quantity && quantity > 0)//Checking the quantity for availability and correctness
		{
			EditUser(code, quantity);
			cost = GetCost(code);
			name = GetName(code);
			amount = cost * quantity;
		}
		else
		{
			std::cout << "\nUnfortunately in the warehouse on the consignment note only " << GetQuantity(code) << " units of this product\n";
			throw quantity_error();//Error processing of the entered quantity
		}
	}
	else
	{
		throw prod_absent();
	}
}

//Show the list of purchased goods
void User::showdata()
{
	//Data output
	std::cout << "\n" << name << "\n\t" << quantity << " * " << cost << " = " << amount;
}

//Save the list of purchased goods to a file
void User::safe_pf()
{
	std::ofstream fout; //Opening a stream
	fout.open("Receipt.txt", std::ofstream::app); //Open the file
	if (fout.is_open())
	{
		fout << "\n" << name << "\n\t" << quantity << " * " << cost << " = " << amount;
	}
	else
	{
		throw file_error();
	}
	fout.close();//Close the file
}