/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixedPointNumbers.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:24:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 16:45:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP
#include <string>
#include <iostream>

class Fixed
{
private:
    int _value;
    static const int _fractionalBits;
public:
    Fixed();
    Fixed(const Fixed& source);
    Fixed& operator = (const Fixed& other);
     ~Fixed();

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif