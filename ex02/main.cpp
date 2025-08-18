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

bool isSorted(const std::vector<int>& vec)
{
	for (size_t i = 1; i < vec.size(); ++i)
    {
        if (vec[i - 1] > vec[i])
            return false;
    }
    return true;
}

void printVector(const std::vector<int>& vec)
{
	std::string color;
	if (isSorted(vec))
		color = SMGREEN;
	else
		color = SMYELLOW;

    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << color << *it;
        if (it + 1 != vec.end())
            std::cout << " ";
    }
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
		std::vector<int> vec = pmrg.parse(ac, av);
		std::cout << "Before: ";
		printVector(vec);
		pmrg.sort(vec);
		std::cout << "After: ";
		printVector(vec);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		return 1;
	}
	

    return 0;
}
