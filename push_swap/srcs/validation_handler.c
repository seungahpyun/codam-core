/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:47:12 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/02 08:28:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdbool.h>

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

bool	is_valid_number(char *str)
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
