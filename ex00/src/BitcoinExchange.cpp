#include "../includes/BitcoinExchange.h"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream data_file("data.csv");

	if (!data_file)
		throw std::runtime_error("BitcoinExchange : Unable to open data file");

	std::string	line;

	while (std::getline(data_file, line))
	{
		// call function to parse line
	}
}