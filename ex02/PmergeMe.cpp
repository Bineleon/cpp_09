#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    // std::cout << "PmergeMe default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
    (void) src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
    // std::cout << "PmergeMe copy assignment operator called" << std::endl;
        // copy attributs here
    (void) rhs;
    return *this;
}

PmergeMe::~PmergeMe(void)
{
    // std::cout << "PmergeMe destructor called" << std::endl;
}

std::vector<int>    PmergeMe::parse(int ac, char **input)
{
    std::vector<int> res;

    for (int i = 1; i < ac; ++i)
    {
        std::string element = input[i];

        if (element.empty())
            throw std::runtime_error("DEBUG: element empty");
        
        for (size_t j = 0; j < element.length(); ++j)
        {
            if (!std::isdigit(element[j]))
                throw std::runtime_error("DEBUG: not int");
        }

        std::istringstream iss(element);
        long long value;
        iss >> value;

        if (iss.fail() || !iss.eof())
            throw std::runtime_error("DEBUG: not int iss");
        
        if (value < 0 || value > INT_MAX)
            throw std::runtime_error("DEBUG: neg or > int_max");

        if (std::find(res.begin(), res.end(), static_cast<int>(value)) != res.end())
            throw std::runtime_error("DEBUG: double");

        res.push_back(static_cast<int>(value));
    }
    return res;
}