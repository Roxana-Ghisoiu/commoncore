/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:30:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 13:34:38 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cctype>

/**
 * @brief Implementation of the BitcoinExchange class
 *  that loads a CSV database and evaluates input lines.
 */

static std::string trim(const std::string &s)
{
    std::string::size_type start = 0;
    while (start < s.size() &&
           std::isspace(static_cast<unsigned char>(s[start])))
        ++start;

    std::string::size_type end = s.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;

    return s.substr(start, end - start);
}

BitcoinExchange::BitcoinExchange()
{
    std::ifstream file("data.csv");
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    if (std::getline(file, line))
    {
        if (line.find(',') == std::string::npos ||
            line.find("date") == std::string::npos)
        {
            std::string::size_type comma = line.find(',');
            if (comma != std::string::npos)
            {
                std::string date = trim(line.substr(0, comma));
                std::string valueStr = trim(line.substr(comma + 1));
                std::istringstream ss(valueStr);
                float value;
                if (ss >> value)
                    _data[date] = value;
            }
        }
    }

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::string::size_type comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, comma));
        std::string valueStr = trim(line.substr(comma + 1));

        std::istringstream ss(valueStr);
        float value;
        if (!(ss >> value))
            continue;

        _data[date] = value;
    }

    file.close();

    if (_data.empty())
        throw std::runtime_error("Error: database is empty.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    this->_data = copy._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
    if (this != &copy)
        this->_data = copy._data;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::checkFormat(const std::string &date) const
{
    if (date.size() != 10)
        throw std::runtime_error("bad date format");

    if (date[4] != '-' || date[7] != '-')
        throw std::runtime_error("bad date format");

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            throw std::runtime_error("bad date format");
    }
}

void BitcoinExchange::checkDate(size_t year, size_t month, size_t day) const
{
    if (month < 1 || month > 12 || day < 1 || day > 31)
        throw std::runtime_error("invalid date");

    bool leap = false;
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        leap = true;

    if (month == 2)
    {
        if ((!leap && day > 28) || (leap && day > 29))
            throw std::runtime_error("invalid date");
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            throw std::runtime_error("invalid date");
    }
}

void BitcoinExchange::handleFile(std::ifstream &file)
{
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        if (line == "date | value")
            continue;

        std::string original = line;

        std::string::size_type pipe = line.find('|');
        if (pipe == std::string::npos)
        {
            std::cerr << "Error: bad input => " << original << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pipe));
        std::string valueStr = trim(line.substr(pipe + 1));

        try
        {
            checkFormat(date);
        }
        catch (const std::exception &)
        {
            std::cerr << "Error: bad input => " << original << std::endl;
            continue;
        }

        size_t year = std::atoi(date.substr(0, 4).c_str());
        size_t month = std::atoi(date.substr(5, 2).c_str());
        size_t day = std::atoi(date.substr(8, 2).c_str());

        try
        {
            checkDate(year, month, day);
        }
        catch (const std::exception &)
        {
            std::cerr << "Error: bad input => " << original << std::endl;
            continue;
        }

        if (valueStr.empty())
        {
            std::cerr << "Error: bad input => " << original << std::endl;
            continue;
        }

        double value;
        {
            std::istringstream iss(valueStr);
            iss >> value;
            if (iss.fail())
            {
                std::cerr << "Error: bad input => " << original << std::endl;
                continue;
            }
            char c;
            if (iss >> c)
            {
                std::cerr << "Error: bad input => " << original << std::endl;
                continue;
            }
        }

        if (value < 0.0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        if (_data.empty())
        {
            std::cerr << "Error: bad input => " << original << std::endl;
            continue;
        }

        std::map<std::string, float>::const_iterator it = _data.lower_bound(date);

        if (it == _data.end())
        {
            --it;
        }
        else if (it->first != date)
        {
            if (it == _data.begin())
            {
                std::cerr << "Error: bad input => " << original << std::endl;
                continue;
            }
            --it;
        }

        double result = value * static_cast<double>(it->second);
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}