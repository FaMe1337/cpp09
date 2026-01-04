/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:00:14 by toferrei          #+#    #+#             */
/*   Updated: 2026/01/04 16:34:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): _dataBase(src._dataBase),
															_secondDataBase(src._secondDataBase),
															_inputFileName(src._inputFileName){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->_dataBase = src._dataBase;
		this->_secondDataBase = src._secondDataBase;
		this->_inputFileName = src._inputFileName;
	}
	return (*this);
}

std::string cleanInput(std::string input, char c)
{
	for (std::string::iterator it = input.begin(); it < input.end(); it++)
	{
		if (*it == c)
		{
			input.erase(it);
			it--;
		}
	}
	return (input);
}

int datetoint(std::string date)
{
	date = cleanInput(date, '-');
	return (std::atoi(date.c_str()));
}

BitcoinExchange::BitcoinExchange(std::fstream *inputFile, std::fstream *dataBaseToCompare, std::string inputFileName): _inputFileName(inputFileName)
{
	std::string strtmp, btcValue;
	float value;
	char *Nullpointer = NULL;
	int key;

	while (std::getline(*inputFile, strtmp))
	{
		if (strtmp != "date,exchange_rate")
		{
			key = datetoint(strtmp.substr(0, strtmp.find(",")));
			btcValue = strtmp.substr(strtmp.find(",") + 1);
			value = std::strtof(btcValue.c_str(), &Nullpointer);
			if (Nullpointer == btcValue.c_str())
				throw BitcoinExchange::FailedConvertion();
			this->_dataBase.insert(std::make_pair(key, value));
		}
	}
	int i = 0;
	while (std::getline(*dataBaseToCompare, strtmp))
	{
		(this->_secondDataBase).insert((this->_secondDataBase).end(), strtmp);
		i++;
	}
}

bool inputTester(char c)
{
	if (isdigit(c) || c == '|' || c == '-' || c == '.')
		return (1);
	return (0);
}

void isInputValid(std::string input)
{
	size_t pipe = 0;

	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		if (*it == '|')
			pipe++;
		if (!inputTester(*it))
			throw BitcoinExchange::InvalidInput();
	}
	if (pipe != 1)
		throw BitcoinExchange::InvalidInput();
}

bool isLeapYear(int year)
{
	if (year % 4 && year % 100 && year % 400)
		return 0;
	return 1;
}

int evenMonth(int month)
{
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 1;
		case 4: case 6: case 9: case 11:
			return 0;
		case 2:
			return 2;
		default: return 0;
	}
}

void isDateValid(std::string date)
{
	size_t year, month, day;
	std::string tmp;
	size_t dash = 0;

	for (std::string::iterator it = date.begin(); it != date.end(); it++)
		if (*it == '-')
			dash++;
	if (dash != 2)
		throw BitcoinExchange::InvalidInput();
	tmp = date.substr(0, date.find('-'));
	year = std::atoi(tmp.c_str());
	if (tmp.size() != 4 || year < 2000)
		throw BitcoinExchange::InvalidDate();
	date = date.substr(date.find('-') + 1);
	tmp = date.substr(0, date.find('-'));
	month = std::atoi(tmp.c_str());
	date = date.substr(date.find('-') + 1);
	day = std::atoi(date.c_str());
	if ((tmp.size() > 2 || month > 12 || month < 1)
		|| (date.size() > 2 || day > 31 || day < 1)
		|| (month == 2 && day >= 29 && !isLeapYear(year))
		|| (!evenMonth(month) && day > 30))
		throw BitcoinExchange::InvalidDate();
}

float isValueValid(std::string input)
{
	char *Nullpointer;
	float value;

	value = std::strtof(input.c_str(), &Nullpointer);
	if (Nullpointer == input.c_str())
		throw BitcoinExchange::FailedConvertion();
	if (value < 0)
		throw BitcoinExchange::NegativeValue();
	if (value > 1000)
		throw BitcoinExchange::ValueTooBig();
	return (value);
}

void BitcoinExchange::comparator() const
{
	std::string strtmp, tmp, date;
	float value;
	size_t i = 1;
	while (i - 1 < this->_secondDataBase.size())
	{
		strtmp = this->_secondDataBase.at(i - 1);
		if (strtmp != "date | value")
		{
			try
			{
				tmp = cleanInput(strtmp, ' ');
				isInputValid(tmp);
				date = tmp.substr(0, tmp.find("|"));
				isDateValid(date);
				value = isValueValid(tmp.substr(tmp.find("|") + 1));
				if (datetoint(date) < this->_dataBase.begin()->first)
				{
					std::cout << date << " => " << value << " = " << value * this->_dataBase.begin()->second << std::endl;
				}
				std::map<int, float>::const_iterator search = this->_dataBase.upper_bound(datetoint(tmp.substr(0, tmp.find("|"))));
				if (search != this->_dataBase.end())
					search--;
				std::cout << date << " => " << value << " = " << value * search->second << std::endl;
				


			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				std::cout << "In file " << this->_inputFileName << " line " << i << " ==> " << strtmp << std::endl;
			}
		}
		i++;
	}
}

const char *BitcoinExchange::FailedConvertion::what() const throw()
{
	return ("Error: Failed convertion");
}

const char *BitcoinExchange::InvalidInput::what() const throw()
{
	return ("Error: Invalid input");
}

const char *BitcoinExchange::InvalidDate::what() const throw()
{
	return ("Error: Invalid date");
}

const char *BitcoinExchange::NegativeValue::what() const throw()
{
	return ("Error: Negative Value");
}

const char *BitcoinExchange::ValueTooBig::what() const throw()
{
	return ("Error: Value is too big");
}
