#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
	public:
		class BadInputException : public std::exception
		{
			private:
				std::string _msg;

			public:
				BadInputException(const std::string& input): _msg("Error: bad input => " + input) {}

				virtual ~BadInputException() throw() {}

				virtual const char* what() const throw() {
					return _msg.c_str();
				}
		};

		class NegativeValueException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class TooLargeValueException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		BitcoinExchange(void);
		~BitcoinExchange(void);
		
		void	processDb(void);
		void	printDb(void);
		bool	checkValidDate(std::string date) const;
		bool	checkValidValue(float value) const;
		void	parseLine(const std::string& line);
		void    processFile(std::ifstream& file);
		float   getRate(const std::string &date);

	private:
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);

		std::string						_filename;
		std::map<std::string, float>    _db;
};

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
