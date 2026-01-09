#include "BitcoinExchange.hpp"
#include <map>
#include <iostream>
#include <string>
#include <stdint.h>

int main (int ac, char **av)
{
	if (ac == 2)
	{
		BitcoinExchange btc;

		btc.compute(av[1]);
	}
	else
		std::cout << "Not enought parameter ./btc <input_file.txt>\n";

    return(0);
}