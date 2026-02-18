/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:21:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/12 17:21:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n) : _maxSize(n), _numbers() {
    _numbers.reserve(n);
}

Span::Span(const Span &other)
    : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int value) {
    if (_numbers.size() >= _maxSize)
        throw std::out_of_range("Span is full: cannot add more numbers");
    _numbers.push_back(value);
}

unsigned int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
    for (std::size_t i = 1; i + 1 < sorted.size(); ++i) {
        int diff = sorted[i + 1] - sorted[i]; // non-negative thanks to sorting
        unsigned int udiff = static_cast<unsigned int>(diff);
        if (udiff < minSpan) minSpan = udiff;
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers to find a span");

    std::vector<int>::const_iterator minIt =
        std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt =
        std::max_element(_numbers.begin(), _numbers.end());

    // do the math in wider type to avoid signed overflow
    long long diff = static_cast<long long>(*maxIt) - static_cast<long long>(*minIt);
    if (diff < 0) diff = -diff; // defensive, though max>=min
    return static_cast<unsigned int>(diff);
}