#include "../includes/RPN.h"
#include <iostream>

int main(int ac, char **av)
{
	try
	{
		std::string	input;
		if (ac != 2)
			throw std::invalid_argument("RPN must be given 1 argument only");
		if (av[1][0] == 0)
			throw std::invalid_argument("RPN must be given at least 2 digits and an operator");
		parse(input, av[1]);
		std::cout << calculate(input) << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Error : " << e.what() << std::endl;
		return (1);
	}
}
