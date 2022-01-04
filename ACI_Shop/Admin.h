#pragma once
#include "User.h"

class Admin : public User
{
private:

public:
	//Constructors
	Admin();
	/*Admin(std::string f_name, std::string f_name_cache, std::string inv_name,
		float inv_cost, float inv_quantity,
			int inv_index);*/
	~Admin();

	void Delete();//Removal method
	void New();//Method for creating a new field
	void Read();//Method to read from the invoice file
	void Edit();
	void ShowProdRunningOut();
	void ShowCashRegicterTape();
};