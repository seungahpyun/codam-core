/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:06:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 12:06:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void addContact(PhoneBook &phoneBook)
{
	Contact contact;

	std::string firstName = getValidInput("Enter first name: ", isValidName);
	contact.setFirstName(firstName);

	std::string lastName = getValidInput("Enter last name: ", isValidName);
	contact.setLastName(lastName);

	std::string nickname = getValidInput("Enter nickname: ", [](const std::string &str) { return !str.empty(); });
	contact.setNickname(nickname);

	std::string mobileNumber = getValidInput("Enter mobile number: ", isValidNumber);
	contact.setMobileNumber(mobileNumber);

	std::string darkest = getValidInput("Enter darkest secret: ", [](const std::string &str) { return !str.empty(); });
	contact.setDarkestSecret(darkest);

	phoneBook.addContact(contact);
	std::cout << GREEN << "Contact added successfully!" << RESET << std::endl;
}

void searchContact(PhoneBook &phoneBook)
{
	phoneBook.displayContacts();
	std::string strIndex;
	std::cout << "Enter index: ";
	std::getline(std::cin, strIndex);
	try
	{
		int index = std::stoi(strIndex);
		phoneBook.displayContact(index);
	}
	catch (std::exception &e)
	{
		std::cout << RED << "Invalid index" << RESET << std::endl;
	}
}

int main ()
{
	PhoneBook phoneBook;
	std::string command;
	std::cout << "Welcome to the phone book!" << std::endl;
	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	while (1 && !std::cin.eof())
	{
		std::cout << "Enter a command: ";
		std::getline(std::cin, command);
		if (command == "ADD")
		{
			addContact(phoneBook);
		}
		else if (command == "SEARCH")
		{
			searchContact(phoneBook);
		}
		else if (command == "EXIT")
		{
			break ;
		}
		else
		{
			std::cout << RED << "Invalid command, Commands: ADD, SEARCH, EXIT"
				<< RESET << std::endl;
		}
	}
	return 0;
}
