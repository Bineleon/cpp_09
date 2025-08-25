#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>
#include <algorithm>
#include <sys/time.h>

# define RESET "\033[0m"
# define SMRED "\033[0;31m"
# define SMGREEN "\033[0;32m"
# define SMYELLOW "\033[0;33m"
# define SMBLUE "\033[0;34m"
# define SMMAGENTA "\033[0;35m"
# define SMCYAN "\033[0;36m"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"

void                checkIfIsDigit(std::string const & element);

template <typename T>
void    checkIsValidInt(std::string const& element, T& res)
{
	std::istringstream iss(element);

	long long value;
	iss >> value;

	if (iss.fail() || !iss.eof())
		throw std::runtime_error("Error");
	
	if (value < 0 || value > INT_MAX)
		throw std::runtime_error("Error");

	if (std::find(res.begin(), res.end(), static_cast<int>(value)) != res.end())
		throw std::runtime_error("Error");
	res.push_back(static_cast<int>(value));
}

class PmergeMe
{
	public:
		PmergeMe(void);
		~PmergeMe(void);
		
		template <typename T>
		T    parse(int ac, char **input)
		{
			T res;

			for (int i = 1; i < ac; ++i)
			{
				std::string element = input[i];

				if (element.empty())
					throw std::runtime_error("Error");
				
				checkIfIsDigit(element);
				checkIsValidInt(element, res);
			}
			return res;
		}

		void                sort(std::vector<int> &vec);
		void                sort(std::deque<int> &dq);


		
	private:
		PmergeMe(const PmergeMe& src);
		PmergeMe& operator=(const PmergeMe& rhs);
		
};

bool                sortSmallCont(std::vector<int> & vec);
bool                sortSmallCont(std::deque<int> & dq);

void                boundedInsert(std::vector<int>& mainChain, int bigValue, int toInsert);
void                boundedInsert(std::deque<int>& mainChain, int bigValue, int toInsert);


int                 pairAndSort(std::vector<int> &vec, std::vector<int> &bigs, std::vector<std::pair<int, int> > &pairs, bool &hasOrphan);
int                 pairAndSort(std::deque<int> &dq, std::deque<int> &bigs, std::deque<std::pair<int, int> > &pairs, bool &hasOrphan);

void                insertSmall(std::vector<int> &bigs, std::vector<std::pair<int, int> > &pairs, bool &hasOrphan, int orphan);
void                insertSmall(std::deque<int> &bigs, std::deque<std::pair<int, int> > &pairs, bool &hasOrphan, int orphan);

std::vector<size_t> jacobsthal(size_t lim);
std::deque<size_t>  jacobsthalDeque(size_t lim);

std::vector<size_t> insertionIndex(size_t size);
std::deque<size_t>  insertionIndexDeque(size_t size);

template <typename T>
bool isSorted(const T& cont)
{
	for (size_t i = 1; i < cont.size(); ++i)
	{
		if (cont[i - 1] > cont[i])
			return false;
	}
	return true;
}

template <typename T>
void                printContainer(const T& cont)
{
	std::string color;
	if (isSorted(cont))
		color = SMGREEN;
	else
		color = SMYELLOW;

	for (typename T::const_iterator it = cont.begin(); it != cont.end(); ++it)
	{
		std::cout << color << *it;
		if (it + 1 != cont.end())
			std::cout << " ";
	}
	std::cout << RESET << std::endl;
}

template <typename T>
void    printPairs(const T& pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		std::cout << "[" << pairs[i].first << ", " << pairs[i].second << "]";
		if (i + 1 < pairs.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}

#endif
