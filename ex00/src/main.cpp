#include "../includes/BitcoinExchange.h"
#include <iostream>

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw std::invalid_argument("Program must be given a filename as argument");
		BitcoinExchange b = BitcoinExchange("truc.csv");

		b.calculateWallet(av[1]);
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
