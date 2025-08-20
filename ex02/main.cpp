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

static double	getTimestampUsec(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000000.0 + (double)tv.tv_usec);
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
		double start_timeV, end_timeV, start_timeD, end_timeD;
		std::vector<int> vec = pmrg.parse<std::vector<int> >(ac, av);
		std::cout << "Before: ";
		printContainer<std::vector<int> >(vec);

		start_timeV = getTimestampUsec();
		pmrg.sort(vec);
		end_timeV = getTimestampUsec();

		std::cout << "After: ";
		printContainer<std::vector<int> >(vec);

		std::cout << "Time to process a range of	" << vec.size() << " elements with std::vector	:	" <<  end_timeV - start_timeV<< " us\n";

		std::deque<int> dq = pmrg.parse<std::deque<int> >(ac, av);
		start_timeD = getTimestampUsec();
		pmrg.sort(dq);
		end_timeD = getTimestampUsec();

		std::cout << "Time to process a range of	" << dq.size() << " elements with std::deque	:	" << end_timeD - start_timeD << " us\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		return 1;
	}

    return 0;
}
