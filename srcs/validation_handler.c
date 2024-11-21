/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:47:12 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/21 10:12:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdbool.h>

bool	ft_has_duplicates(t_stack *a)
{
	t_stack	*temp;

	while (a)
	{
		temp = a->next;
		while (temp)
		{
			if (a->nbr == temp->nbr)
				return (true);
			temp = temp->next;
		}
		a = a->next;
	}
	return (false);
}

bool	ft_is_sorted(t_stack *a)
{
	int	i;

	i = a->nbr;
	while (a)
	{
		if (i > a->nbr)
			return (true);
		i = a->nbr;
		a = a->next;
	}
	return (false);
}
