#include "../includes/BitcoinExchange.h"

std::ostream & operator<<( std::ostream & o, const s_date & d)
{
	o << d._year << "-";
	if (d._month < 10)
		o << "0" << d._month << "-";
	else
		o << d._month << "-";
	if (d._day < 10)
		o << "0" << d._day;
	else
		o << d._day;
	return o;
}

void	get_part_date(int & struct_date, std::string date, int & x)
{
	std::string	date_str;
	double		temp;

	while (date[x] && date[x] != '-')
	{
		if (date[x] < '0' || date[x] > '9')
			throw std::runtime_error("Error : date must be a set of integers");
		date_str += date[x];
		x++;
	}
	temp = std::atof(date_str.c_str());
	if (temp < std::numeric_limits<int>::min() || temp > std::numeric_limits<int>::max())
		throw std::runtime_error("Error : date overflow");
	struct_date = temp;
}

void	verify_date(t_date & date_struct)
{
	if (date_struct._month < 1 || date_struct._month > 12)
		throw std::runtime_error("Error : date does not exist");
	if (date_struct._day < 1 || date_struct._day > 31 || (date_struct._month == 2 && date_struct._day > 29))
		throw std::runtime_error("Error : date does not exist");
	if (date_struct._month == 2 && date_struct._day == 29)
	{
		if (date_struct._year % 4 != 0)
			throw std::runtime_error("Error : date does not exist");
		if (date_struct._year % 100 == 0 && date_struct._year % 400 != 0 )
			throw std::runtime_error("Error : date does not exist");
	}
}

void	convert_line(std::string line, std::map<t_date,double> & map, char delimiter)
{
	t_date		date_struct;
	long double		_value;
	std::string	date;
	std::string	value;

	int i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != delimiter && line[i] != ' ')
		date += line[i++];
	while (line[i] && line[++i] && (line[i] == ' ' || line[i] == delimiter))
		;
	int x = 0;
	if (date[x] == '-')
		x++;
	get_part_date(date_struct._year, date, x);
	get_part_date(date_struct._month, date, ++x);
	get_part_date(date_struct._day, date, ++x);
	verify_date(date_struct);
	while (line[i])
	{
		if (line[i] != '.' && (line[i] < '0' || line[i] > '9'))
			throw std::invalid_argument("Error : value must be a positive integer");
		value += line[i];
		i++;
	}
	_value = std::atof(value.c_str());
	map[date_struct] = _value;
}

BitcoinExchange::BitcoinExchange()
{
	std::ifstream data_file("data.csv");

	if (!data_file)
		throw std::runtime_error("Error : Unable to open data file");

	try
	{
		std::string line;
		std::getline(data_file, line);
		if (line != "date,exchange_rate")
			throw std::runtime_error("Error : csv file doesn't have right format");
		while (std::getline(data_file, line))
		{
			if (!line.empty())
				convert_line(line, this->_data, ',');
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << " (data file)" << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(std::string data_filename)
{
	std::ifstream data_file(data_filename.c_str());

	if (!data_file)
		throw std::runtime_error("Error : Unable to open data file");

	try
	{
		std::string line;
		std::getline(data_file, line);
		if (line != "date,exchange_rate")
			throw std::runtime_error("Error : csv file doesn't have right format");
		while (std::getline(data_file, line))
		{
			if (!line.empty())
				convert_line(line, this->_data, ',');
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << " (data file)" << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &b)
{
	this->_data.insert(b._data.begin(), b._data.end());
}

BitcoinExchange::~BitcoinExchange()
{
}


BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange & b)
{
	this->_data.clear();
	this->_data.insert(b._data.begin(), b._data.end());
	return *this;
}

void	calculate_line(std::map<t_date, double> input, std::map<t_date, double> data)
{
	std::map<t_date, double>::iterator it = data.find(input.begin()->first);
	std::map<t_date, double>::iterator prev;

	if (it != data.end())
	{
		std::cout << input.begin()->first << " => " << input.begin()->second << " = " << it->second * input.begin()->second << std::endl;
		return ;
	}
	it = data.begin();
	prev = it;
	while (it != data.end())
	{
		if (input.begin()->first < it->first)
		{
			if (prev != it)
				std::cout << input.begin()->first << " => " << input.begin()->second << " = " << prev->second * input.begin()->second << std::endl;
			else
				std::cout << "No prior data to " << data.begin()->first << std::endl;
			return ;
		}
		prev = it;
		it++;
	}
	std::cout << input.begin()->first << " => " << input.begin()->second << " = " << data.rbegin()->second * input.begin()->second << std::endl;
}

void	try_convert(std::string line, std::map<t_date, double> data)
{
	try
	{
		std::map<t_date, double> input;
		convert_line(line, input, '|');
		if (input.begin()->second > 1000)
			throw std::invalid_argument("Error : too large a number");
		calculate_line(input, data);
		input.clear();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << " (input file)" << std::endl;
	}
}

void	BitcoinExchange::calculateWallet(std::string input_file)
{
	std::ifstream data_file(input_file.c_str());
	if (!data_file)
		throw std::runtime_error("Error : Unable to open input file");

	std::cout << std::fixed << std::setprecision(2);
	std::string line;
	std::getline(data_file, line);
	if (!line.empty() && line != "date | value")
		try_convert(line, this->_data);
	while (std::getline(data_file, line))
		if (!line.empty())
			try_convert(line, this->_data);
}