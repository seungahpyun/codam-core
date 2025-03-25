/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:05:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 16:06:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iomanip>
#include <limits>
#include <algorithm>
#include <string>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

class PhoneBook
{
	private:
		Contact _contacts[8];
		int _numContacts;
	public:
		PhoneBook();
		void addContact(Contact contact);
		void displayContacts();
		void displayContact(int index);
};

bool		isValidNumber(const std::string &number);
bool		isValidName(const std::string &name);
std::string	getValidInput(const std::string &command, bool (*validator)(const std::string &));
#endif
