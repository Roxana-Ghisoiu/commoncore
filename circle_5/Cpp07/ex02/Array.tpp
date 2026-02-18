#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"
#include <stdexcept> // std::out_of_range

// Empty array
template <typename T>
Array<T>::Array() : _elements(0), _size(0) {}

// n default-initialized elements
template <typename T>
Array<T>::Array(unsigned int n) : _elements(0), _size(n) {
    if (_size > 0) {
        // value-initialize elements (e.g., int -> 0, std::string -> "")
        _elements = new T[_size]();
    }
}

// Deep copy
template <typename T>
Array<T>::Array(const Array& other) : _elements(0), _size(other._size) {
    if (_size > 0) {
        _elements = new T[_size];
        for (unsigned int i = 0; i < _size; ++i) {
            _elements[i] = other._elements[i];
        }
    }
}

template <typename T>
Array<T>::~Array() {
    delete[] _elements;
}

// Strong exception guarantee via copy-and-swap
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        Array tmp(other); // may throw, but *this is unchanged if it does
        swap(tmp);        // no-throw: just pointer/size swap
    }
    return *this;
}

template <typename T>
void Array<T>::swap(Array& other) {
    T* ptr = _elements;
    _elements = other._elements;
    other._elements = ptr;

    unsigned int sz = _size;
    _size = other._size;
    other._size = sz;
}

// Bounds-checked access
template <typename T>
T& Array<T>::operator[](unsigned int i) {
    if (i >= _size) {
        throw std::out_of_range("Array: index out of range");
    }
    return _elements[i];
}

template <typename T>
const T& Array<T>::operator[](unsigned int i) const {
    if (i >= _size) {
        throw std::out_of_range("Array: index out of range");
    }
    return _elements[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}

#endif // ARRAY_TPP