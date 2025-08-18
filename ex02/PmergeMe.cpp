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
        
        checkIfIsDigit(element);
        checkIsValidInt(element, res);
    }
    return res;
}


void PmergeMe::sort(std::vector<int> &vec)
{
    if (sortSmallVec(vec))
        return;
    
    std::vector<int> bigs;
    std::vector<int> smalls;
    size_t vecSize = vec.size();

    for (size_t i = 0; i < vecSize - 1; i += 2)
    {
        int a = vec[i];
        int b = vec[i + 1];
        if (a > b)
        {
            bigs.push_back(a);
            smalls.push_back(b);
        }
        else
        {
            bigs.push_back(b);
            smalls.push_back(a);
        }
    }

    bool isOddsize = (vecSize % 2 != 0);
    int orphan = 0;
    if (isOddsize)
        orphan = vec[vecSize - 1];

    std::cout << "Bigs : ";
    printVector(bigs);
    std::cout << "Smalls : ";
    printVector(smalls);
    sort(bigs);

    for (size_t i = 0; i < smalls.size(); ++i)
    {
        std::vector<int>::iterator limit = bigs.begin() + i + 1;
        std::vector<int>::iterator pos = std::lower_bound(bigs.begin(), limit, smalls[i]);
        bigs.insert(pos, smalls[i]);
    }

    if (isOddsize)
    {
        std::vector<int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), orphan);
        bigs.insert(pos, orphan);
    }

    vec = bigs;
}

/* UTILS */

std::vector<size_t> jacobsthal(size_t lim)
{
    std::vector<size_t> jacob;
    size_t j0 = 0;
    size_t j1 = 1;

    while (1)
    {
        size_t j2 = j1 + 2 * j0;
        if (j2 >= 3)
            jacob.push_back(j2);
        if (j2 > lim)
            break;
        j0 = j1;
        j1 = j2;
    }
    return jacob;
}

bool sortSmallVec(std::vector<int> & vec)
{
    if (vec.size() <= 1)
        return true;
    if (vec.size() == 2)
    {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
        return true;
    }
    return false;
}

void checkIfIsDigit(std::string const & element)
{
    for (size_t i = 0; i < element.length(); ++i)
    {
        if (!std::isdigit(element[i]))
            throw std::runtime_error("DEBUG: not int");
    }
}

void checkIsValidInt(std::string const & element, std::vector<int> &res)
{
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
