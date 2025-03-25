/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:06:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 10:59:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main ()
{
	PhoneBook phoneBook;
	std::string command;
	while (1)
	{
		std::cout << "Enter a command: ";
		std::cin >> command;
		if (command == "ADD")
		{
			Contact contact;
			std::string firstName;
			std::string lastName;
			std::string nickname;
			std::string mobileNumber;
			std::string darkestSecret;
			std::cout << "Enter first name: ";
			std::cin >> firstName;
			contact.setFirstName(firstName);
			std::cout << "Enter last name: ";
			std::cin >> lastName;
			contact.setLastName(lastName);
			std::cout << "Enter nickname: ";
			std::cin >> nickname;
			contact.setNickname(nickname);
			std::cout << "Enter mobile number: ";
			std::cin >> mobileNumber;
			contact.setMobileNumber(mobileNumber);
			std::cout << "Enter darkest secret: ";
			std::cin >> darkestSecret;
			contact.setDarkestSecret(darkestSecret);
			phoneBook.addContact(contact);
		}
		else if (command == "SEARCH")
		{
			phoneBook.displayContacts();
			int index;
			std::cout << "Enter index: ";
			std::cin >> index;
			phoneBook.displayContact(index);
		}
		else if (command == "EXIT")
		{
			break ;
		}
		else
		{
			std::cout << "Invalid command" << std::endl;
		}
	}
	return 0;
}
