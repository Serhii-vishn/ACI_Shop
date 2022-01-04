#pragma once
#include <string>
std::string authorization(std::string, char);

class Login
{
private:
	std::string AdminLogin;
	std::string AdminPassword;
	std::string	f_users;
public:
	std::string NameUser;
	Login();
	~Login();
	bool DataValidation(std::string, std::string);
	//void AddNewAdmin();
};

Login::Login()
{
	f_users = "users.txt";
	char key = 'l';
	AdminLogin = authorization(f_users, key);
	key = 'p';
	AdminPassword = authorization(f_users, key);
	key = 'n';
	NameUser = authorization(f_users, key);
}

Login::~Login()
{
}

//Retrieving data from a file
std::string authorization(std::string std, char i)
{
	std::string login, password, name;

	std::ifstream fout(std);

	if (!fout.is_open())//If the file opening was successful
	{
		std::cout << "Error! Failed to open login and password file!\n";
	}
	else
	{
		//Read data file
		fout >> name >> login >> password;
	}

	if (i == 'l')
	{
		return login;
	}
	else if (i == 'p')
	{
		return password;
	}
	else
	{
		return name;
	}
}

//Method for checking the entered password and login of the administrator
bool Login::DataValidation(std::string login, std::string password)
{
	if (login == AdminLogin || password == AdminPassword)
	{
		return true;
	}
	else
	{
		return false;
	}
}