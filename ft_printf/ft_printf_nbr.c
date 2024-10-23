/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf_nbr.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 17:12:24 by spyun          #+#    #+#                */
/*   Updated: 2024/10/21 17:12:34 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_num_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static size_t	ft_unsigned_num_len(unsigned int n)
{
	size_t	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_unsigned_putnbr_fd(unsigned int n, int fd)
{
	if (n >= 10)
		ft_unsigned_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

int	ft_print_int(va_list args)
{
	int	nbr;

	nbr = va_arg(args, int);
	ft_putnbr_fd(nbr, 1);
	return (ft_num_len(nbr));
}

int	ft_print_unsigned_int(va_list args)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	ft_unsigned_putnbr_fd(nbr, 1);
	return (ft_unsigned_num_len(nbr));
}
