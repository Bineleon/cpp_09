#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
    std::cout << "BitcoinExchange default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    std::cout << "BitcoinExchange copy constructor called" << std::endl;
    *this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
    std::cout << "BitcoinExchange copy assignment operator called" << std::endl;
        // copy attributs here
    return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
    std::cout << "BitcoinExchange destructor called" << std::endl;
}
