/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:41:11 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 10:15:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>

/**
 * @brief Prompts the user with a message and reads a line of input.
 * 
 * @param prompt The message to display before input.
 * @return The user input as a string.
 */
std::string getInput(const std::string& prompt) {
	std::string input;
	std::cout << prompt;
	std::getline(std::cin, input);
	return input;
}

/**
 * @brief Creates a new Contact by prompting the user for each field.
 * 
 * @return A fully initialized Contact object.
 */
Contact createContact() {
	Contact contact;

	contact.setfirstName(getInput("Enter first name: "));
	contact.setlastName(getInput("Enter last name: "));
	contact.setnickname(getInput("Enter nickname: "));
	contact.setphoneNumber(getInput("Enter phone number: "));
	contact.setdarkestSecret(getInput("Enter darkest secret: "));

	return contact;
}

/**
 * @brief Entry point of the program.
 * 
 * Initializes the PhoneBook and processes user commands (ADD, SEARCH, EXIT).
 * 
 * @return 0 on successful exit.
 */
int main() {
	PhoneBook phonebook;
	std::string command;

	std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;
	std::cout << "Available commands:\n"
	          << "\033[32mADD\033[0m\n"
	          << "\033[33mSEARCH\033[0m\n"
	          << "\033[31mEXIT\033[0m\n";

	while (true) {
		command = getInput("Enter command: ");

		if (command == "ADD") {
			Contact newContact = createContact();
			phonebook.addContact(newContact);
			std::cout << "Contact added successfully!" << std::endl;
		}
		else if (command == "SEARCH") {
			phonebook.searchContact();
		}
		else if (command == "EXIT") {
			std::cout << "Goodbye! Contacts are lost forever!" << std::endl;
			break;
		}
		else {
			std::cout << "Use ADD, SEARCH, or EXIT." << std::endl;
		}
	}
	return 0;
}
