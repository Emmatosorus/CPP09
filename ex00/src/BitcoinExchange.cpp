#include "../includes/BitcoinExchange.h"

void	get_part_date(int & struct_date, std::string date, int & x)
{
	std::string	date_str;
	double		temp;

	while (date[x] && date[x] != '-')
	{
		if (date[x] < '0' || date[x] > '9')
			throw std::runtime_error("BitcoinExchange : Incorrect date(s) in data.csv");
		date_str += date[x];
		x++;
	}
	temp = std::atof(date_str.c_str());
	if (temp < std::numeric_limits<int>::min() || temp > std::numeric_limits<int>::max())
		throw std::runtime_error("BitcoinExchange : Date overflow in data.csv");
	struct_date = temp;
}

void	verify_date(t_date & date_struct)
{
	if (date_struct._month < 1 || date_struct._month > 12)
		throw std::runtime_error("BitcoinExchange : Incorrect date(s) in data.csv");
	if (date_struct._day < 1 || date_struct._day > 31 || (date_struct._month == 2 && date_struct._day > 29))
		throw std::runtime_error("BitcoinExchange : Incorrect date(s) in data.csv");
	if (date_struct._month == 2 && date_struct._day == 29)
	{
		if (date_struct._year % 4 != 0)
			throw std::runtime_error("BitcoinExchange : Incorrect date(s) in data.csv");
		if (date_struct._year % 100 == 0 && date_struct._year % 400 != 0 )
			throw std::runtime_error("BitcoinExchange : Incorrect date(s) in data.csv");
	}
}

void	convert_line(std::string line, std::map<t_date,int> map)
{
	t_date		date_struct;
	long double		_value;
	std::string	date;
	std::string	value;

	int i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ',')
		date += line[i++];
	while (line[++i] && line[i] == ' ')
		;
	while (line[i])
	{
		if (line[i] != '.' && (line[i] < '0' || line[i] > '9'))
			throw std::runtime_error("BitcoinExchange : Incorrect value(s) in data.csv");
		value += line[i];
		i++;
	}
	_value = std::atof(value.c_str());
	int x = 0;
	get_part_date(date_struct._year, date, x);
	get_part_date(date_struct._month, date, ++x);
	get_part_date(date_struct._day, date, ++x);
	verify_date(date_struct);
//	std::cout << std::fixed << std::setprecision(2);
//	std::cout << date_struct._year << "-" << date_struct._month << "-" << date_struct._day << "," << _value << std::endl;
}

BitcoinExchange::BitcoinExchange()
{
	std::ifstream data_file("data.csv");

	if (!data_file)
		throw std::runtime_error("BitcoinExchange : Unable to open data file");

	std::string	line;
	std::getline(data_file, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("BitcoinExchange : csv file doesn't have right format");
	while (std::getline(data_file, line))
	{
		if (!line.empty())
			convert_line(line, this->_data);
	}
}