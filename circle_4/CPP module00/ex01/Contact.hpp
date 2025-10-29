/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:02:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/08/30 14:17:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

/**
 * @class Contact
 * @brief Represents a single contact in the phonebook.
 * 
 * This class stores and manages information such as first name, last name,
 * nickname, phone number, and darkest secret. It provides methods for setting 
 * and getting these fields, checking if the contact is empty, displaying the 
 * contact details, and formatting strings for display.
 */

class Contact
{
private:
   std::string firstName;
   std::string lastName;
   std::string nikname;
   std::string phoneNumber;
   std::string darkestSecret;

public:
    Contact();
    ~Contact();
    // Getters
        std::string getfirstName() const;
        std::string getlastName() const;
        std::string getnickname() const;
        std::string getphoneNumber() const;
        std::string getdarkestSecret() const;

        // Setters
        void setfirstName(const std::string& firstName);
        void setlastName(const std::string& lastName);
        void setnickname(const std::string& nickname);
        void setphoneNumber(const std::string& phoneNumber);
        void setdarkestSecret(const std::string& darkestSecret);

        // Utility methods
        bool isEmpty() const;
        void displayContact() const;
        std::string truncateField(const std::string& field) const;
};

#endif