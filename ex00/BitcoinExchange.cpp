#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    read_file();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    (void) other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    (void) other;

    return(*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::read_file()
{
	std::ifstream data_file ("data.csv");
	t_file file;

	if (!data_file)
		throw std::runtime_error("Unable to open this file <<data.csv>> !!");
	
	std::string line;

	while(getline(data_file, line))
	{
        std::cout << "Test 1\n";
		if (invalid_line(line))
		{
			file.date = line.substr(0, 10);
            std::string sPrice = line.substr(11, line.size() - 12);
			file.price = atoi(sPrice.c_str());
			_file.push_back(file);
            std::cout << "Test 2\n";
		}
	}

	for (size_t i = 0; i < _file.size() - 1; i++)
    {
        std::cout << "Date: " << _file[i].date << ", Price: " << _file[i].price << "\n";
    }
}

bool BitcoinExchange::invalid_line(std::string line)
{
	int i = 0;

	while (line[i])
	{
		if ((line[i] < '0' || line[i] > '9') ||  line [i] != '-' || line [i] != ',')
			return (false);
		i++;
	}

	std::string year = line.substr(0, 4);
	
	if (year < "2009" || year > "2030")
		return (false);

	std::string month = line.substr(5, 2);
	
	if (month < "01" || month > "12")
		return (false);

	std::string day = line.substr(8, 2);
	
	if (month < "01" || month > "31")
		return (false);

	std::string price = line.substr(11, line.size() - 12);
	
	for (size_t j = 0; j < price.size() - 1; j++)
	{
		if (!isdigit(price[j]))
			return (false);
	}

	return (true);
}