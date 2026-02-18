/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:26:58 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 13:31:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

/**
 * @brief Declaration of the BitcoinExchange class 
 * used to evaluate bitcoin values by date.
 */

class BitcoinExchange
{
private:
    std::map<std::string, float> _data;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator=(const BitcoinExchange &copy);
    ~BitcoinExchange();

    void handleFile(std::ifstream &file);

    void checkDate(size_t year, size_t month, size_t day) const;
    void checkFormat(const std::string &date) const;
};

#endif