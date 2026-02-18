/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:28:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 13:46:22 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

/** @brief Default private constructor (non-instantiable). */
ScalarConverter::ScalarConverter() {}

/** @brief Private copy constructor (disabled). */
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

/** @brief Private assignment operator (disabled). */
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

/** @brief Private destructor. */
ScalarConverter::~ScalarConverter() {}

/** @brief Print 'impossible' for all four scalar types. */
static void outputImpossibleForAll() {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

/** @brief Print char conversion from a numeric value. */
static void displayCharType(double value) {
    std::cout << "char: ";
    if (std::isnan(value) || std::isinf(value)) { std::cout << "impossible" << std::endl; return; }
    if (value < 0 || value > 127) { std::cout << "impossible" << std::endl; return; }
    char c = static_cast<char>(value);
    if (value >= 32 && value <= 126) std::cout << "'" << c << "'" << std::endl;
    else std::cout << "Non displayable" << std::endl;
}

/** @brief Print int conversion from a numeric value. */
static void displayIntType(double value) {
    std::cout << "int: ";
    if (std::isnan(value) || std::isinf(value) ||
        value < std::numeric_limits<int>::min() ||
        value > std::numeric_limits<int>::max()) {
        std::cout << "impossible" << std::endl; return;
    }
    std::cout << static_cast<int>(value) << std::endl;
}

/** @brief Print float conversion with required formatting. */
static void displayFloatType(float value) {
    std::cout << "float: ";
    if (std::isnan(value)) std::cout << "nanf" << std::endl;
    else if (std::isinf(value)) std::cout << (value > 0 ? "+inff" : "-inff") << std::endl;
    else std::cout << std::fixed << std::setprecision(1) << value << "f" << std::endl;
}

/** @brief Print double conversion with required formatting. */
static void displayDoubleType(double value) {
    std::cout << "double: ";
    if (std::isnan(value)) std::cout << "nan" << std::endl;
    else if (std::isinf(value)) std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
    else std::cout << std::fixed << std::setprecision(1) << value << std::endl;
}

/** @brief True if literal is a single printable non-digit or a quoted char like 'a'. */
static bool checkIfChar(const std::string& s) {
    if (s.length() == 1 &&
        std::isprint(static_cast<unsigned char>(s[0])) &&
        !std::isdigit(static_cast<unsigned char>(s[0])))
        return true;
    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'' &&
        std::isprint(static_cast<unsigned char>(s[1])) &&
        !std::isdigit(static_cast<unsigned char>(s[1])))
        return true;
    return false;
}

/** @brief True if literal is a base-10 integer with optional sign. */
static bool checkIfInteger(const std::string& literal) {
    if (literal.empty()) return false;
    size_t i = 0;
    if (literal[i] == '+' || literal[i] == '-') i++;
    if (i >= literal.length()) return false;
    while (i < literal.length()) {
        if (!std::isdigit(static_cast<unsigned char>(literal[i]))) return false;
        i++;
    }
    return true;
}

/** @brief True if literal is a float: decimal notation with '.' and trailing 'f', or a float pseudo-literal. */
static bool checkIfFloatType(const std::string& literal) {
    if (literal == "nanf" || literal == "+inff" || literal == "-inff") return true;
    if (literal.length() < 2 || literal[literal.length() - 1] != 'f') return false;
    std::string body = literal.substr(0, literal.length() - 1);
    return body.find('.') != std::string::npos; // enforce decimal notation
}

/** @brief True if literal is a double: has '.' or is a double pseudo-literal. */
static bool checkIfDoubleType(const std::string& literal) {
    if (literal == "nan" || literal == "+inf" || literal == "-inf") return true;
    return (literal.find('.') != std::string::npos);
}

/**
 * @brief Convert the input literal and print it as char, int, float, and double.
 *
 * Accepted forms:
 *  - char: 'a' or a single printable non-digit
 *  - int: 0, -42, 42
 *  - float: 0.0f, -4.2f, 4.2f, plus nanf/+inff/-inff (requires '.')
 *  - double: 0.0, -4.2, 4.2, plus nan/+inf/-inf
 * Prints "Non displayable" for non-printable char and "impossible" when a conversion cannot be performed.
 */
void ScalarConverter::convert(const std::string& literal) {
    if (literal.empty()) { outputImpossibleForAll(); return; }

    if (checkIfChar(literal)) {
        char c = (literal.length() == 1) ? literal[0] : literal[1];
        displayCharType(static_cast<double>(c));
        displayIntType(static_cast<double>(c));
        displayFloatType(static_cast<float>(c));
        displayDoubleType(static_cast<double>(c));
        return;
    }

    if (checkIfInteger(literal)) {
        char* end;
        errno = 0;
        long num = std::strtol(literal.c_str(), &end, 10);
        if (errno == ERANGE || *end != '\0' ||
            num < std::numeric_limits<int>::min() ||
            num > std::numeric_limits<int>::max()) {
            outputImpossibleForAll();
            return;
        }
        int i = static_cast<int>(num);
        displayCharType(static_cast<double>(i));
        displayIntType(static_cast<double>(i));
        displayFloatType(static_cast<float>(i));
        displayDoubleType(static_cast<double>(i));
        return;
    }

    if (checkIfFloatType(literal)) {
        float f;
        if (literal == "nanf") f = std::numeric_limits<float>::quiet_NaN();
        else if (literal == "+inff") f = std::numeric_limits<float>::infinity();
        else if (literal == "-inff") f = -std::numeric_limits<float>::infinity();
        else {
            std::string body = literal.substr(0, literal.length() - 1);
            char* end;
            errno = 0;
            double temp = std::strtod(body.c_str(), &end);
            if (errno == ERANGE || *end != '\0') { outputImpossibleForAll(); return; }
            f = static_cast<float>(temp);
        }
        displayCharType(static_cast<double>(f));
        displayIntType(static_cast<double>(f));
        displayFloatType(f);
        displayDoubleType(static_cast<double>(f));
        return;
    }

    if (checkIfDoubleType(literal)) {
        double d;
        if (literal == "nan") d = std::numeric_limits<double>::quiet_NaN();
        else if (literal == "+inf") d = std::numeric_limits<double>::infinity();
        else if (literal == "-inf") d = -std::numeric_limits<double>::infinity();
        else {
            char* end;
            errno = 0;
            d = std::strtod(literal.c_str(), &end);
            if (errno == ERANGE || *end != '\0') { outputImpossibleForAll(); return; }
        }
        displayCharType(d);
        displayIntType(d);
        displayFloatType(static_cast<float>(d));
        displayDoubleType(d);
        return;
    }

    outputImpossibleForAll();
}