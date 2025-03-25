/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:06:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 10:55:52 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>

PhoneBook::PhoneBook()
{
	_numContacts = 0;
}

void PhoneBook::addContact(Contact contact)
{
	if (_numContacts < 8)
	{
		_contacts[_numContacts] = contact;
		_numContacts++;
	}
}

void PhoneBook::displayContacts()
{
	std::cout << "     index|first name| last name|  nickname" << std::endl;
	for (int i = 0; i < _numContacts; i++)
	{
		std::cout << std::setw(10) << i + 1 << "|";
		std::cout << std::setw(10) << _contacts[i].getFirstName().substr(0, 10) << "|";
		std::cout << std::setw(10) << _contacts[i].getLastName().substr(0, 10) << "|";
		std::cout << std::setw(10) << _contacts[i].getNickname().substr(0, 10) << std::endl;
	}
}

void PhoneBook::displayContact(int index)
{
	if (index >= 1 && index <= _numContacts)
	{
		std::cout << "First name: " << _contacts[index - 1].getFirstName() << std::endl;
		std::cout << "Last name: " << _contacts[index - 1].getLastName() << std::endl;
		std::cout << "Nickname: " << _contacts[index - 1].getNickname() << std::endl;
		std::cout << "Mobile number: " << _contacts[index - 1].getMobileNumber() << std::endl;
		std::cout << "Darkest secret: " << _contacts[index - 1].getDarkestSecret() << std::endl;
	}
	else
	{
		std::cout << "Invalid index" << std::endl;
	}
}
