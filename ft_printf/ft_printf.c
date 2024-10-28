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

// #include <stdio.h>
// #include <limits.h>
// #include <stdint.h>
// int	main(void)
// {
// 	uint64_t *c = NULL;
// 	int *ptr = NULL;
// 	char *c = NULL;

// 	ft_printf("write % write\n");
// 	printf("write % write\n\n");

// 	ft_printf("write %% write\n");
// 	printf("write %% write\n\n");

// 	ft_printf("%x\n", 123456);
// 	printf("%x\n\n", 123456);

// 	ft_printf("%x %d %c\n", 123456, 123456, 'a');
// 	printf("%x %d %c\n\n", 123456, 123456, 'a');

// 	ft_printf("%d\n", INT_MIN);
// 	printf("%d\n\n", INT_MIN);

// 	ft_printf("%d\n", INT_MAX);
// 	printf("%d\n\n", INT_MAX);

// 	ft_printf("%u\n", -42);
// 	printf("%u\n\n", -42);

// 	ft_printf("%p\n", ptr);
// 	printf("%p\n\n", ptr);

// 	ft_printf("%p\n", c);
// 	printf("%p\n\n", c);

// 	ft_printf("%d\n", 0);
// 	printf("%d\n\n", 0);

// 	ft_printf("%p\n",NULL);
// 	printf("%p\n\n",NULL);

// 	ft_printf("%s\n",NULL);
// 	printf("%s\n\n",NULL);

// 	ft_printf("%c\n",c);
// 	printf("%c\n\n",c);

// 	ft_printf(NULL);
// 	printf(NULL);
// 	//cc *.c -L./libft -lft -o ft_printf_program
// }
