/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:15:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/12 12:23:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef> // for std::size_t

template <typename T, typename F>
void iter(T* array, const std::size_t len, F const& func) {
    if (!array || len == 0) return;
    for (std::size_t i = 0; i < len; ++i) {
        func(array[i]); // T& for non-const array
    }
}

template <typename T, typename F>
void iter(T const* array, const std::size_t len, F const& func) {
    if (!array || len == 0) return;
    for (std::size_t i = 0; i < len; ++i) {
        func(array[i]); // const T& for const array
    }
}

#endif