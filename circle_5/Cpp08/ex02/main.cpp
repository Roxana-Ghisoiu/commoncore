/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 10:51:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <list>
#include "MutantStack.hpp"

/**
 * @brief Entry point for testing the MutantStack class.
 *
 * This test program demonstrates:
 * - The example behavior required by the subject.
 * - Iteration using normal iterators.
 * - Iteration using const_iterators and reverse_iterators.
 * - Copy construction and copy assignment.
 * - Comparison with std::list for equivalent iteration behavior.
 *
 * @return 0 on success, non-zero on error.
 */
int main() {
    std::cout << "== SUBJECT TEST ==" << std::endl;
    {
        MutantStack<int> mstack;

        mstack.push(5);
        mstack.push(17);
        std::cout << mstack.top() << std::endl;
        mstack.pop();
        std::cout << mstack.size() << std::endl;
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);

        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();

        ++it;
        --it;

        while (it != ite) {
            std::cout << *it << std::endl;
            ++it;
        }

        std::stack<int> s(mstack);
    }

    std::cout << "\n== CONST ITERATOR TEST ==" << std::endl;
    {
        MutantStack<int> mstack;
        for (int i = 0; i < 5; ++i)
            mstack.push(i * 10);

        const MutantStack<int> cmstack(mstack);
        MutantStack<int>::const_iterator it = cmstack.begin();
        MutantStack<int>::const_iterator ite = cmstack.end();

        while (it != ite) {
            std::cout << *it << std::endl;
            ++it;
        }
    }

    std::cout << "\n== REVERSE ITERATOR TEST ==" << std::endl;
    {
        MutantStack<std::string> mstack;
        mstack.push("first");
        mstack.push("second");
        mstack.push("third");

        MutantStack<std::string>::reverse_iterator rit = mstack.rbegin();
        MutantStack<std::string>::reverse_iterator rite = mstack.rend();

        while (rit != rite) {
            std::cout << *rit << std::endl;
            ++rit;
        }
    }

    std::cout << "\n== COPY CONSTRUCTOR AND ASSIGNMENT TEST ==" << std::endl;
    {
        MutantStack<int> original;
        original.push(1);
        original.push(2);
        original.push(3);

        MutantStack<int> copy(original);
        MutantStack<int> assigned;
        assigned = original;

        std::cout << "Original top: " << original.top() << std::endl;
        std::cout << "Copy top    : " << copy.top() << std::endl;
        std::cout << "Assigned top: " << assigned.top() << std::endl;
    }

    std::cout << "\n== COMPARISON WITH std::list ==" << std::endl;
    {
        MutantStack<int> mstack;
        std::list<int> lst;

        mstack.push(5);
        mstack.push(17);
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);

        lst.push_back(5);
        lst.push_back(17);
        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);

        std::cout << "MutantStack iteration:" << std::endl;
        for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;

        std::cout << "std::list iteration:   " << std::endl;
        for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }

    return 0;
}