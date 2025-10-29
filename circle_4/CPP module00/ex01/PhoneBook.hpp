/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:20:53 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/08/30 14:18:28 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include "Contact.hpp"

/**
 * @class PhoneBook
 * @brief Manages a fixed-size collection of Contact entries.
 * 
 * The PhoneBook class allows adding new contacts, searching through existing ones,
 * and displaying contact details. It supports up to 8 contacts and overwrites the 
 * oldest one when the limit is reached.
 */
class PhoneBook
{
private:
   Contact contacts[8];
   int contactCount;
   int oldestContactIndex;

public:
    PhoneBook();
    ~PhoneBook();

    void addContact(const Contact& contact);
    void searchContact() const;
    void displayContactList() const;
    void displayContactbyIndex(int index) const;
    int getContactCount() const;

};

#endif