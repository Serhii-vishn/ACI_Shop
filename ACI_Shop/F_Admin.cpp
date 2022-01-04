#include "Admin.h"
//Constructors
Admin::Admin()
{}

Admin::~Admin()
{}

//Method for removing a field from an invoice
void Admin::Delete()
{
	int i;
	std::cout << "\nPlease enter the product code you want to delete: "; std::cin >> i;
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
			std::string line;
			int size = 0;
			while (getline(fout, line))
			{
				//Read data file
				fout >> inv_index >> inv_name >> inv_quantity >> inv_cost;
				if (inv_index != i)
				{
					size = inv_name.size();//Find out the size, for the correct tab
					//Data output
					if (size > 15)
					{
						file_cache << inv_index
										<< "\t\t" << inv_name
											<< "\t" << inv_quantity
												<< "\t\t\t" << inv_cost << "\n";
					}
					else
					{
						file_cache << inv_index
										<< "\t\t" << inv_name
											<< "\t\t" << inv_quantity
												<< "\t\t\t" << inv_cost << "\n";
					}
				}
			}
		}
		//Closing files
		fout.close();
		file_cache.close();

		//Overwrite in the file of new data with the deletion of the specified product
		std::fstream ifs(f_name_cache, std::ios::in), ofs(f_name, std::ios::out); //create streams to overwrite files
		if (!ifs)
		{
			throw file_error(); //File not found
		}
		else
		{
			while (ifs >> inv_index >> inv_name >> inv_quantity >> inv_cost)
			{
				ofs << "\n" << inv_index << "\t\t" << inv_name << "\t\t" << inv_quantity << "\t\t" << inv_cost; //запис в основний файл
			}
		}
		//Closing files
		ifs.close();
		ofs.close();
	}
	else
	{
		throw index_error();//Error entered index
	}
}

//Method for adding a new field to the invoice
void Admin::New()
{
	std::ofstream file_edit;//An object of class ofstream to work with the file
	file_edit.open(f_name, std::ios::app); //File write stream (new ones are added, old ones are not deleted)
	if (!file_edit.is_open()) //check for file availability and install an unusual situation
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
															<< inv_cost; //entry in the product data file
			}
			else
			{
				file_edit << "\n" << inv_index << "\t\t"
													<< inv_name << "\t\t"
														<< inv_quantity << "\t\t"
															<< inv_cost; //entry in the product data file
			}

			//Request to repeat work with new data entry
			std::cout << "\nAdd another product, enter any character, return to the selection menu - *: "; std::cin >> z; //запит на повтор
			if (z == '*')
				k = false;
		}
	}
	file_edit.close();//Close the file
}

//The method of withdrawing the entire consignment note
void Admin::Read()
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

//The method for changing the field, which is already in the consignment note
void Admin::Edit()
{
	int h;
	std::cout << "\n\nEnter the product code you want to edit (change): "; std::cin >> h;
	if (h % 2 == 0 || h <= inv_index)
	{
		bool g;
		//Request to confirm data deletion
		std::cout << "\nAre you sure you want to edit this product? (1-yes, 0-no): "; std::cin >> g;
		if (g == 1)
		{
			std::ifstream fout(f_name);//An object of class ofstream to work with the main file
			std::ofstream file_cache;//An object of class ofstream to work with the cache file
			file_cache.open(f_name_cache);
			if (!fout.is_open())
			{
				throw error_file();
			}
			else
			{
				for (int i = 0; !fout.eof(); i++)
				{
					//Read data file
					fout >> inv_index >> inv_name >> inv_quantity >> inv_cost;
					if (h != inv_index)
					{
						//Data output
						if (inv_name.size() >= 15)//Find out the size, for the correct tab
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
					else
					{
						char l;
						std::cout << "\nClick '+' next to the field you want to edit, otherwise enter any character";
						//The user chooses what to change
						std::cout << "\nName:  " << inv_name << " - "; std::cin >> l;
						if (l == '+')
						{
							std::cout << "\nEnter a new product name:  "; std::cin >> inv_name;
						}

						std::cout << "\nQuantity (weight):  " << inv_quantity << " - "; std::cin >> l;
						if (l == '+')
						{
							std::cout << "\nEnter a new number (weight):  "; std::cin >> inv_quantity;
						}

						std::cout << "\nCost:  " << inv_cost << " - "; std::cin >> l;
						if (l == '+')
						{
							std::cout << "\nEnter the new value of the product:  "; std::cin >> inv_cost;
						}

						std::cout << "\nYou will receive such field in the invoice\n";
						std::cout << inv_index << "\t\t" << inv_name << "\t" << inv_quantity << "\t\t\t" << inv_cost << "\n";

						char u;//Variable to confirm data change
						std::cout << "\nConfirm changes - 1, return to edit menu - any character: "; std::cin >> u;
						if (u == '1')
						{
							//Data output
							if (inv_name.size() >= 15)
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
							//goto m;
						}
					}
				}
			}
			//Close the file
			fout.close();
			file_cache.close();

			//Overwrite in the file of new data with the deletion of the specified product
			std::fstream ifs(f_name_cache, std::ios::in), ofs(f_name, std::ios::out); //create streams to overwrite files
			if (!ifs)
			{
				throw file_error();
			}
			else
			{
				while (ifs >> inv_index >> inv_name >> inv_quantity >> inv_cost)
				{
					//write to the main file
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
			goto ot;
		}
		else
		{
			goto ot;
		}
	}
	else
	{
		throw index_error();
	}
ot:
	system("cls");
}

void Admin::ShowProdRunningOut()
{
	char temp;
	std::cout << "\n You want to set a minimum for searching for goods - 1, not any character: "; std::cin >> temp;
	double min = 0.0;
	if (temp == '1')
	{
		std::cout << "\n Please enter data to sort: "; std::cin >> min;
	}
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
			if (inv_quantity <= min)
			{
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
	}
	fout.close();
}

void Admin::ShowCashRegicterTape()
{
	std::ifstream fout("Receipt.txt");
	if (!fout.is_open())//If the file opening was successful
	{
		throw file_error(); //File not found
	}
	else
	{
		std::string x;
		system("cls");
		while (getline(fout, x))
		{
			std::cout << x << std::endl;
		}
	}
	fout.close();
}