#ifndef SED_HPP
#define SED_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <string>

/**@brief Declares the sed_replace function used to perform string replacement.
 * This header provides the prototype for the sed_replace function,
 * which takes an input string and replaces all occurrences of `from` with `to`.
 */

/** @brief Replace all occurrences of `from` with `to` in the given source string.
 * @param src The original string to process.
 * @param from The substring to search for.
 * @param to The substring to replace with.
 * @return A new string with all occurrences of `from` replaced by `to`.
 */

std::string sed_replace(const std::string& src,
                        const std::string& from,
                        const std::string& to);

#endif
