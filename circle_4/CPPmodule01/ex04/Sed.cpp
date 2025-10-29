/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:15:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 13:16:19 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

/** @brief Implements the sed_replace function.
 * The function searches for all occurrences of the string `from` inside `src`
 * and replaces them with `to`. The result is returned as a new string.
 * If `from` is empty, the original string is returned unchanged.
 */

std::string sed_replace(const std::string& src,
                        const std::string& from,
                        const std::string& to)
{
    if (from.empty())
        return src;

    std::string out;
    out.reserve(src.size());
    std::string::size_type pos = 0;

    while (true) {
        std::string::size_type found = src.find(from, pos);
        if (found == std::string::npos) {
            out.append(src, pos, std::string::npos);
            break;
        }
        out.append(src, pos, found - pos);
        out.append(to);
        pos = found + from.size();
    }
    return out;
}
