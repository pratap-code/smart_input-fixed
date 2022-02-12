
#include "../headers/fixed.h"


// constructor for fixed

fixed::fixed()
{
	std::cout << "Constructor called!" << '\n';
}



// assgining the value to string num
void fixed::create(std::stringstream& strm)
{
	// this assgins the double number as a std::string to string num
	if (strm >> num)
	{
		std::cout << "Successfully created num" << '\n';
	}
	else
	{
		std::cout << "Error!!! Extraction from input unsuccessful!" << '\n';
	}
	
}

//this function returns the num as a double variable for processing
double fixed::get_double() const
{
	if (!num.empty())
	{
		double d{};
		std::stringstream tmp(num);
		tmp >> d;
		return d;
	}
	else
	{
		std::cout << "Error! num is not set!" << '\n';
		return -9999999;
	}
}

void fixed::display() const
{
	std::cout << "Value : std::string<" << num << "> , double<" << get_double() << ">" << '\n';
}


