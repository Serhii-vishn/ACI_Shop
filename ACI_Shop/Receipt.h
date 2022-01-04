#pragma once
#include "Product.h"

class receipt : public product//Base class for User class
{
private:
	static float sum;//Amount to be paid
	int k;//Switch (card / cash payment)
	float f_sum;//The amount is paid by the user
	float rem;//Surrender
public:
	//Constructors: initialization, copy, destructor
	receipt();
	receipt(std::string name, float quantity);
	receipt(float r, float f_s, int b_k);
	receipt(const receipt&);
	~receipt();

	//Creating a static variable
	static float getsum(float value);

	//Methods
	void payment();//Calculating the amount
	void save_f();//Save to file
	void time();//Current time
	void savetime_f();//Save to current time file

	//Exclusion
	class error {};
	class error_file {};//Checking the correctness of the payment method
};