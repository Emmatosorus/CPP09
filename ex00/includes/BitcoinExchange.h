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

	bool operator<(const s_date & other) const
	{
		if (_year != other._year)
			return _year < other._year;
		if (_month != other._month)
			return _month < other._month;
		return _day < other._day;
	}
	bool operator>(const s_date & other) const
	{
		if (_year != other._year)
			return _year > other._year;
		if (_month != other._month)
			return _month > other._month;
		return _day > other._day;
	}

	bool operator==(const s_date & other) const
	{
		return (_year == other._year && _month == other._month && _day == other._day);
	}

	s_date & operator=(const s_date & other)
	{
		_year = other._year;
		_month = other._month;
		_day = other._day;
		return *this;
	}
}	t_date;

std::ostream & operator<<( const std::ostream & o, s_date & d);

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(std::string data_filename);
		BitcoinExchange( const BitcoinExchange & b );
		~BitcoinExchange();

		BitcoinExchange & operator=( BitcoinExchange & b );

		void	calculateWallet(std::string input_file);

	private:
		std::map<t_date, double> _data;
};

#endif
