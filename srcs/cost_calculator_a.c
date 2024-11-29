/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost_calculator_a.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:04:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 17:23:30 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_calc_rarb_a(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = ft_find_place_a(stack_a, c);
	if (i < ft_find_index(stack_b, c))
		i = ft_find_index(stack_b, c);
	return (i);
}

int	ft_calc_rarrb_a(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_index(stack_b, c))
		i = ft_stack_size(stack_b) - ft_find_index(stack_b, c);
	i = ft_find_place_a(stack_a, c) + i;
	return (i);
}

int	ft_calc_rrarb_a(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_place_a(stack_a, c))
		i = ft_stack_size(stack_a) - ft_find_place_a(stack_a, c);
	i = ft_find_index(stack_b, c) + i;
	return (i);
}

int	ft_calc_rrarrb_a(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;
	int	j;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_place_a(stack_a, c))
		i = ft_stack_size(stack_a) - ft_find_place_a(stack_a, c);
	j = ft_stack_size(stack_b) - ft_find_index(stack_b, c);
	if ((i < j) && ft_find_index(stack_b, c))
		i = j;
	return (i);
}
