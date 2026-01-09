#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    this->_data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
	{
		this->_data = other._data;
	}

    return(*this);
}

BitcoinExchange::~BitcoinExchange() {}

int BitcoinExchange::compute(const char *file_name)
{
	if (!read_db())
	{
		std::cout << "Cannot open this file: data.csv !!\n";
		return (-1);
	}
	
	std::ifstream input (file_name);

	if (!input)
	{
		std::cout << "Cannot to open this file: " << file_name << " !!\n";
		return (-2);
	}

	std::string line;
	Input input_data;

	getline(input, line);
	while (getline(input, line))
	{
		if (line_is_valid(line))
		{
			input_data = extract_data(line);
			if (input_data.exchange < 0)
			{
				std::cout << "Error: not a positive number => " << line << "\n";
				continue;
			}
			if (input_data.exchange > 1000.0f)
			{
				std::cout << "Error: too large a number => " << line << "\n";
				continue;
			}
			std::cout << input_data.date << " => " << input_data.exchange <<
			 " = " << evaluate(input_data) << "\n";
		}
		else
			std::cout << "Error: bad input => " << line << "\n";
	}

	return(0);
}

float BitcoinExchange::evaluate(const Input input)
{
	for(std::map<std::string, float>::iterator it = _data.begin(); it != _data.end(); it++)
	{
		if (input.date == it->first)
			return (it->second * input.exchange);

		if (input.date < it->first)
		{
			if (it == _data.begin())
				return(-1);

			std::map<std::string, float>::iterator prev = it;
			prev--;

			return (prev->second * input.exchange);
		}
	}

	return(-2);
}

bool BitcoinExchange::read_db()
{
	std::ifstream data_file ("data.csv");

	if (!data_file)
		return (false);
	
	std::string line;

	while(getline(data_file, line))
	{
		if (invalid_line(line))
		{
			std::string price = line.substr(11, line.size() - 11);
			_data[line.substr(0, 10)] = strtof(price.c_str(), NULL);
		}
	}

	return(true);
}

bool BitcoinExchange::invalid_line(const std::string& line)
{
	if (line.size() <= 12)
		return (false);

	for (size_t i = 0; i < line.size() - 1; i++)
	{
		if ((line[i] < '0' || line[i] > '9') &&  line [i] != '-' && line [i] != ',' && line [i] != '.')
			return (false);

	}

	std::string year = line.substr(0, 4);
	
	if (year < "2009" || year > "2022")
		return (false);

	std::string month = line.substr(5, 2);
	
	if (month < "01" || month > "12")
		return (false);

	std::string day = line.substr(8, 2);
	
	if (month < "01" || month > "31")
		return (false);

	std::string price = line.substr(11, line.size() - 12);
	
	for (size_t i = 0; i < price.size() - 1; i++)
	{
		if (isdigit(price[i]) && price[i] == '.')
			return (false);
	}

	return (true);
}

bool BitcoinExchange::line_is_valid(const std::string& line)
{
	if (line.size() < 14)
		return (false);

	for (size_t i = 0; i < line.size() - 1; i++)
	{
		if ((line[i] < '0' || line[i] > '9') &&  line [i] != '-' && line [i] != '|' && line [i] != '.' && line [i] != ' ')
			return (false);

	}

	std::string year = line.substr(0, 4);
	
	if (year < "2009" || year > "2022")
		return (false);

	std::string month = line.substr(5, 2);
	
	if (month < "01" || month > "12")
		return (false);

	std::string day = line.substr(8, 2);
	
	if (month < "01" || month > "31")
		return (false);

	std::string exchange = line.substr(13, line.size() - 13);
	
	for (size_t i = 0; i < exchange.size() - 1; i++)
	{
		if (isdigit(exchange[i]) && exchange[i] == '.' && exchange[i] == '-')
			return (false);
	}

	return (true);
}

BitcoinExchange::Input BitcoinExchange::extract_data(const std::string& line)
{
	Input input;
	std::string exchange = line.substr(13, line.size() - 13);

	input.date = line.substr(0, 10);
	input.exchange = strtof(exchange.c_str(), NULL);

	return(input);
}

