#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
#include <algorithm>

class PmergeMe
{
    public:
        PmergeMe(void);
        ~PmergeMe(void);
        std::vector<int>    parse(int ac, char **input);
        void                sort(std::vector<int> &vec);

        
    private:
        PmergeMe(const PmergeMe& src);
        PmergeMe& operator=(const PmergeMe& rhs);
        
};

void                printVector(const std::vector<int>& vec);
void                checkIfIsDigit(std::string const & element);
void                checkIsValidInt(std::string const & element, std::vector<int> &res);
bool                sortSmallVec(std::vector<int> & vec);
std::vector<size_t> jacobsthal(size_t lim);
std::vector<size_t> insertionIndex(size_t size);

void boundedInsertByBig(std::vector<int>& mainChain, int bigValue, int smallValue);

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

#endif
