/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:56:09 by toferrei          #+#    #+#             */
/*   Updated: 2026/01/04 13:13:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP

# define BITCOINEXCHANGE_HPP

#include <map>
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
