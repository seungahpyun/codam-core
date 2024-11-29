/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:27:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 15:20:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_find_index(t_stack *stack, long nbr)
{
	int		i;

	if (!stack)
		return (0);
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
	t_stack	*next_node;

	if (!stack_a)
		return (0);
	i = 1;
	if (nbr_push < stack_a->nbr && nbr_push > ft_stack_last(stack_a)->nbr)
		i = 0;
	else if (nbr_push > ft_max(stack_a) || nbr_push < ft_min(stack_a))
		i = ft_find_index(stack_a, ft_min(stack_a));
	else
	{
		next_node = stack_a->next;
		if (!next_node)
			return (i);
		while (stack_a->nbr > nbr_push || next_node->nbr < nbr_push)
		{
			stack_a = stack_a->next;
			next_node = stack_a->next;
			if (!next_node)
				break ;
			i++;
		}
	}
	return (i);
}

int	ft_find_place_b(t_stack *stack_b, int nbr_push)
{
	int		i;
	t_stack	*next_node;

	if (!stack_b)
		return (0);
	i = 1;
	if (nbr_push > stack_b->nbr && nbr_push < ft_stack_last(stack_b)->nbr)
		i = 0;
	else if (nbr_push > ft_max(stack_b) || nbr_push < ft_min(stack_b))
		i = ft_find_index(stack_b, ft_max(stack_b));
	else
	{
		next_node = stack_b->next;
		if (!next_node)
			return (i);
		while (stack_b->nbr < nbr_push || next_node->nbr > nbr_push)
		{
			stack_b = stack_b->next;
			next_node = stack_b->next;
			if (!next_node)
				break ;
			i++;
		}
	}
	return (i);
}

int	ft_min(t_stack *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = stack->nbr;
	while (stack)
	{
		if (stack->nbr < min)
			min = stack->nbr;
		stack = stack->next;
	}
	return (min);
}

int	ft_max(t_stack *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = stack->nbr;
	while (stack)
	{
		if (stack->nbr > max)
			max = stack->nbr;
		stack = stack->next;
	}
	return (max);
}
