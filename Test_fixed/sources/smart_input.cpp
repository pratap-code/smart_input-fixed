#include "..\headers\smart_input.h"


smart_input::smart_input() // no need for xno, that will be counted, this is default constructor
{
}


// to get input from the user along with the expected input and expected no. of inputs, inp and xinp has to be entered in the same order
void smart_input::get_input(std::string message, std::string xinp)
{
	bool result{ false };
		
		
	while (!result)
	{
		reset();  // before every input reset the smart_input object

		// prompt to get input from the user    --> just counting in this function
		std::cout << message << " : ";
		getline(std::cin, inp);

		this->xinp = xinp; // copying the xinp to class member this->xinp




		// to count the actual no of words in inp string and xinp string and verify
		int count_inp{ 0 }, count_xinp{ 0 };

		count_inp = count(inp, "inp");
		count_xinp = count(xinp, "xinp");  // count returns -1 if there are arbitrary no of terms

		if (count_inp == count_xinp)  // this is only possible when there are fixed no of terms expected in input
		{
			// to process inp and xinp word by word non-destructively
			std::string word_inp, word_xinp;
			std::stringstream stm_inp{ inp }, stm_xinp{ xinp };
			std::vector<std::string> vec_inp, vec_xinp;

			while (stm_inp >> word_inp && stm_xinp >> word_xinp)
			{
				vec_inp.push_back(word_inp);
				vec_xinp.push_back(word_xinp);
			}
			// now each inp and xinp word to be compared


			for (size_t i = 0; i < vec_xinp.size(); ++i)
			{
				std::string cur_inp{ vec_inp[i] };
				std::string cur_xinp{ vec_xinp[i] };
				split_xinp(cur_xinp);  // splitted xinp is ready in cur_xinp word

				char type{ cur_xinp[0] }, lb{ cur_xinp[2] }, rb{ cur_xinp.back() };

				// checking each word of xinp and comparing with corrensponding word of inp

				if (type == 'i')
				{
					if (check_num(cur_inp, 'i'))
					{
						int num{ create_val<int>(cur_inp) };
						std::vector<int>values(create_vec<int>(cur_xinp));

						result = compare<int>(lb, rb, values, num);
					}
					else
					{
						std::cout << "ERROR!!! Enterd input expects an int and contains an invalid characters!" << '\n';
						result = false;
						break;
					}
				}
				else if (type == 'd')
				{
					if (check_num(cur_inp, 'd'))
					{
						double num{ create_val<double>(cur_inp) };
						std::vector<double>values(create_vec<double>(cur_xinp));

						result = compare<double>(lb, rb, values, num);
					}
					else
					{
						std::cout << "ERROR!!! Enterd input expects an double and contains an invalid characters!" << '\n';
						result = false;
						break;
					}
				}
				else if (type == 's')
				{
					std::string word{ create_val<std::string>(cur_inp) };
					std::vector<std::string>values(create_vec<std::string>(cur_xinp));

					result = compare<std::string>(lb, rb, values, word);
				}
				// by here comparison should be done

				// return result here if false otherwise continue checking for all
				if (result == false)
				{
					std::cout << "ERROR!!! Input at position " << (i + 1) << " not in range!" << '\n';
					break;
				}
				/*else
				{
					std::cout << "Correct Input!! Input at position " << (i + 1) << " is in range!" << '\n';
				}*/
			}

			// add additional result check here
			if (result == false)
			{
				std::cout << "Please try again!" << "\n\n";
				
			}
			else
			{
				// if all the inputs are valid result is true and now return the result and also create strm for creating objects
				
				//std::cout << "All inputs entered are correct!" << '\n';
				strm = create_strm();  // creating strm for creating objects
				//return result here
			}		
		}
		else if (count_xinp == -1) // this is for arbitrary no of input terms
		{
			char type{ xinp[0] };

			if (type == 'i')
			{
				std::stringstream strm(inp);
				std::string word;
				while (strm >> word)
				{
					if (check_num(word, 'i'))
					{
						result = true;
					}
					else
					{
						std::cout << "INVALID INPUT!! Input contains number that is not an int!" << '\n';
						result = false;
						break;
					}
				}

				if (!result)
				{
					std::cout << "Please try again!" << "\n\n";
				}
				else 
				{
					//std::cout << "All inputs correctly entered!" << '\n';
					strm = create_strm();
					//return result here
				}

			}
			else if (type == 'd')
			{
				std::stringstream strm(inp);
				std::string word;
				while (strm >> word)
				{
					if (check_num(word, 'd'))
					{
						result = true;
					}
					else
					{
						std::cout << "INVALID INPUT!! Input contains number that is not a double!" << '\n';
						result = false;
						break;
					}
				}
				
				if (!result)
				{
					std::cout << "Please try again!" << "\n\n";
				}
				else
				{
					//std::cout << "All inputs correctly entered!" << '\n';
					strm = create_strm();
					//return result here
				}

			}
			else if (type == 's')
			{
				result = true;
				strm = create_strm();
				//return result here
			}

		}
		else
		{
			std::cout << "ERROR!!! The number to terms in the input and expected input do not match!" << '\n';
			std::cout << "Please try again!" << "\n\n";
			result = false;
		}
	}
}




// this separates the current xinp word into a space separated string of entities
void smart_input::split_xinp(std::string& cur_xinp) const
{
	size_t pos = cur_xinp.find_first_of("([{");

	while (pos != std::string::npos)
	{
		cur_xinp.insert(pos, " ");

		if (pos == (cur_xinp.length() - 2))  // if this is the last character which should be a bracket no need to add a space after
			break;

		cur_xinp.insert((pos + 2), " ");    // add space both before and after the character

		pos = cur_xinp.find_first_of(",)]}", (pos + 3));  // start looking after pos+2 or it will keep looping and wrongly			
	}

	// by here the xinp should be separated nicely into a space separated string with space between brackets and nums and commas

}



//this checks the actual inp word to verify if the word is made only out of allowed characters and also in the correct order including signs and point
bool smart_input::check_num(std::string& num, char type) const
{
	if (type == 'i')  // if it is an integer
	{
		if (ifStrOnly(num, "-0123456789"))    //checking to see if the input is only int characters
		{
			size_t pos = num.find_first_of("-");   // first check if the sign exists or not

			if (pos != std::string::npos)  // if sign exists
			{
				if (pos == 0) // if sign exists and is at the first spot
				{
					pos = num.find_first_of("-", 1); //search the entire string from position 1 on and find out if another -ve sign exists

					if (pos == std::string::npos) // if it doesn't exist then input is a valid int
					{
						//std::cout << "Valid int entered!" << '\n';
						return true;
					}
					else  // if it does exist then pos wil be non zero and hence multiple -ve signs exist!
					{
						std::cout << "ERROR!!! Multiple -ve signs exist in the input!!!" << '\n';
						return false;
					}

				}
				else // here atleast 1 -ve sign exists but it is not at the beginning
				{
					std::cout << "ERROR!!! INVALID INPUT! sign not at the beggining in int!!!" << '\n';
					return false;
				}
			}
			else    // if the sign doesn't exist then valid int
			{
				//std::cout << "Valid Int entered!" << '\n';
				return true;
			}

		}
		else
		{
			std::cout << "ERROR!!! Input contains invalid characters that do not make up int!" << '\n';
			return false;
		}

	}
	else if (type == 'd') // or if is a double
	{
		if (ifStrOnly(num, "-.0123456789"))  // if the input only consists of valid numbers and dot and -ve sign
		{
			size_t pos_dot = num.find_first_of(".");  // first check if -ve sign exists
			size_t pos_sign = num.find_first_of("-");   // check to see if dot also exists

			if (pos_dot == std::string::npos && pos_sign == std::string::npos)  // if neither the -ve sign nor the dot exist then valid
			{
				//std::cout << "Valid double entered!" << '\n';
				return true;
			}
			else if (pos_dot == std::string::npos && pos_sign != std::string::npos)  // if dot doesn't exists but sign exists
			{
				if (pos_sign == 0) // if sign exists and is at the first position
				{
					pos_sign = num.find_first_of("-", 1); // check to see if another -ve sign exists after 0th pos

					if (pos_sign == std::string::npos)  // if no more -ve sign exists then valid
					{
						//std::cout << "Valid double entered!" << '\n';
						return true;
					}
					else  // atleast 2 -ve signs exist when pos_sign is not npos
					{
						std::cout << "Invalid!! Multiple -ve signs exist!!!" << '\n';
						return false;
					}
				}
				else // sign not at the first position so invalid
				{
					std::cout << "Invalid! -ve sign not at the beginning in input!" << '\n';
					return false;
				}
			}
			else if (pos_dot != std::string::npos && pos_sign == std::string::npos)  // if dot exists but -ve sign doesn't  --> if . is at beggining then also add 0 at the beggining
			{
				if (pos_dot == 0) // if . is at beginning then add zero at the beginning
				{
					num.insert(0, "0");
					pos_dot = num.find_first_of(".");
				}

				pos_dot = num.find_first_of(".", (pos_dot + 1));  // start looking for another . from position pos_dot+1

				if (pos_dot == std::string::npos) // if only one . exists then valid
				{
					//std::cout << "Valid double entered!" << '\n';
					return true;
				}
				else // multiple dots exist so invalid
				{
					std::cout << "Invalid!! Multiple dots exist in the input!" << '\n';
					return false;
				}
			}
			else if (pos_dot != std::string::npos && pos_sign != std::string::npos)  // if both exist  --> also add 0 at the beggining if . is at 2nd place
			{
				if (pos_sign == 0)  // proceed only if the sign is at 0th position
				{
					pos_sign = num.find_first_of("-", 1);  // look for another -ve sign

					if (pos_sign == std::string::npos)   // if another -ve sign doesn't exist 
					{
						if (pos_dot == 1)   // if input is without zero at the beginning of the input
						{
							num.insert(1, "0");
							pos_dot = num.find_first_of(".");  // or pos_dot=2, updating new position of dot
						}

						pos_dot = num.find_first_of(".", (pos_dot + 1));   // look for another dot

						if (pos_dot == std::string::npos)  // if another dot doesn't exist then valid
						{
							//std::cout << "Valid double entered!" << '\n';
							return true;
						}
						else  // another dot exists
						{
							std::cout << "Invalid! Multiple dots exist!" << '\n';
							return false;
						}

					}
					else  // another -ve sign exists 
					{
						std::cout << "Invalid! Multiple -ve signs exist!" << '\n';
						return false;
					}
				}
				else    // sign not at the beginning of input so invalid
				{
					std::cout << "Invalid!! sign not at the beginning of input!" << '\n';
					return false;
				}

			}
			else
			{
				std::cout << "ERROR!!! UNEXPECTED ERROR OCCURED IN 'bool smart_input::check_num(std::string&, char&) const' in 'smart_input.cpp' !!" << '\n';
				return false;
			}
		}
		else  // if not then not a valid double
		{
			std::cout << "ERROR!!! UNEXPECTED CHARACTERS IN DOUBLE INPUT!" << '\n';
			return false;
		}
	}
	else
	{
		std::cout << "ERROR!!! Unknown error occured in 'bool smart_input::check_num(std::string&, char&) const' in 'smart_input.cpp' !!" << '\n';
		return false;
	}
}





int smart_input::count_values(std::string str) const  // this counts no of values in cur_xinp word
{
	std::stringstream tmp(str);
	std::string word;

	int count{ 0 };

	while (tmp >> word)
	{
		++count;
	}

	if (count == 3)
		return 0;
	else
		return ((count - 2) / 2);
}



// count can also check for arbitrary no of values, in that case count return -1
int smart_input::count(std::string str, const char* type) const  // this returns the actual no of values in the xinp word
{
	int count{ 0 };
	std::stringstream strm(str);
	std::string word;

	if (type == "inp")
	{
		while (strm >> word)
			++count;

		return count;
	}
	else if (type == "xinp") // this counts the no of values in currrent xinp word that is being processed
	{
		while (strm >> word)
			++count;

		if (count == 1) // if there is only one xinp word
		{
			split_xinp(str);
			int v{ count_values(str) };  // v counts the no of values in the single xinp

			if (v == 0)  // if no values then return -1 for the count which means arbitrary no of input words
				return -1;
			else
				return 1;
		}
		else // return actual count here
			return count;
	}
	else    // this won't happen unless the programmer makes mistake in typing the xinp input string
	{
		std::cout << "ERROR!!! Unexpected error occured in 'size_t smart_input::count(std::string&, const char*) const' in 'smart_input.cpp'!" << '\n';
		return 99999;
	}


}



// this function creates and returns a 0 corrected stringstream for create
std::stringstream smart_input::create_strm() const
{
	std::stringstream tmp;

	int count_inp(count(inp, "inp")), count_xinp(count(xinp, "xinp")), i{ 1 };

	if (count_xinp == -1)
	{
		std::stringstream strm_inp(inp);
		std::string cur_inp;
		if (xinp[0] == 'd')
		{
			while (i <= count_inp)
			{
				strm_inp >> cur_inp;

				if (cur_inp[0] == '.')
					cur_inp.insert(0, "0");
				else if (cur_inp[0] == '-')
				{
					if (cur_inp[1] == '.')
						cur_inp.insert(1, "0");
				}
				tmp << cur_inp;

				if (i < count_inp)
					tmp << " ";

				++i;
			}

		}
		else
			tmp << inp;
	}
	else
	{
		std::stringstream strm_inp(inp), strm_xinp(xinp);
		std::string cur_inp, cur_xinp;

		while (i <= count_inp)
		{
			strm_inp >> cur_inp;
			strm_xinp >> cur_xinp;
			if (cur_xinp[0] == 'd')
			{
				if (cur_inp[0] == '.')
					cur_inp.insert(0, "0");
				else if (cur_inp[0] == '-')
				{
					if (cur_inp[1] == '.')
						cur_inp.insert(1, "0");
				}
			}

			tmp << cur_inp;

			if (i < count_inp)
				tmp << " ";

			++i;
		}

	}

	//std::cout << "stringstream successfully created!\n" << tmp.str() << '\n';

	return tmp;

}



void smart_input::print_strm() const
{
	std::cout << "Contents of stream : " << strm.str() << "\n";
}




void smart_input::reset()
{
	inp.clear();
	xinp.clear();

	strm.clear();
	strm.str("");

}

std::stringstream& smart_input::get_stream()
{
	return strm;
}

