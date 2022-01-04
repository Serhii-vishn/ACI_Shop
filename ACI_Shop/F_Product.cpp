#include "Product.h"

//Constructors: initialization, copy, destructor
product::product()
{
	cost = 0.0;
	quantity = 0.0;
	amount = 0.0;
}

//Initialization constructor
product::product(float quantity, std::string name, float cost)
{
	this->quantity = quantity;
	this->name = name;
	this->cost = cost;
}
product::product(std::string n, float q)
{
	this->name = n;
	this->quantity = q;
}

//Copy constructor
product::product(const product& copy_product) : quantity(copy_product.quantity), amount(copy_product.amount)
{}

//Destructor
product::~product()
{}

//Fill out check(overdefined)
void product::getdata()
{
	std::cout << "Enter the product code: "; std::cin >> code;
	std::cout << "Enter quantity (weight):  "; std::cin >> quantity;
	//Check quantity entry
	if (quantity <= 0)
	{
		throw quantity_null();//error handling
	}
}

//Show product info(overridden)
void product::showdata()
{
	std::cout << name << "\t" << cost << "\t" << amount << "\n";
}

//Save data to file(overridden)
void product::save_pf()
{
	std::ofstream fout;//Record stream
	fout.open("Receipt.txt", std::ofstream::app);//Open the file
	if (fout.is_open())
	{
		fout << name << "\t" << cost << "\t" << amount << "\n";
	}
	fout.close();
}

//Overload +
float product::operator+(float s)
{
	return this->amount + s;
}