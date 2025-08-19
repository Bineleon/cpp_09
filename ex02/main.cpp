#include "PmergeMe.hpp"
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
	if (ac < 2)
	{
		std::cerr << RED << "Error" << RESET << std::endl;
		return 1;
	}

	try
	{
		PmergeMe pmrg;
		std::vector<int> vec = pmrg.parse<std::vector<int> >(ac, av);
		std::cout << "Before: ";
		printContainer<std::vector<int> >(vec);
		pmrg.sort(vec);
		std::cout << "After: ";
		printContainer<std::vector<int> >(vec);

		std::deque<int> dq = pmrg.parse<std::deque<int> >(ac, av);
		std::cout << "Before: ";
		printContainer<std::deque<int> >(dq);
		pmrg.sort(dq);
		std::cout << "After: ";
		printContainer<std::deque<int> >(dq);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		return 1;
	}

    return 0;
}
