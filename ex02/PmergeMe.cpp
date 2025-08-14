#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    std::cout << "PmergeMe default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
    std::cout << "PmergeMe copy constructor called" << std::endl;
    *this = src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
    std::cout << "PmergeMe copy assignment operator called" << std::endl;
        // copy attributs here
    return *this;
}

PmergeMe::~PmergeMe(void)
{
    std::cout << "PmergeMe destructor called" << std::endl;
}
