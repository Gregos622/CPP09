#pragma once

#include <vector>
#include <fstream>
#include <exception>
#include <string>
#include <iostream>
#include <cstdlib>

typedef struct s_file t_file;
typedef struct s_date t_date;

struct s_file
{
    //t_date date;
    std::string date;
    int price;
    int exchange;
};

struct s_date
{
    int year;
    int month;
    int day;
};

class BitcoinExchange
{
    private:
        std::vector<t_file> _file;

        bool invalid_line(std::string line);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void read_file();
};