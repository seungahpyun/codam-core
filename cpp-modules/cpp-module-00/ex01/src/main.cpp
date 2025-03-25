/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:06:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 11:37:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <limits>

void addContact(PhoneBook &phoneBook)
{
	Contact contact;
	std::string firstName, lastName, nickname, mobileNumber, darkest;

	std::cout << "Enter first name: ";
	std::getline(std::cin, firstName);
	contact.setFirstName(firstName);

	std::cout << "Enter last name: ";
	std::getline(std::cin, lastName);
	contact.setLastName(lastName);

	std::cout << "Enter nickname: ";
	std::getline(std::cin, nickname);
	contact.setNickname(nickname);

	std::cout << "Enter mobile number: ";
	std::getline(std::cin, mobileNumber);
	contact.setMobileNumber(mobileNumber);

	std::cout << "Enter darkest secret: ";
	std::getline(std::cin, darkest);
	contact.setDarkestSecret(darkest);

	phoneBook.addContact(contact);
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
