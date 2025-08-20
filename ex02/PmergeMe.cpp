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


void    PmergeMe::sort(std::vector<int> &vec)
{
    if (sortSmallCont(vec))
        return;

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> bigs;

    size_t vecSize = vec.size();
    bool hasOrphan = (vecSize % 2 != 0);
    int orphan = pairAndSort(vec, bigs, pairs, hasOrphan);

    // std::cout << "Bigs before sort: ";
    // printContainer(bigs);
    // std::cout << "Pairs : ";
    // printPairs(pairs);

    sort(bigs);

    // std::cout << "Bigs after sort: ";
    // printContainer(bigs);
    // std::cout << "Pairs : ";
    // printPairs(pairs);


    insertSmall(bigs, pairs, hasOrphan, orphan);

    vec = bigs;
}


/* UTILS */

void    boundedInsert(std::vector<int>& mainChain, int bigValue, int toInsert)
{
    std::vector<int>::iterator bigIt = std::find(mainChain.begin(), mainChain.end(), bigValue);
    if (bigIt == mainChain.end())
        return;
    std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), bigIt + 1, toInsert);
    mainChain.insert(pos, toInsert);
}

int    pairAndSort(std::vector<int> &vec, std::vector<int> &bigs, std::vector<std::pair<int, int> > &pairs, bool &hasOrphan)
{
    size_t vecSize = vec.size();
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

    return orphan;
}

void    insertSmall(std::vector<int> &bigs, std::vector<std::pair<int, int> > &pairs, bool &hasOrphan, int orphan)
{
    if (!pairs.empty())
        boundedInsert(bigs, pairs[0].first, pairs[0].second);

    std::vector<size_t> order = insertionIndex(pairs.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        boundedInsert(bigs, pairs[idx].first, pairs[idx].second);
    }
    if (hasOrphan)
    {
        std::vector<int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), orphan);
        bigs.insert(pos, orphan);
    }
}

void    checkIfIsDigit(std::string const & element)
{
    for (size_t i = 0; i < element.length(); ++i)
    {
        if (!std::isdigit(element[i]))
            throw std::runtime_error("Error");
    }
}

bool isSorted(const std::vector<int>& cont)
{
    for (std::size_t i = 1; i < cont.size(); ++i)
        if (cont[i - 1] > cont[i])
            return false;
    return true;
}


bool sortSmallCont(std::vector<int>& cont)
{
    if (cont.size() <= 1)
        return true;
    if (cont.size() == 2)
    {
        if (cont[0] > cont[1])
            std::swap(cont[0], cont[1]);
        return true;
    }
    return false;
}

std::vector<std::size_t> jacobsthal(std::size_t lim)
{
    std::vector<std::size_t> jacob;
    std::size_t j0 = 0;
    std::size_t j1 = 1;

    while (1)
    {
        std::size_t j2 = j1 + 2 * j0;
        if (j2 >= 3)
            jacob.push_back(j2);
        if (j2 > lim)
            break;
        j0 = j1;
        j1 = j2;
    }
    return jacob;
}

std::vector<std::size_t> insertionIndex(std::size_t size)
{
    std::vector<std::size_t> indexToInsert;
    std::vector<std::size_t> jacob = jacobsthal(size);

    std::size_t prev = 1;
    for (std::size_t k = 0; k < jacob.size(); ++k)
    {
        std::size_t j = jacob[k];
        std::size_t limit = (j < size) ? j : size;

        for (std::size_t i = limit; i > prev; --i)
            indexToInsert.push_back(i - 1);

        prev = j;
        if (prev >= size)
            break;
    }

    if (prev < size)
    {
        for (std::size_t i = size; i > prev; --i)
            indexToInsert.push_back(i - 1);
    }
    return indexToInsert;
}

/* DEQUE */


bool sortSmallCont(std::deque<int>& cont)
{
    if (cont.size() <= 1)
        return true;
    if (cont.size() == 2)
    {
        if (cont[0] > cont[1])
            std::swap(cont[0], cont[1]);
        return true;
    }
    return false;
}

void    PmergeMe::sort(std::deque<int> &dq)
{
    if (sortSmallCont(dq))
        return;

    std::deque<std::pair<int, int> > pairs;
    std::deque<int> bigs;

    size_t dqSize = dq.size();
    bool hasOrphan = (dqSize % 2 != 0);
    int orphan = pairAndSort(dq, bigs, pairs, hasOrphan);

    // std::cout << "Bigs before sort: ";
    // printContainer<std::deque<int> >(bigs);
    // std::cout << "Pairs : ";
    // printPairs(pairs);

    sort(bigs);

    // std::cout << "Bigs after sort: ";
    // printContainer<std::deque<int> >(bigs);
    // std::cout << "Pairs : ";
    // printPairs(pairs);


    insertSmall(bigs, pairs, hasOrphan, orphan);

    dq = bigs;
}

/* UTILS */

void    boundedInsert(std::deque<int>& mainChain, int bigValue, int toInsert)
{
    std::deque<int>::iterator bigIt = std::find(mainChain.begin(), mainChain.end(), bigValue);
    if (bigIt == mainChain.end())
        return;
    std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), bigIt + 1, toInsert);
    mainChain.insert(pos, toInsert);
}

int    pairAndSort(std::deque<int> &dq, std::deque<int> &bigs, std::deque<std::pair<int, int> > &pairs, bool &hasOrphan)
{
    size_t dqSize = dq.size();
    int orphan = 0;

    for (size_t i = 0; i + 1 < dqSize; i += 2)
    {
        int big = std::max(dq[i], dq[i + 1]);
        int small = std::min(dq[i], dq[i + 1]);
        pairs.push_back(std::make_pair(big, small));
    }

    if (hasOrphan)
        orphan = dq[dqSize - 1];

    for (size_t i = 0; i < pairs.size(); ++i)
        bigs.push_back(pairs[i].first);

    return orphan;
}

void    insertSmall(std::deque<int> &bigs, std::deque<std::pair<int, int> > &pairs, bool &hasOrphan, int orphan)
{
    if (!pairs.empty())
        boundedInsert(bigs, pairs[0].first, pairs[0].second);

    std::deque<size_t> order = insertionIndexDeque(pairs.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        boundedInsert(bigs, pairs[idx].first, pairs[idx].second);
    }
    if (hasOrphan)
    {
        std::deque<int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), orphan);
        bigs.insert(pos, orphan);
    }
}

std::deque<size_t> jacobsthalDeque(size_t lim)
{
    std::deque<size_t> jacob;
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

std::deque<size_t> insertionIndexDeque(size_t size)
{
    std::deque<size_t> indexToInsert;
    std::deque<size_t> jacob = jacobsthalDeque(size);

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
