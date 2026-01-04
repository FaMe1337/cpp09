/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:56:09 by toferrei          #+#    #+#             */
/*   Updated: 2025/10/31 17:41:35 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP

# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <vector>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(std::fstream *inputFile, std::fstream *dataBaseToCompare, std::string inputFileName);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);

		void comparator() const;

		class FailedConvertion : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

		class InvalidInput : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

		class InvalidDate : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

		class NegativeValue : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

		class ValueTooBig : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

	private:
		std::map<int, float> _dataBase;
		std::vector<std::string> _secondDataBase;
		std::string _inputFileName;

};

#endif
