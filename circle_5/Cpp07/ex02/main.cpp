/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:53:02 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/12 12:53:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Array.hpp"

template <typename T>
void printArray(const Array<T>& a, const char* name) {
    std::cout << name << " (size=" << a.size() << "): ";
    for (unsigned int i = 0; i < a.size(); ++i) {
        std::cout << a[i] << (i + 1 < a.size() ? " " : "");
    }
    std::cout << std::endl;
}

int main() {
    try {
        std::cout << "=== Default construction ===\n";
        Array<int> a0;
        std::cout << "a0.size() = " << a0.size() << std::endl;

        std::cout << "\n=== Sized construction & default values ===\n";
        Array<int> a1(5); // value-initialized => 0s for ints
        printArray(a1, "a1");

        std::cout << "\n=== Write & read via operator[] ===\n";
        for (unsigned int i = 0; i < a1.size(); ++i) {
            a1[i] = static_cast<int>(i * 10);
        }
        printArray(a1, "a1 (after writes)");

        std::cout << "\n=== Copy construction (deep copy) ===\n";
        Array<int> a2(a1);
        printArray(a2, "a2 (copy of a1)");
        a1[0] = 999; // change original
        std::cout << "After a1[0]=999 -> a1[0]=" << a1[0]
                  << ", a2[0]=" << a2[0] << " (should remain old value)\n";

        std::cout << "\n=== Assignment (deep copy) ===\n";
        Array<int> a3;
        a3 = a1;
        printArray(a3, "a3 (assigned from a1)");
        a1[1] = 777; // change source, a3 must not change
        std::cout << "After a1[1]=777 -> a1[1]=" << a1[1]
                  << ", a3[1]=" << a3[1] << " (should remain old value)\n";

        std::cout << "\n=== Self-assignment safety ===\n";
        a3 = a3; // should be a no-op
        printArray(a3, "a3 (after self-assign)");

        std::cout << "\n=== Const correctness ===\n";
        const Array<int> ac(a1);
        std::cout << "ac.size() = " << ac.size() << std::endl;
        if (ac.size() > 0) {
            std::cout << "ac[0] (read-only) = " << ac[0] << std::endl;
        }

        std::cout << "\n=== Strings (non-POD types) ===\n";
        Array<std::string> s(3);
        s[0] = "hello";
        s[1] = "array";
        // s[2] remains default-initialized to ""
        printArray(s, "s");

        std::cout << "\n=== Out-of-bounds exceptions ===\n";
        try {
            std::cout << "Accessing a1[999]...\n";
            std::cout << a1[999] << std::endl; // should throw
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        try {
            std::cout << "Writing a0[0] on empty array...\n";
            a0[0] = 42; // should throw (size==0)
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "\nUnexpected error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}