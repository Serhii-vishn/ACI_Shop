#include "Storage.h"
//Constructors
Storage::Storage()
{
	f_name = "storage.txt";
	f_name_cache = "storage_cache.txt";
	inv_cost = 0.0;
	inv_quantity = 0.0;
	inv_index = get_index(f_name);
}

Storage::Storage(std::string f_name, std::string f_name_cach, std::string inv_name, float inv_cost, float inv_quantity, int inv_index)
{
	this->f_name = f_name;
	this->f_name_cache = f_name_cach;
	this->inv_name = inv_name;
	this->inv_cost = inv_cost;
	this->inv_quantity = inv_quantity;
	this->inv_index = inv_index;
}

Storage::~Storage()
{}

//Method of searching for goods
bool Storage::Find(int i)
{
	if (i % 2 == 0 && i <= get_index(f_name))
	{
		int inc = 0;
		std::ifstream f_find(f_name);
		if (!f_find.is_open())//If the file opening was successful
		{
			throw file_error(); //File not found
		}
		else
		{
			std::string l;
			//The information is read line by line until the desired name is found or the file ends
			while (getline(f_find, l))
			{
				//Read data from file
				f_find >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (i == inv_index)
				{
					inc++;
					//Data output
					std::cout << inv_name << " - " << inv_cost;
				}
			}
			f_find.close();
			//Error output if the user entered an incorrect name that is not in the file
			if (inc == 0)
			{
				std::cout << "Error! Unfortunately, there are no goods under this code in the invoice\n";
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	else
	{
		std::cout << "Error! Unfortunately, there are no goods under this code in the invoice\n";
		return 0;
	}
}

//Method of reading from a file and outputting data to the console
void Storage::Read()
{
	std::ifstream fout(f_name);
	if (!fout.is_open())//If the file opening was successful
	{
		throw file_error(); //File not found
	}
	else
	{
		system("cls");
		std::string line;
		//The information is read line by line until the file is finished
		std::cout << "Invoice for goods in the store";
		std::cout << "\n_________________________________________________";
		std::cout << "\nProduct code\t" << "Product name\t\t" << "Quantity (weight)\t" << "Price\n";
		for (int i = 0; !fout.eof(); i++)
		{
			//Read data file
			fout >> inv_index >> inv_name >> inv_quantity >> inv_cost;
			//Data output
			if (inv_name.size() > 15)//Find out the size, for the correct tab
			{
				std::cout << "\n" << inv_index << "\t\t"
													<< inv_name << "\t"
														<< inv_quantity << "\t\t\t"
															<< inv_cost;
			}
			else
			{
				std::cout << "\n" << inv_index << "\t\t"
													<< inv_name << "\t\t"
														<< inv_quantity << "\t\t\t"
															<< inv_cost;
			}
		}
	}
	fout.close();
}

//Data editing method (purchase of goods)
void Storage::EditUser(int a, float quantity)
{
	if (a % 2 == 0 && a <= get_index(f_name))
	{
		std::ifstream fout(f_name);//An object of class ofstream to work with the main file
		std::ofstream file_cache;//An object of class ofstream to work with the cache file
		file_cache.open(f_name_cache);
		if (!fout.is_open())
		{
			throw file_error(); //File not found
		}
		else
		{
			for (int i = 0; !fout.eof(); i++)
			{
				//Read data file
				fout >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (a == inv_index)
				{
					inv_quantity -= quantity;
				}
				//Data output
				if (inv_name.size() >= 16)//Find out the size, for the correct tab
				{
					file_cache << "\n" << inv_index
											<< "\t\t" << inv_name
												<< "\t" << inv_quantity
													<< "\t\t\t" << inv_cost;
				}
				else
				{
					file_cache << "\n" << inv_index
											<< "\t\t" << inv_name
												<< "\t\t" << inv_quantity
													<< "\t\t\t" << inv_cost;
				}
			}
			//Close the file
			fout.close();
			file_cache.close();

			//Overwrite in the file of new data with the deletion of the specified product
			std::fstream ifs(f_name_cache, std::ios::in), ofs(f_name, std::ios::out); //Create streams to overwrite files
			if (!ifs)
			{
				std::cout << "Error! Failed to open file!";
			}
			else
			{
				while (ifs >> inv_index >> inv_name >> inv_quantity >> inv_cost)
				{
					//Write to the main file
					if (inv_name.size() >= 15)
					{
						ofs << "\n" << inv_index
										<< "\t\t" << inv_name
											<< "\t" << inv_quantity
												<< "\t\t\t" << inv_cost;
					}
					else
					{
						ofs << "\n" << inv_index
										<< "\t\t" << inv_name
											<< "\t\t" << inv_quantity
												<< "\t\t\t" << inv_cost;
					}
				}
			}
			//Close the file
			ifs.close();
			ofs.close();
		}
	}
}

//Method to delete from file
void Storage::Delete(int i)
{
	if (i % 2 == 0 && i <= get_index(f_name))
	{
		std::ifstream fout(f_name);//An object of class ofstream to work with the main file
		std::ofstream file_cache;//An object of class ofstream to work with the cache file
		file_cache.open(f_name_cache);
		if (!fout.is_open())
		{
			throw file_error(); //File not found
		}
		else
		{
			for (int i = 0; !fout.eof(); i++)
			{
				//Read data file
				fout >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (inv_index != i)
				{
					//Data output
					if (inv_name.size() > 15)//Find out the size, for the correct tab
					{
						file_cache << "\n" << inv_index
												<< "\t\t" << inv_name
													<< "\t" << inv_quantity
														<< "\t\t\t" << inv_cost;
					}
					else
					{
						file_cache << "\n" << inv_index
												<< "\t\t" << inv_name
													<< "\t\t" << inv_quantity
														<< "\t\t\t" << inv_cost;
					}
				}
			}
		}
		//Close the file
		fout.close();
		file_cache.close();

		//Overwrite in the file of new data with the deletion of the specified product
		std::fstream ifs(f_name_cache, std::ios::in), ofs(f_name, std::ios::out); //Create streams to overwrite files
		if (!ifs)
		{
			std::cout << "Error! Failed to open file!";
		}
		else
		{
			while (ifs >> inv_index >> inv_name >> inv_quantity >> inv_cost)
			{
				//Write to the main file
				if (inv_name.size() >= 15)
				{
					ofs << "\n" << inv_index
									<< "\t\t" << inv_name
										<< "\t" << inv_quantity
											<< "\t\t\t" << inv_cost;
				}
				else
				{
					ofs << "\n" << inv_index
									<< "\t\t" << inv_name
										<< "\t\t" << inv_quantity
											<< "\t\t\t" << inv_cost;
				}
			}
		}
		//Close the file
		ifs.close();
		ofs.close();
	}
	else
	{
		throw index_error();//Error entered index
	}
}

//Method for adding a new field to the invoice
void Storage::New()
{
	std::ofstream file_edit;//An object of class ofstream to work with the file
	file_edit.open(f_name, std::ios::app); //File write stream (new ones are added, old ones are not deleted)
	if (!file_edit.is_open()) //Check for file availability and install an unusual situation
	{
		throw file_error(); //File not found
	}
	else
	{
		inv_index = get_index(f_name);
		char z;
		bool k = true;
		while (k)
		{
			inv_index += 2;
			//Get data from the console
			std::cout << "\nEnter the product name: "; std::cin >> inv_name;
			std::cout << "Enter quantity (weight): "; std::cin >> inv_quantity;
			std::cout << "Enter the price of the product: "; std::cin >> inv_cost;
			std::cout << "The product is assigned an index: " << inv_index;

			//Write data to a file
			if (inv_name.size() > 14)//Get the size of the tab name
			{
				file_edit << "\n" << inv_index << "\t\t"
													<< inv_name << "\t"
														<< inv_quantity << "\t\t"
															<< inv_cost; //Entry in the product data file
			}
			else
			{
				file_edit << "\n" << inv_index << "\t\t"
													<< inv_name << "\t\t"
														<< inv_quantity << "\t\t"
															<< inv_cost; //Entry in the product data file
			}

			//Request to repeat work with new data entry
			std::cout << "\nAdd another product, enter any character, return to the selection menu - *: "; std::cin >> z; //Retry request
			if (z == '*')
				k = false;
		}
	}
	file_edit.close();//Close the file
}

//Method that returns a name for a given product code
std::string Storage::GetName(int i)
{
	std::string name;
	if (i % 2 == 0 && i <= get_index(f_name))
	{
		std::ifstream f_find(f_name);
		if (!f_find.is_open())//If the file opening was successful
		{
			throw file_error(); //File not found
		}
		else
		{
			std::string line;
			//The information is read line by line until the desired name is found or the file ends
			while (getline(f_find, line))
			{
				//Read data file
				f_find >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (i == inv_index)
				{
					name = inv_name;//Getting the right name
				}
			}
			f_find.close();//Close the file
		}
	}
	else
	{
		std::cout << "Error! Unfortunately, there are no goods under this code in the invoice\n";
	}
	return name;
}

//The method that returns the price for a given product code
float Storage::GetCost(int i)
{
	float cost = 0.0;
	if (i % 2 == 0 && i <= get_index(f_name))
	{
		std::ifstream f_find(f_name);
		if (!f_find.is_open())//If the file opening was successful
		{
			throw file_error(); //File not found
		}
		else
		{
			std::string line;
			//The information is read line by line until the desired name is found or the file ends
			while (getline(f_find, line))
			{
				//Read data file
				f_find >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (i == inv_index)
				{
					cost = inv_cost;//Getting the right price
				}
			}
			f_find.close();
		}
	}
	else
	{
		std::cout << "Error! Unfortunately, there are no goods under this code in the invoice\n";
	}
	return cost;
}

//The method that returns the quantity in the warehouse for a given product code
float Storage::GetQuantity(int i)
{
	float quantity = 0.0;
	if (i % 2 == 0 && i <= get_index(f_name))
	{
		std::ifstream f_find(f_name);
		if (!f_find.is_open())//If the file opening was successful
		{
			throw file_error(); //File not found
		}
		else
		{
			std::string line;
			//The information is read line by line until the desired name is found or the file ends
			while (getline(f_find, line))
			{
				//Read data file
				f_find >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (i == inv_index)
				{
					quantity = inv_quantity;//getting the right price
				}
			}
			f_find.close();
		}
	}
	else
	{
		std::cout << "Error! Unfortunately, there are no goods under this code in the invoice\n";
	}
	return quantity;
}

//The function of obtaining a value for the index
int get_index(std::string name)
{
	int id = 0;
	std::ifstream f_find(name);

	std::string l;
	while (getline(f_find, l))
	{
		f_find >> id;
	}
	f_find.close();
	return id;//returns the value of the last commodity index
}