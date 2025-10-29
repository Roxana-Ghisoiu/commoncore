/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:40:08 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 10:15:38 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

/**
 * @brief Default constructor for the Contact class.
 *        Initializes all contact fields to empty strings.
 */
Contact::Contact(){
        firstName = "";
        lastName = "";
        nikname = "";
        phoneNumber = "";
        darkestSecret = "";
}
/**
 * @brief Destructor for the Contact class.
 */
Contact::~Contact(){
}

/**
 * @brief Gets the first name of the contact.
 * @return The contact's first name.
 */
std::string Contact::getfirstName() 
const{
        return firstName;
    }

/**
 * @brief Gets the last name of the contact.
 * @return The contact's last name.
 */
std::string Contact::getlastName() 
const{
        return lastName;
    }

 /**
 * @brief Gets the nickname of the contact.
 * @return The contact's nickname.
 */   
std::string Contact::getnickname()
const{
    return nikname;
}

/**
 * @brief Gets the phone number of the contact.
 * @return The contact's phone number.
 */
std::string Contact::getphoneNumber()
const{
    return phoneNumber;
}

/**
 * @brief Gets the darkest secret of the contact.
 * @return The contact's darkest secret.
 */
std::string Contact::getdarkestSecret() 
const{
    return darkestSecret;
}

/**
 * @brief Sets the first name of the contact.
 * @param firstName The new first name to set.
 */
void Contact::setfirstName(const std::string& firstName){
    this->firstName = firstName;
}

/**
 * @brief Sets the last name of the contact.
 * @param lastName The new last name to set.
 */
void Contact::setlastName(const std::string& lastName) {
        this->lastName = lastName;
}

/**
 * @brief Sets the last name of the contact.
 * @param lastName The new last name to set.
 */
void Contact::setnickname(const std::string& nickname) {
        this->nikname = nickname;
}

/**
 * @brief Sets the phone number of the contact.
 * @param phoneNumber The new phone number to set.
 */
void Contact::setphoneNumber(const std::string& phoneNumber) {
        this->phoneNumber = phoneNumber;
}


/**
 * @brief Sets the darkest secret of the contact.
 * @param darkestSecret The new darkest secret to set.
 */
void Contact::setdarkestSecret(const std::string& darkestSecret) {
        this->darkestSecret = darkestSecret;
}

/**
 * @brief Checks if all fields of the contact are empty.
 * @return true if all fields are empty, false otherwise.
 */
bool Contact::isEmpty() const {
        return firstName.empty() && lastName.empty() && nikname.empty() &&
                   phoneNumber.empty() && darkestSecret.empty();
}

/**
 * @brief Displays all fields of the contact in full detail.
 */
void Contact::displayContact() const {
        std::cout << "First Name: " << firstName << std::endl;
        std::cout << "Last Name: " << lastName << std::endl;
        std::cout << "nickname: " << nikname << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}

/**
 * @brief Truncates a string field to 10 characters for formatted display.
 *        If the field is longer than 10 characters, the last character is replaced with '.'.
 * @param field The original string to be truncated.
 * @return The truncated string.
 */
std::string Contact::truncateField(const std::string& field) const {
        if (field.length() <= 10)
                return field;
        return field.substr(0, 9) + ".";
}