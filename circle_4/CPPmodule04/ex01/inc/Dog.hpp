/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:20:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 12:52:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Dog.hpp
 * @brief Dog for Module 04 — ex01 (composed with Brain*).
 *
 * Requirements:
 *  - Private Brain* allocated in ctor with new Brain() and deleted in dtor.
 *  - Deep copy in copy-ctor & copy-assignment (duplicate Brain content).
 *  - Ctors/dtor must print specific messages (see Dog.cpp).
 *  - Forwarders getIdea/setIdea for tests (encapsulation-friendly).
 */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <cstddef>
# include <string>

class Dog : public Animal {
private:
    Brain* _brain;

public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    virtual ~Dog();

    virtual void makeSound() const;

    const std::string& getIdea(std::size_t index) const;
    void setIdea(std::size_t index, const std::string& idea);
};

#endif