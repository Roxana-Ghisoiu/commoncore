/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:47:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 14:48:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Polymorphic Base with derived A, B, C and helpers generate/identify.
 */
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif