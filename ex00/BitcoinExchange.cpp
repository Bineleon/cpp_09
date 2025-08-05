#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void): _db("data.csv")
{
    // std::cout << "BitcoinExchange default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    // std::cout << "BitcoinExchange copy constructor called" << std::endl;
    (void) src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
    // std::cout << "BitcoinExchange copy assignment operator called" << std::endl;
    (void) rhs;
    return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
    // std::cout << "BitcoinExchange destructor called" << std::endl;
}
