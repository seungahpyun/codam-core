/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf_ptr.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 15:36:58 by spyun          #+#    #+#                */
/*   Updated: 2024/10/21 15:37:00 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

static void	ft_print_hex(uintptr_t num, int uppercase)
{
	if (num >= 16)
	{
		ft_print_hex(num / 16, uppercase);
		ft_print_hex(num % 16, uppercase);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd(num + '0', 1);
		else
		{
			if (uppercase)
				ft_putchar_fd(num - 10 + 'A', 1);
			else
				ft_putchar_fd(num - 10 + 'a', 1);
		}
	}
}

static size_t	ft_hex_len(uintptr_t num)
{
	size_t	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 16;
		length++;
	}
	return (length);
}

int	ft_print_hex_lower(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	ft_print_hex(num, 0);
	return (ft_hex_len(num));
}

int	ft_print_hex_upper(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	ft_print_hex(num, 1);
	return (ft_hex_len(num));
}

int	ft_print_pointer(va_list args)
{
	void				*ptr;
	uintptr_t			address;
	int					printed_chars;

	ptr = va_arg(args, void *);
	address = (uintptr_t)ptr;
	if (address == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	printed_chars = 2;
	ft_print_hex(address, 0);
	printed_chars += ft_hex_len(address);
	return (printed_chars);
}
