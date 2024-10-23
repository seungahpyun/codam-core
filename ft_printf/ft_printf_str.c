/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf_util.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 14:16:08 by spyun          #+#    #+#                */
/*   Updated: 2024/10/21 14:16:10 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
