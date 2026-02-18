/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:18:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 10:16:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <iterator> // std::distance

class Span {
public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int value);

    // Bulk add: checks capacity up-front and inserts efficiently
    template <typename InputIt>
    void addNumber(InputIt first, InputIt last) {
        // compute how many elements would be added
        std::size_t count = static_cast<std::size_t>(std::distance(first, last));
        if (_numbers.size() + count > _maxSize)
            throw std::out_of_range("Span is full: range does not fit");
        // reserve extra capacity if useful, then insert in one shot
        _numbers.insert(_numbers.end(), first, last);
    }

    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

private:
    unsigned int     _maxSize;
    std::vector<int> _numbers;
};

#endif