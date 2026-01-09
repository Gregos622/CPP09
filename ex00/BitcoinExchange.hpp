#pragma once

#include <map>
#include <fstream>
#include <exception>
#include <string>
#include <iostream>
#include <cstdlib>


class BitcoinExchange
{
	private:
		struct Input
		{
			std::string date;
			float exchange;
		};
		std::map<std::string, float> _data;

		bool invalid_line(const std::string& line);
		float evaluate(const Input input);
		bool read_db();
		bool line_is_valid(const std::string& line);
		Input extract_data(const std::string& line);

	public:

		BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

		int compute(const char *file_name);
};

