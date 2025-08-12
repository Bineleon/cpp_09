#include "RPN.hpp"
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

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: use this format : <rpn>";
		return 1;
	}
	
	try
	{
		RPN rpn;
		rpn.calculate(av[1]);
		std::cout << rpn.getRes() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
		return 1;
	}
	

    return 0;
}
