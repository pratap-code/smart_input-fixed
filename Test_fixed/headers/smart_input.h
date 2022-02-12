#pragma once

#include "common.h"

// this defines a class to take input in a smart way that is self checking

// need to add type check for variables  .... 

// how to ensure the order of entering is correct


class smart_input
{
private:
	std::string inp;     // this is the actual input entered by the user
	std::string xinp;    // this is the expected input

	std::stringstream strm;  // this is used to store 0 formatted input if objects need to be created


public:
	smart_input();

	void get_input(std::string, std::string);  // to get inp and xinp


	void split_xinp(std::string&) const; // to split words depending on what kind of word it is

	bool check_num(std::string&, char) const;

	template <typename T>
	std::vector<T> create_vec(const std::string) const;

	int count(std::string, const char*) const;  //this counts the no of words in inp or xinp string

	int count_values(std::string) const;  //this counts no of values in cur_xinp word


	template <typename T>
	bool compare(char&, char&, std::vector<T>&, T&) const;

	template <typename T>
	T create_val(std::string&) const;


	std::stringstream create_strm() const;

	std::stringstream& get_stream();

	void print_strm() const;

	void reset();
};









//this function creates and initializes vector of type T from values in cur_xinp

template <typename T>
std::vector<T> smart_input::create_vec(const std::string cur_xinp) const
{
	size_t n{ 0 };  // using n to count total no of terms, then later only the no of values
	std::string word;
	std::stringstream stm(cur_xinp);  // cur_xinp word here should be split(space separated)
	std::vector<std::string>vecx;

	while (stm >> word)  // cur_xinp stored word by word in a vector
	{
		vecx.push_back(word);
		++n;
	}

	n = (n - 2) / 2;   // here n is storing the no of values

	std::vector<T>vec;

	for (size_t k = 1; k <= n; ++k)
	{
		std::stringstream tmp(vecx[2 * k]);   // here stream only gets the values that are at position 2*k.
		T var{};
		tmp >> var;  // storing the value from stream tmp to T
		vec.push_back(var);
	}

	return vec;
	// by here the vector of values of type T should be created and initialized

}




// this function creates current inp value to be compared
template <typename T>
T smart_input::create_val(std::string& cur_inp) const
{
	std::stringstream tmp(cur_inp);
	T val{};
	tmp >> val;
	return val;
}

template <typename T>
bool smart_input::compare(char& lb, char& rb, std::vector<T>& vec, T& val) const
{
	if (lb == '(' && rb == ')')
	{
		std::cout << "Comparing {" << val << "} to " << "{" << vec.front() << "} " << " & {" << vec.back() << "} " << '\n';
		if (vec.front() < val && val < vec.back())
			return true;
		else
			return false;
	}
	else if (lb == '(' && rb == ']')
	{
		std::cout << "Comparing {" << val << "} to " << "{" << vec.front() << "} " << " & {" << vec.back() << "} " << '\n';
		if (vec.front() < val && val <= vec.back())
			return true;
		else
			return false;
	}
	else if (lb == '[' && rb == ')')
	{
		std::cout << "Comparing {" << val << "} to " << "{" << vec.front() << "} " << " & {" << vec.back() << "} " << '\n';
		if (vec.front() <= val && val < vec.back())
			return true;
		else
			return false;
	}
	else if (lb == '[' && rb == ']')
	{
		std::cout << "Comparing {" << val << "} to " << "{" << vec.front() << "} " << " & {" << vec.back() << "} " << '\n';
		if (vec.front() <= val && val <= vec.back())
			return true;
		else
			return false;
	}
	else if (lb == '{' && rb == '}')
	{

		for (size_t i = 0; i < vec.size(); ++i)  // comparing to each of the values here for {}
		{
			std::cout << "Comparing {" << val << "} to " << "{ " << vec[i] << "} " << '\n';
			if (val == vec[i])
				return true;
		}

		return false;
	}

}




