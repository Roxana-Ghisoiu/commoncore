/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:15:43 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/12 12:15:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

// Read-only action
template <typename T>
void print(const T& item) {
    std::cout << item << std::endl;
}

// Mutating action (non-const arrays only)
template <typename T>
void increment(T& item) {
    ++item;
}

void appendX(std::string& s) {
    s += "_X";
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    const int arr2[] = {5, 6, 7, 8};
    std::string arr3[] = {"ab", "cd", "ef", "gh", "ij"};
    const std::string arr4[] = {"ab", "cd", "ef", "gh", "ij"};

    // Print arr1
    iter(arr1, 4, print<int>);
    std::cout << std::endl;

    // Increment then print arr1
    iter(arr1, 4, increment<int>);
    iter(arr1, 4, print<int>);
    std::cout << std::endl;

    // Print arr2 (const)
    iter(arr2, 4, print<int>);
    std::cout << std::endl;

    // Print arr3
    iter(arr3, 5, print<std::string>);
    std::cout << std::endl;

    // Append then print arr3
    iter(arr3, 3, appendX);
    iter(arr3, 5, print<std::string>);
    std::cout << std::endl;

    // Print arr4 (const)
    iter(arr4, 5, print<std::string>);
}