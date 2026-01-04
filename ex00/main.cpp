/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:55:24 by toferrei          #+#    #+#             */
/*   Updated: 2025/10/31 16:40:30 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char **argv)
{

	
	if (argc == 2 )
	{
		std::fstream dB, inputFile;
		dB.open("data.csv");
		if (!dB.is_open())
		{
			std::cerr << "Error: CSV file not found" << std::endl;
			return (1);
		}
		try
		{
			
			inputFile.open(argv[1]);
			if (!inputFile.is_open())
			{
				std::cerr << "Error: Input file not found" << std::endl;
				return (1);
			}
			BitcoinExchange bitcoin(&dB, &inputFile, argv[1]);
			bitcoin.comparator();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		return (0);
	}
	std::cerr << "Error: Wrong number of arguments" << std::endl;
	return (1);
}