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

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> bigs;

    size_t vecSize = vec.size();
    bool hasOrphan = (vecSize % 2 != 0);
    int orphan = 0;

    for (size_t i = 0; i + 1 < vecSize; i += 2)
    {
        int big = std::max(vec[i], vec[i + 1]);
        int small = std::min(vec[i], vec[i + 1]);
        pairs.push_back(std::make_pair(big, small));
    }

    if (hasOrphan)
        orphan = vec[vecSize - 1];

    for (size_t i = 0; i < pairs.size(); ++i)
        bigs.push_back(pairs[i].first);

    sort(bigs);

    if (!pairs.empty())
        boundedInsertByBig(bigs, pairs[0].first, pairs[0].second);

    std::vector<size_t> order = insertionIndex(pairs.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        boundedInsertByBig(bigs, pairs[idx].first, pairs[idx].second);
    }

    if (hasOrphan)
    {
        std::vector<int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), orphan);
        bigs.insert(pos, orphan);
    }

    vec = bigs;
}

void boundedInsertByBig(std::vector<int>& mainChain, int bigValue, int smallValue)
{
    std::vector<int>::iterator bigIt = std::find(mainChain.begin(), mainChain.end(), bigValue);
    if (bigIt == mainChain.end())
        return;
    std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), bigIt + 1, smallValue);
    mainChain.insert(pos, smallValue);
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

std::vector<size_t> insertionIndex(size_t size)
{
    std::vector<size_t> indexToInsert;
    std::vector<size_t> jacob = jacobsthal(size);

    size_t prev = 1;
    for (size_t k = 0; k < jacob.size(); ++k)
    {
        size_t j = jacob[k];
        size_t limit = (j < size) ? j : size;

        for (size_t i = limit; i > prev; --i)
            indexToInsert.push_back(i - 1);

        prev = j;
        if (prev >= size)
            break;
    }

    if (prev < size)
    {
        for (size_t i = size; i > prev; --i)
            indexToInsert.push_back(i - 1);
    }

    return indexToInsert;
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
