#include "Product.h"
#include "Receipt.h"

//Constructors: initialization, copy, destructor
receipt::receipt() :product()
{
	f_sum = 0.0;
	rem = 0.0;
	sum = 0.0;
}

receipt::receipt(std::string name, float quantity) : product(name, quantity)
{}

receipt::receipt(float r, float f_s, int b_k)
{
	this->rem = r;
	this->f_sum = f_s;
	this->k = b_k;
}

receipt::receipt(const receipt& copy_receipt) : rem(copy_receipt.rem), f_sum(copy_receipt.f_sum), k(copy_receipt.k)
{}

receipt::~receipt()
{}

//Static value for calculating the amount per check
float receipt::sum = 0.0;

//Get data on a static value
float receipt::getsum(float value)
{
	sum = value;
	return sum;
}


//Show of the current time
void receipt::time()
{
	std::cout << "\n------------------------------------";
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::cout << "\n" << (now->tm_mday) << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900);
	std::cout << ", " << (now->tm_hour) << ":" << (now->tm_min) << ":" << (now->tm_sec);
	std::cout << "\nThank you for your purchase, have a nice day ;)";
	std::cout << "\n************************************\n";
}

//Calculating the amount
void receipt::payment()
{
	std::cout << "To be paid: " << sum << "\n";
	std::cout << "Please choose a payment method: 1 - payment in cash, 0 - by card "; std::cin >> k;
	system("cls");
	if (k == 1)
	{
		std::cout << "Amount to be paid: " << sum << "\n";
		std::cout << "\nAmount: "; std::cin >> f_sum;
		if (f_sum >= sum)
		{
			rem = f_sum - sum;
			system("cls");
			std::cout << "************************************\n";
			std::cout << "Amount to be paid: " << sum << "\n";
			std::cout << "Imported: " << f_sum << "\n";
			std::cout << "Surrender: " << rem;
			std::cout << "\n------------------------------------";
		}
		else
		{
			rem = f_sum - sum;
			system("cls");
			std::cout << "************************************\n";
			std::cout << "Amount to be paid: " << sum << "\n";
			std::cout << "Imported: " << f_sum << "\n";
			std::cout << "You still have to pay extra: " << abs(rem);
			std::cout << "\n------------------------------------";
		}
	}
	else if (k == 0)
	{
		system("cls");
		std::cout << "************************************\n";
		std::cout << "Amount to be paid: " << sum << "\nPayment by card";
		std::cout << "\n------------------------------------";
	}
	else
	{
		throw error_file();
	}
}

//Save data to file
void receipt::save_f()
{
	std::ofstream out; //File to write
	out.open("Receipt.txt", std::ofstream::app); //Open the file for writing
	if (out.is_open())
	{
		if (k == 1)
		{
			if (f_sum >= sum)
			{
				out << "************************************\n";
				out << "Amount to be paid: " << sum << "\n";
				out << "Imported: " << f_sum << "\n";
				out << "Surrender: " << rem;
				out << "\n------------------------------------\n";
			}
			else
			{
				out << "************************************\n";
				out << "Amount to be paid: " << sum << "\n";
				out << "Imported: " << f_sum << "\n";
				out << "You still have to pay extra: " << abs(rem);
				out << "\n------------------------------------\n";
			}
		}
		else if (k == 0)
		{
			out << "************************************\n";
			out << "Amount to be paid: " << sum << "\nPayment by card";
			out << "\n------------------------------------\n";
		}
	}
	else
	{
		throw error_file();
	}
}

//Save time data to a file
void receipt::savetime_f()
{

	std::ofstream out;//Stream for recording
	out.open("Receipt.txt", std::ofstream::app); //Open the file for writing
	if (out.is_open())
	{
		out << "\n------------------------------------";
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		out << "\n" << (now->tm_mday) << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900);
		out << ", " << (now->tm_hour) << ":" << (now->tm_min) << ":" << (now->tm_sec);
		out << "\nThank you for your purchase, have a nice day";
		out << "\n************************************\n";
	}
	else
	{
		throw error_file();
	}
}