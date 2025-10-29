/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:54:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 11:30:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Brain.hpp
 * @brief Declaration of the Brain class used by Dog and Cat.
 *
 * The Brain class stores an array of 100 std::string called ideas.
 * - It follows the Rule of Three: copy constructor, copy-assignment operator,
 *   and destructor must be implemented.
 * - Constructors and destructor must display specific messages (in Brain.cpp).
 * - Dog and Cat will have a private Brain* attribute.
 *   They allocate it with new Brain() and delete it in their destructor.
 * - Copying a Dog or Cat must perform a deep copy of its Brain.
 */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>
# include <cstddef>  //for size_t

class Brain {
    private:
        std::string _ideas[100];

    public:
        Brain();
        Brain(const Brain& other);
        Brain& operator=(const Brain& other);
        ~Brain();

        const std::string& getIdea(std::size_t index) const;
        void setIdea(std::size_t index, const std::string& idea);
};

#endif