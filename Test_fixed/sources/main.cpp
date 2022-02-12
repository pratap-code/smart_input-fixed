
#include "../headers/common.h"
#include "../headers/smart_input.h"
#include "../headers/fixed.h"


int main()
{
	smart_input inp;
	fixed f{};

	inp.get_input("Please enter an input in set d{2.4,-3.99}", "d{2.4,-3.99}");

	f.create(inp.get_stream());
	f.display();




	return 0;

}