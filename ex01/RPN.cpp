#include "RPN.hpp"

RPN::RPN(void)
{
    // std::cout << "RPN default constructor called" << std::endl;
}

RPN::RPN(const RPN& src)
{
    // std::cout << "RPN copy constructor called" << std::endl;
    (void) src;
}

RPN& RPN::operator=(const RPN& rhs)
{
    // std::cout << "RPN copy assignment operator called" << std::endl;
    (void) rhs;
    return *this;
}

RPN::~RPN(void)
{
    // std::cout << "RPN destructor called" << std::endl;
}

long long const &RPN::getRes(void) const
{
    return _stack.top();
}

void    RPN::calculate(const std::string & rpn)
{
    std::istringstream ss(rpn);
    std::string element;
    
    while (ss >> element)
    {
        if (element.length() == 1 && std::isdigit(element[0]))
            _stack.push(element[0] - '0');
        else if (isOpertor(element))
        {
            checkEnoughOpElement(_stack);
            doOp(element);
        }
        else
            throw std::runtime_error("Error");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");
}

void    RPN::doOp(std::string const & element)
{
    long long a, b;
    long long res;
    b = _stack.top();
    _stack.pop();
    a = _stack.top();
    _stack.pop();
    switch (element[0])
    {
    case '+':
        res = add(a, b);
        break;
    case '-':
        res = sub(a, b);
        break;
    case '*':
        res = mult(a, b);
        break;
    case '/':
        res = divide(a, b);
        break;
    default:
        break;
    }
    _stack.push(res);
}

/* UTILS */

bool    isOpertor(const std::string & element)
{
    if (element.length() == 1 && 
        (element[0] == '+' || element[0] == '-'
        || element[0] == '*' || element[0] == '/'))
        return true;
    return false;
}

void    checkEnoughOpElement(std::stack<long long> stack)
{
    if (stack.size() < 2)
        throw std::runtime_error("Error");
}

long long   add(int a, int b)
{
    return a + b;
}

long long   sub(int a, int b)
{
    return a - b;
}

long long   mult(int a, int b)
{
    return a * b;
}

long long   divide(int a, int b)
{
    if (b == 0)
        throw std::runtime_error("Error");
    return a / b;
}