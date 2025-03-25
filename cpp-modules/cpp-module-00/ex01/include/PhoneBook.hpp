/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:05:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 11:03:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
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
