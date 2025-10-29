/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:27:24 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/08/30 14:19:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

/**
 * @brief Constructs a new PhoneBook object.
 *        Initializes contact count and oldest contact index.
 */
PhoneBook::PhoneBook() {
	contactCount = 0;
	oldestContactIndex = 0;
}

/**
 * @brief Destroys the PhoneBook object.
 */
PhoneBook::~PhoneBook() {
}

/**
 * @brief Adds a new contact to the phonebook.
 *        If the phonebook is full (8 contacts), the oldest contact is overwritten.
 * 
 * @param contact The new contact to add.
 */
void PhoneBook::addContact(const Contact& contact) {
	if (contactCount < 8) {
		contacts[contactCount] = contact;
		contactCount++;
	} else {
		contacts[oldestContactIndex] = contact;
		oldestContactIndex = (oldestContactIndex + 1) % 8;
	}
}

/**
 * @brief Prompts the user to search and display a contact by index.
 *        If no contacts are available, it prints a warning.
 */
void PhoneBook::searchContact() const {
	if (contactCount == 0) {
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	displayContactList();

	std::cout << "Enter the index of the contact to display: ";
	int index;
	std::cin >> index;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input!" << std::endl;
		return;
	}

	if (index >= 0 && index < contactCount) {
		displayContactbyIndex(index);
	} else {
		std::cout << "Index out of range!" << std::endl;
	}
}

/**
 * @brief Displays a formatted list of all contacts in the phonebook.
 *        Only shows index, first name, last name, and nickname (truncated).
 */
void PhoneBook::displayContactList() const {
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	std::cout << "----------|----------|----------|----------" << std::endl;

	for (int i = 0; i < contactCount; i++) {
		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10) << contacts[i].truncateField(contacts[i].getfirstName()) << "|";
		std::cout << std::setw(10) << contacts[i].truncateField(contacts[i].getlastName()) << "|";
		std::cout << std::setw(10) << contacts[i].truncateField(contacts[i].getnickname()) << std::endl;
	}
}

/**
 * @brief Displays full details of a specific contact by index.
 * 
 * @param index The index of the contact to display.
 */
void PhoneBook::displayContactbyIndex(int index) const {
	if (index >= 0 && index < contactCount) {
		contacts[index].displayContact();
	}
}

/**
 * @brief Returns the number of contacts currently stored in the phonebook.
 * 
 * @return The number of contacts.
 */
int PhoneBook::getContactCount() const {
	return contactCount;
}