#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(std::string data);
		BitcoinExchange( const BitcoinExchange & b );
		~BitcoinExchange();

		BitcoinExchange & operator=( BitcoinExchange & b );

		void	calculateWallet(std::string input);

	private:
		std::map<std::string, int> _data;
};

#endif
