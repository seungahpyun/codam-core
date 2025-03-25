/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 10:05:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/25 10:50:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

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
