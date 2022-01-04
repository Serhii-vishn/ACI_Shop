#include "User.h"
#include "Login.h"
#include "Admin.h"

const int max = 50;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char log;
log_r:
	system("cls");
	std::cout << "\n\n\n\n\t\t\t\t\tHello! Please log in";
	std::wcout << "\n\t\t\t____________________________________________________\n";

	std::cout << "\n\t\t\tIf you:";
	std::cout << "\n\t\t\tAdministrator enter - 1\n" << " \t\t\tCashier - 2\n" << " \t\t\tFinish work - 3\n" << " Result: "; std::cin >> log;
	switch (log)
	{
	case '1'://Administrator work menu
	{
		Login login;
		std::string log, pass;
		std::cout << "Please enter a login: "; std::cin >> log;
		std::cout << "Please enter a password: "; std::cin >> pass;
		if (login.DataValidation(log, pass) == true)//data verification
		{
			Admin adminlogin;
			bool we = true;
			char stor;

			system("cls");
			std::cout << "\t\t\tYou are logged in. Glad to see you again " << login.NameUser << "\n";
			std::cout << "\t\t\t_________________________________________________\n";

			system("pause");

			while (we == true)
			{
			men_adm:
				system("cls");
				std::cout << "\t\t\t\tWork with the warehouse (consignment note):\n";
				std::cout << "\t\t\t______________________________________________\n";
				std::cout << "\n\t\t\tView all goods on the invoice - 1\n"
							<< "\t\t\tEditing the invoice - 2\n"
							<< "\t\t\tView ending items - 3\n"
							<< "\t\t\tView checklist - 4\n"
							<< "\t\t\tReturn to the authorization menu - 0\n" << " Result: ";	std::cin >> stor;
				switch (stor)
				{
				case '1':
				{
					system("cls");
					try
					{
						adminlogin.Read();
					}
					catch (Admin::file_error)
					{
						std::cout << "Error! Failed to open file!";
					}
					break;
				}
				case '2':
				{
				menu_reg:
					system("cls");
					char j;
					std::cout << "\t\t\t\tSelect edit mode:\n";
					std::wcout << "\t\t\t______________________________________\n";
					std::cout << "\n\t\t\tAdd a new product to the invoice - 1\n"
								<< "\t\t\tEditing goods that are already in the invoice - 2\n"
								<< "\t\t\tRemove the goods from the consignment note - 3\n"
								<< "\t\t\tReturn to the invoice work menu - *\n"; std::cin >> j;
					switch (j)
					{
					case '1':
					{
						try
						{
							adminlogin.New();
						}
						catch (Admin::file_error)
						{
							std::cout << "Error! Failed to open file!";
						}
						break;
					}
					case '2':
					{
						bool ed = true;
						while (ed == true)
						{
							system("cls");
						prod_edit:
							try
							{
								adminlogin.Read();
							}
							catch (Admin::file_error)
							{
								std::cout << "\nError! Failed to open file!\n";
							}
							try
							{
								adminlogin.Edit();
							}
							catch (Admin::file_error)
							{
								std::cout << "Error! Failed to open file!";
							}
							catch (Admin::index_error)
							{
								std::cout << "Error! Incorrect product code entered!";
								goto prod_edit;
							}
							char g;
							std::cout << "\nContinue to edit any character characters, complete - *: "; std::cin >> g;
							if (g == '*')
								ed = false;
						}
						break;
					}
					case '3':
					{
					prod_del:
						try
						{
							adminlogin.Read();
						}
						catch (Admin::file_error)
						{
							std::cout << "\nError! Failed to open file!\n";
						}
						try
						{
							adminlogin.Delete();
						}
						catch (Admin::file_error)
						{
							std::cout << "\nError! Failed to open file!\n";
						}
						catch (Admin::index_error)
						{
							std::cout << "\nError! Incorrectly entered index!\n";
							system("pause");
							system("cls");
							goto prod_del;
						}
						break;
					}
					case '*':
					{
						goto men_adm;
					}
					default:
						std::cout << "\nInvalid character, please try again\n";
						system("pause");
						goto menu_reg;
						break;
					}
					break;
				}
				case '3':
				{
					system("cls");
					try
					{
						adminlogin.ShowProdRunningOut();
					}
					catch (Admin::file_error)
					{
						std::cout << "Error! Failed to open file!";
					}
					break;
				}
				case '4':
				{
					system("cls");
					try
					{
						adminlogin.ShowCashRegicterTape();
					}
					catch (Admin::file_error)
					{
						std::cout << "Error! Failed to open file!";
					}
					break;
				}
				case '0':
				{
					system("pause");
					system("cls");
					goto log_r;
				}
				default:
					std::cout << "\nInvalid character, please try again\n";
					system("pause");
					goto men_adm;
					break;
				}
				char z;
				std::cout << "\nContinue working with the invoice of any character, complete - *: "; std::cin >> z;
				if (z == '*')
					we = false;
			}
		}
		else
		{
			std::cout << "Error! Incorrect data, please try again\n";
			system("pause");
			system("cls");
			goto log_r;
		}
		break;
	}
	case '2'://Cashier's work menu
	{
		User userlog[max], total;
		bool k = true;
		while (k)
		{
			int ty[max];//The array is equal to the length of the goods in the check, for the convenience of working with cancellations
			int prod_inc = 0;//Counter of the number of goods per check
			char sign;//Sign (+ add product; - cancel)
			float sum = 0;//Variable in which the amount of goods is written
			bool u_bool = true;

			system("cls");
			std::cout << "\t\t\t\tGlad to see you again dear customer\n";
			std::cout << "\t\t\t_________________________________________________\n\n";

			for (int i = 0; i < max; i++)
			{
				if (u_bool == true)
				{
					prod_inc++;
				prod_abst:
					try
					{
						userlog[i].getdata();
					}
					catch (User::quantity_error)
					{
					l_qunt:
						char l;
						std::cout << "Do you want to pick up this product with another quantity or continue to register the next product - 1, 0 - calculate the amount: ";
						std::cin >> l;
						if (l == '1')
						{
							goto prod_abst;
						}
						else if (l == '0')
						{
							ty[i] = 0;
							goto prod_r;
						}
						else
						{
							std::cout << "Error! Invalid character entered!";
							goto l_qunt;
						}
					}
					catch (User::prod_absent)
					{
						std::cout << "Please try again\n";
						goto prod_abst;
					}
				sign:
					std::cin >> sign;
					if (sign == '+')
					{
						ty[i] = 1;
						sum = userlog[i] + sum;
						receipt::getsum(sum);
						u_bool = true;
					}
					else if (sign == '-')
					{
						ty[i] = 0;
						bool d = 0;
						std::cout << "\nTo continue the registration of goods, enter 1, count - 0: "; std::cin >> d;
						if (d == 1)
						{
							u_bool = true;
						}
						else
						{
							u_bool = false;
						}
					}
					else if (sign == '=')
					{
						ty[i] = 1;
					prod_r:
						sum = userlog[i] + sum;
						receipt::getsum(sum);
						u_bool = false;
					}
					else
					{
						std::cout << "Error! incorrectly entered character, please try again! ";
						goto sign;
					}
				}
			}

		pay:
			try
			{
				total.payment();//Display results
			}
			catch (receipt::error)
			{
				std::cout << "\nError! Choose a payment method\n";
				goto pay;//Error entering payment method incorrectly
			}

			try
			{
				total.save_f();//Save prefixes to a file
			}
			catch (receipt::error_file)
			{
				std::cout << "\nError! File to save checks not found or damaged\n";
			}

			for (int i = 0; i < prod_inc; i++)
			{
				if (ty[i] == 1)
				{
					userlog[i].showdata();//Display a list of goods on the check

					try
					{
						userlog[i].safe_pf();//Save to file a list of goods for a check
					}
					catch (User::file_error)
					{
						std::cout << "\nError! File to save checks not found or damaged\n";
					}
				}
			}
			total.time();//Call the function to display the current time

			try
			{
				total.savetime_f();//Save the current time to a file
			}
			catch (receipt::error_file)
			{
				std::cout << "\nError! File to save checks not found or damaged\n";
			}

			char z;
			std::cout << "To continue working as a cashier, enter any character, return to the authorization menu - *: ";
			std::cin >> z;
			if (z == '*')
			{
				k = false;
				system("cls");
				goto log_r;
			}
		}
		break;
	}
	case '3'://Shutdown menu
	{
		goto out;
	}
	default:
	{
		std::cout << "\nError! Invalid character entered\n";
		system("pause");
		system("cls");
		goto log_r;
		break;
	}
	}
out:
	std::cout << "\n\t\t\t\t\tHave a nice day";
	std::wcout << "\n \t\t\t____________________________________________________\n";
	system("pause");
}