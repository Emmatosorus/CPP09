#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <map>

typedef struct s_date
{
	int	_year;
	int	_month;
	int	_day;
}	t_date;

class BitcoinExchange
{
	public:
		BitcoinExchange();
//		BitcoinExchange(std::string data);
//		BitcoinExchange( const BitcoinExchange & b );
//		~BitcoinExchange();
//
//		BitcoinExchange & operator=( BitcoinExchange & b );
//
//		void	calculateWallet(std::string input);

	private:
		std::map<t_date, int> _data;
};

#endif
