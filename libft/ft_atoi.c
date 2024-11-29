/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 10:34:01 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 11:59:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	skip_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	check_overflow(long result, int sign, char c)
{
	long	max;
	long	min;
	long	next;

	max = 2147483647;
	min = -2147483648;
	next = (result * 10) + (c - '0');
	if (sign > 0 && next > max)
		return (-1);
	if (sign < 0 && - next < min)
		return (0);
	return (1);
}

static void	ft_error(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		sign;
	int		overflow_check;

	i = skip_whitespace(str);
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!str[i])
		ft_error();
	while (ft_isdigit(str[i]))
	{
		overflow_check = check_overflow(result, sign, str[i]);
		if (overflow_check != 1)
			ft_error();
		result = result * 10 + (str[i++] - '0');
	}
	if (str[i] != '\0')
		ft_error();
	return (sign * result);
}
