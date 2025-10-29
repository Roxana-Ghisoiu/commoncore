/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 12:53:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Cat.hpp
 * @brief Cat for Module 04 — ex01 (composed with Brain*).
 */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <cstddef>
# include <string>

class Cat : public Animal {
private:
    Brain* _brain;

public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    virtual ~Cat();

    virtual void makeSound() const;

    const std::string& getIdea(std::size_t index) const;
    void setIdea(std::size_t index, const std::string& idea);
};

#endif