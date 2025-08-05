#include "BitcoinExchange.hpp"
#include <iomanip>

void printHeader(const std::string& str)
{
	int size = 50;
	int totalPad = size - str.size();
	(totalPad < 0) ? totalPad = 0 : totalPad;
	int lPad = totalPad / 2;
	int rPad = totalPad - lPad;

	std::cout << std::endl << SMGREEN;
	std::cout << std::setfill('=') << std::setw(size) << "" << std::endl;
	std::cout << std::setfill(' ') << std::setw(lPad + str.size()) << str << std::setw(rPad) << "" << std::endl;
	std::cout << std::setfill('=') << std::setw(size) << "" << std::endl;
	std::cout << RESET << std::endl;
}

void	errMsg(std::string msg)
{
	std::cerr << RED << "Error: " << msg << RESET << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1])
	{
		errMsg("could not open file.");
		return 1;
	}

	std::ifstream myFile(av[1]);
    if (!myFile.is_open())
    {
		errMsg("could not open file.");
		return 1;
    }
	
	myFile.close();
	
    return 0;
}

