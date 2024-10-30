/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 09:16:49 by spyun          #+#    #+#                */
/*   Updated: 2024/10/21 09:16:50 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list args, const char format)
{
	int	printed_chars;

	printed_chars = 0;
	if (format == 'c')
		printed_chars += ft_print_char(va_arg(args, int));
	else if (format == 's')
		printed_chars += ft_print_string(args);
	else if (format == 'p')
		printed_chars += ft_print_pointer(args);
	else if (format == 'd' || format == 'i')
		printed_chars += ft_print_int(args);
	else if (format == 'u')
		printed_chars += ft_print_unsigned_int(args);
	else if (format == 'x')
		printed_chars += ft_print_hex_lower(args);
	else if (format == 'X')
		printed_chars += ft_print_hex_upper(args);
	else if (format == '%')
		printed_chars += ft_print_char('%');
	else
	{
		printed_chars += ft_print_char('%');
		printed_chars += ft_print_char(format);
	}
	return (printed_chars);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		printed_chars;

	printed_chars = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str)
				printed_chars += ft_formats(args, *str);
			else
				return (-1);
		}
		else
			printed_chars += ft_print_char(*str);
		str++;
	}
	va_end(args);
	return (printed_chars);
}
