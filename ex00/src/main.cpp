#include "../includes/BitcoinExchange.h"
#include <iostream>

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw std::invalid_argument("Program must be given a filename as argument");
		BitcoinExchange();
		(void)av;
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
