#pragma once

#include "common.h"


// this class defines fixed type to store double from std::string and also to process double from std::string

class fixed
{
private:
	std::string num;


public:
	
	fixed();  // constructor

	void create(std::stringstream&);

	double get_double() const;

	void display() const;

	/*void write_text(std::ofstream&) const;
	void write_binary(std::ofstream&) const;


	void read_text(std::ifstream&);
	void read_binary(std::ifstream&);*/
	

};
