/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:27:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 09:32:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_find_index(t_stack *stack, long nbr)
{
	int		i;

	i = 0;
	while (stack->nbr != nbr)
	{
		i++;
		stack = stack->next;
	}
	stack->index = 0;
	return (i);
}

int	ft_find_place_a(t_stack *stack_a, int nbr_push)
{
	int		i;
	t_stack	*tmp;

	i = 1;
	if (nbr_push < stack_a->nbr && nbr_push > ft_stack_last(stack_a)->nbr)
		i = 0;
	else if (nbr_push > ft_max(stack_a) || nbr_push < ft_min(stack_a))
		i = ft_find_index(stack_a, ft_min(stack_a));
	else
	{
		tmp = stack_a->next;
		while (stack_a->nbr > nbr_push || tmp->nbr < nbr_push)
		{
			stack_a = stack_a->next;
			tmp = stack_a->next;
			i++;
		}
	}
	return (i);
}

int	ft_find_place_b(t_stack *stack_b, int nbr_push)
{
	int		i;
	t_stack	*tmp;

	i = 1;
	if (nbr_push > stack_b->nbr && nbr_push < ft_stack_last(stack_b)->nbr)
		i = 0;
	else if (nbr_push > ft_max(stack_b) || nbr_push < ft_min(stack_b))
		i = ft_find_index(stack_b, ft_max(stack_b));
	else
	{
		tmp = stack_b->next;
		while (stack_b->nbr < nbr_push || tmp->nbr > nbr_push)
		{
			stack_b = stack_b->next;
			tmp = stack_b->next;
			i++;
		}
	}
	return (i);
}

int	ft_min(t_stack *a)
{
	int	min;

	min = a->nbr;
	while (a)
	{
		if (a->nbr < min)
			min = a->nbr;
		a = a->next;
	}
	return (min);
}

int	ft_max(t_stack *a)
{
	int	max;

	max = a->nbr;
	while (a)
	{
		if (a->nbr > max)
			max = a->nbr;
		a = a->next;
	}
	return (max);
}
