/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:47:12 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/03 09:11:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdbool.h>
#include <limits.h>

bool	ft_has_duplicates(t_stack *stack)
{
	t_stack	*temp;

	while (stack)
	{
		temp = stack->next;
		while (temp)
		{
			if (stack->nbr == temp->nbr)
				return (true);
			temp = temp->next;
		}
		stack = stack->next;
	}
	return (false);
}

bool	ft_is_sorted(t_stack *stack)
{
	int	i;

	if (!stack)
		return (true);
	i = stack->nbr;
	while (stack)
	{
		if (i > stack->nbr)
			return (false);
		i = stack->nbr;
		stack = stack->next;
	}
	return (true);
}

bool	ft_is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	while (str[i] == ' ')
		i++;
	return (str[i] == '\0');
}

bool	ft_is_int_range(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= sign;
	return (num <= INT_MAX && num >= INT_MIN);
}
