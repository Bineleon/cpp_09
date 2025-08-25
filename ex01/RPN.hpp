#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
	public:
		RPN(void);
		~RPN(void);
		void    calculate(const std::string & rpn);
		void    doOp(std::string const & element);
		long long const &getRes(void) const;

		
	private:
		RPN(const RPN& src);
		RPN& operator=(const RPN& rhs);
		std::stack<long long>   _stack;

};

bool    isOpertor(const std::string & element);
void    checkEnoughOpElement(std::stack<long long>);
long long   add(int a, int b);
long long   sub(int a, int b);
long long   mult(int a, int b);
long long   divide(int a, int b);

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
