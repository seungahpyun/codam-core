/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation_applier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 14:17:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/02 08:35:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_apply_rarb(t_stack **stack_a, t_stack **stack_b, int c, char s)
{
	if (!stack_a || !stack_b || !*stack_a || !*stack_b)
		return (-1);
	if (s == 'a')
	{
		while ((*stack_a)->nbr != c && ft_find_place_b(*stack_b, c) > 0)
			ft_rr(stack_a, stack_b, 0);
		while ((*stack_a)->nbr != c)
			ft_ra(stack_a, 0);
		while (ft_find_place_b(*stack_b, c) > 0)
			ft_rb(stack_b, 0);
		ft_pb(stack_a, stack_b, 0);
	}
	else
	{
		while ((*stack_b)->nbr != c && ft_find_place_a(*stack_a, c) > 0)
			ft_rr(stack_a, stack_b, 0);
		while ((*stack_b)->nbr != c)
			ft_rb(stack_b, 0);
		while (ft_find_place_a(*stack_a, c) > 0)
			ft_ra(stack_a, 0);
		ft_pa(stack_a, stack_b, 0);
	}
	return (-1);
}

int	ft_apply_rarrb(t_stack **stack_a, t_stack **stack_b, int c, char s)
{
	if (!stack_a || !stack_b || !*stack_a)
		return (-1);
	if (s == 'a')
	{
		while ((*stack_a)->nbr != c)
			ft_ra(stack_a, 0);
		while (ft_find_place_b(*stack_b, c) > 0)
			ft_rrb(stack_b, 0);
		ft_pb(stack_a, stack_b, 0);
	}
	else
	{
		while (ft_find_place_a(*stack_a, c) > 0)
			ft_ra(stack_a, 0);
		while ((*stack_b)->nbr != c)
			ft_rrb(stack_b, 0);
		ft_pa(stack_a, stack_b, 0);
	}
	return (-1);
}

int	ft_apply_rrarb(t_stack **stack_a, t_stack **stack_b, int c, char s)
{
	if (!stack_a || !stack_b || !*stack_a || !*stack_b)
		return (-1);
	if (s == 'a')
	{
		while ((*stack_a)->nbr != c)
			ft_rra(stack_a, 0);
		while (ft_find_place_b(*stack_b, c) > 0)
			ft_rb(stack_b, 0);
		ft_pb(stack_a, stack_b, 0);
	}
	else
	{
		while (ft_find_place_a(*stack_a, c) > 0)
			ft_rra(stack_a, 0);
		while ((*stack_b)->nbr != c)
			ft_rb(stack_b, 0);
		ft_pa(stack_a, stack_b, 0);
	}
	return (-1);
}

int	ft_apply_rrarrb(t_stack **stack_a, t_stack **stack_b, int c, char s)
{
	if (!stack_a || !stack_b || !*stack_a || !*stack_b)
		return (-1);
	if (s == 'a')
	{
		while ((*stack_a)->nbr != c && ft_find_place_b(*stack_b, c) > 0)
			ft_rrr(stack_a, stack_b, 0);
		while ((*stack_a)->nbr != c)
			ft_rra(stack_a, 0);
		while (ft_find_place_b(*stack_b, c) > 0)
			ft_rrb(stack_b, 0);
		ft_pb(stack_a, stack_b, 0);
	}
	else
	{
		while ((*stack_b)->nbr != c && ft_find_place_a(*stack_a, c) > 0)
			ft_rr(stack_a, stack_b, 0);
		while ((*stack_b)->nbr != c)
			ft_rrb(stack_b, 0);
		while (ft_find_place_a(*stack_a, c) > 0)
			ft_rra(stack_a, 0);
		ft_pa(stack_a, stack_b, 0);
	}
	return (-1);
}
