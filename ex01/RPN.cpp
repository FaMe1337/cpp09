/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:28 by marvin            #+#    #+#             */
/*   Updated: 2026/01/04 13:07:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

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

void RPN::calculate(double a, double b, char c)
{
	if (c == '+')
		this->_values.push(b + a);
	else if (c == '-')
		this->_values.push(b - a);
	else if (c == '*')
		this->_values.push(b * a);
	else if (c == '/' && a != 0)
		this->_values.push(b / a);
	else
		throw RPN::DivisionByZero();
}

/*		Alternative "Rigid" Parser (only accepts a string to a certain format digit or )

	for (std::string::iterator it = input.begin(); it <= input.end(); ++it)
	{
		if (isdigit(*it))
			numbers++;
		else if (input.size() > 1 && (*it == '+' || *it == '-' || *it == '*' || *it == '/'))
			symbols++;
		else
			throw RPN::InvalidInput();
		++it;
		std::cout << *it << std::endl;
		if (input.size() > 1 && it < input.end() && *it != ' ')
			throw RPN::InvalidInput();
	}
*/

RPN::RPN(std::string input)
{
	size_t symbols(0), numbers(0);

	for (std::string::iterator it = input.begin(); it <= input.end(); ++it)
	{
		if (isdigit(*it))
			numbers++;
		else if (input.size() > 1 && (*it == '+' || *it == '-' || *it == '*' || *it == '/'))
			symbols++;
		else
			throw RPN::InvalidInput();
		++it;
		if (input.size() > 1 && it < input.end() && *it != ' ')
			throw RPN::InvalidInput();
	}
	if (symbols != numbers - 1)
		throw RPN::InvalidInput();
	input = cleanInput(input, ' ');

	for (std::string::iterator it = input.begin(); it != input.end(); ++it)
	{
		if (isdigit(*it))
			this->_values.push(*it - 48);
		else if ((*it == '+' || *it == '-' || *it == '*' || *it == '/') && this->_values.size() > 1)
		{
			double a = this->_values.top();
			this->_values.pop();
			double b = this->_values.top();
			this->_values.pop();
			this->calculate(a, b, *it);
		}
		else
			throw RPN::InvalidInput();
	}
	if (this->_values.size() > 1)
		throw RPN::InvalidInput();
	else
		std::cout << this->_values.top() << std::endl;
}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
		this->_values = src._values;
	return (*this);
}

const char *RPN::InvalidInput::what() const throw()
{
	return ("Input is invalid");
}

const char *RPN::DivisionByZero::what() const throw()
{
	return ("Division by zero");
}