/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:27:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 11:28:27 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_find_index(t_stack *stack, long nbr)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->nbr == nbr)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

int	ft_find_place_a(t_stack *a, long c)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->nbr < c)
			return (i);
		a = a->next;
		i++;
	}
	return (i);
}

int	ft_find_place_b(t_stack *b, long c)
{
	int	i;

	i = 0;
	while (b)
	{
		if (b->nbr > c)
			return (i);
		b = b->next;
		i++;
	}
	return (i);
}

int ft_min(t_stack *a)
{
	int min;

	min = a->nbr;
	while (a)
	{
		if (a->nbr < min)
			min = a->nbr;
		a = a->next;
	}
	return (min);
}

int ft_max(t_stack *a)
{
	int max;

	max = a->nbr;
	while (a)
	{
		if (a->nbr > max)
			max = a->nbr;
		a = a->next;
	}
	return (max);
}
