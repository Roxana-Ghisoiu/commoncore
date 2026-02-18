/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:14:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/12 16:17:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <iterator>  // std::distance
#include <cstddef>   // std::ptrdiff_t
#include "easyfind.hpp"

template <typename C>
void printContainer(const C &c, const std::string &name) {
    std::cout << "  " << name << " = [";
    typename C::const_iterator it = c.begin();
    typename C::const_iterator end = c.end();
    while (it != end) {
        std::cout << *it;
        ++it;
        if (it != end)
            std::cout << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename C>
void testEasyFind(C &container, int value, const std::string &label) {
    std::cout << "\n[" << label << "]" << std::endl;
    printContainer(container, "container");
    std::cout << "  searching for: " << value << std::endl;

    try {
        typename C::iterator it = easyfind(container, value);
        typename C::const_iterator begin = container.begin();
        typename C::const_iterator cit = it;
        std::ptrdiff_t index = std::distance(begin, cit);

        std::cout << "  [OK] found" << std::endl;
        std::cout << "      value  = " << *it << std::endl;
        std::cout << "      index  = " << index << std::endl;

        // demonstrație: dacă containerul e ne-const, putem modifica elementul
        *it = *it; // no-op; păstrăm codul C++98 sigur fără a schimba valorile
    } catch (const std::exception &e) {
        std::cout << "  [ERROR] not found" << std::endl;
        std::cout << "      exception = " << e.what() << std::endl;
    }
}

template <typename C>
void testEasyFindConst(const C &container, int value, const std::string &label) {
    std::cout << "\n[" << label << "]" << std::endl;
    printContainer(container, "container (const)");
    std::cout << "  searching for: " << value << std::endl;

    try {
        typename C::const_iterator it = easyfind(container, value);
        std::ptrdiff_t index = std::distance(container.begin(), it);

        std::cout << "  [OK] found" << std::endl;
        std::cout << "      value  = " << *it << std::endl;
        std::cout << "      index  = " << index << std::endl;
    } catch (const std::exception &e) {
        std::cout << "  [ERROR] not found" << std::endl;
        std::cout << "      exception = " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== EASYFIND TESTS ===" << std::endl;

    // 1) vector<int> with existing and missing values
    {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);

        testEasyFind(v, 3,  "vector<int> - value in the middle");
        testEasyFind(v, 1,  "vector<int> - value at the beginning");
        testEasyFind(v, 5,  "vector<int> - value at the end");
        testEasyFind(v, 42, "vector<int> - value not found");

        const std::vector<int> cv = v;
        testEasyFindConst(cv, 3, "const vector<int> - read-only search");
    }

    // 2) list<int> with repeated values
    {
        std::list<int> lst;
        lst.push_back(10);
        lst.push_back(20);
        lst.push_back(20);
        lst.push_back(30);

        testEasyFind(lst, 20, "list<int> - repeated value (should find the first occurrence)");
        testEasyFind(lst, 30, "list<int> - unique value");
        testEasyFind(lst, 99, "list<int> - value not found");

        const std::list<int> clst = lst;
        testEasyFindConst(clst, 30, "const list<int> - read-only search");
    }

    // 3) deque<int> empty and non-empty
    {
        std::deque<int> dq;
        testEasyFind(dq, 1, "deque<int> empty - should throw an exception");

        dq.push_back(-1);
        dq.push_back(-2);
        dq.push_back(-3);

        testEasyFind(dq, -2, "deque<int> - value in the middle");
        testEasyFind(dq, 0,   "deque<int> - value not found");

        const std::deque<int> cdq = dq;
        testEasyFindConst(cdq, -3, "const deque<int> - read-only search");
    }

    std::cout << "\n=== END OF TESTS ===" << std::endl;
    return 0;
}