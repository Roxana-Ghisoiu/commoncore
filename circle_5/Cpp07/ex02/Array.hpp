#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef> // for std::size_t
#include <cstdlib> // std::srand, std::rand
#include <ctime>   // std::time


template <typename T>
class Array {
private:
    T*            _elements;
    unsigned int  _size;

public:
    // Constructors / Destructor
    Array();                          // empty
    explicit Array(unsigned int n);   // n default-initialized elements
    Array(const Array& other);        // deep copy
    ~Array();

    // Assignment
    Array& operator=(const Array& other);

    // Element access
    T&       operator[](unsigned int i);
    const T& operator[](unsigned int i) const;

    // Observers
    unsigned int size() const;

private:
    // Utility: no-throw swap to implement copy-and-swap assignment
    void swap(Array& other);
};

#include "Array.tpp"

#endif
