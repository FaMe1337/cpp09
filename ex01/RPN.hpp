/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:25 by marvin            #+#    #+#             */
/*   Updated: 2026/01/04 13:07:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP

# define RPN_HPP
#include <stack>
#include <exception>
#include <iostream>

class RPN
{
	public :
		RPN();
		~RPN();
		RPN(std::string input);
		RPN(const RPN &src);
		RPN &operator=(const RPN &src);
		void calculate(double a, double b, char c);

		class InvalidInput : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

		class DivisionByZero : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};

	private :
		std::stack<double> _values;
};

#endif