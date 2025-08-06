#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void): _filename("../data.csv")
{
    // std::cout << "BitcoinExchange default constructor called" << std::endl;
    processDb();
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

void	BitcoinExchange::beErrMsg(std::string msg)
{
	std::cerr << RED << "Error: " << msg << RESET << std::endl;
}

void	BitcoinExchange::printDb(void)
{
    for (std::map<std::string, float>::iterator it = _db.begin(); it != _db.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
}

void	BitcoinExchange::processDb(void)
{
    std::ifstream dbFile(_filename.c_str());

    if (!dbFile.is_open())
    {
        beErrMsg("could not open db file");
        return;
    }
    std::string line;
    std::getline(dbFile, line);

    while (std::getline(dbFile, line))
    {
        std::istringstream ss(line);
        std::string date, value;

        if (std::getline(ss, date, ',') && std::getline(ss, value))
            _db[date] = std::strtof(value.c_str(), NULL);
    }
}

bool    checkLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
       return true;
    else
        return false;
}

std::map<int, int> getDaysInMonths(int year)
{
    std::map<int, int> daysInMonth;
    
    daysInMonth[1]  = 31;
    daysInMonth[2]  = (checkLeapYear(year) ? 29 : 28);
    daysInMonth[3]  = 31;
    daysInMonth[4]  = 30;
    daysInMonth[5]  = 31;
    daysInMonth[6]  = 30;
    daysInMonth[7]  = 31;
    daysInMonth[8]  = 31;
    daysInMonth[9]  = 30;
    daysInMonth[10] = 31;
    daysInMonth[11] = 30;
    daysInMonth[12] = 31;

    return daysInMonth;
}

bool	BitcoinExchange::checkValidDate(std::string date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year, month, day;
    std::istringstream sYear(date.substr(0, 4));
    std::istringstream sMonth(date.substr(5, 2));
    std::istringstream sDay(date.substr(8, 2));
    
    if (!(sYear >> year) || !(sMonth >> month) || !(sDay >> day))
        return false;
    if (month < 1 || month > 12 || day < 1)
        return false;
    if (year < 2009)
        return false;
    std::map<int, int> daysInMonth = getDaysInMonths(year);
    if (day > daysInMonth[month])
        return false;
    return true;
}

bool	BitcoinExchange::checkValidValue(float value) const
{
    if (value < 0 || value > 1000)
        return false;
    return true;
}

void parseLine(const std::string& line, const BitcoinExchange& btc)
{
    size_t sep = line.find('|');
    if (sep == std::string::npos)
        throw BitcoinExchange::BadInputException(line);

    std::string date = trim(line.substr(0, sep));
    std::string sValue = trim(line.substr(sep + 1));

    if (!btc.checkValidDate(date))
        throw BitcoinExchange::BadInputException(date);

    float value;
    char* end;

    value = std::strtof(sValue.c_str(), &end);

    if (!checkValidValue(value))
    {
        if (value < 0)
            throw BitcoinExchange::NegativeValueException();
        if (value > 1000)
            throw BitcoinExchange::TooLargeValueException();
        throw BitcoinExchange::BadInputException(sValue);
    }

    float rate = btc.getRateForDate(date);
    
    std::cout << date << " => " << value << " = " << rate * value << std::endl;
}
