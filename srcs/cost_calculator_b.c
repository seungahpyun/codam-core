/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost_calculator_b.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 17:21:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_calc_rarb_b(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = ft_find_place_b(stack_b, c);
	if (i < ft_find_index(stack_a, c))
		i = ft_find_index(stack_a, c);
	return (i);
}

int	ft_calc_rarrb_b(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_place_b(stack_b, c))
		i = ft_stack_size(stack_b) - ft_find_place_b(stack_b, c);
	i = ft_find_index(stack_a, c) + i;
	return (i);
}

int	ft_calc_rrarb_b(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_index(stack_a, c))
		i = ft_stack_size(stack_a) - ft_find_index(stack_a, c);
	i = ft_find_place_b(stack_b, c) + i;
	return (i);
}

int	ft_calc_rrarrb_b(t_stack *stack_a, t_stack *stack_b, int c)
{
	int	i;
	int	j;

	if (!stack_a || !stack_b)
		return (0);
	i = 0;
	if (ft_find_place_b(stack_b, c))
		i = ft_stack_size(stack_b) - ft_find_place_b(stack_b, c);
	j = ft_stack_size(stack_a) - ft_find_index(stack_a, c);
	if ((i < j) && ft_find_index(stack_a, c))
		i = j;
	return (i);
}
