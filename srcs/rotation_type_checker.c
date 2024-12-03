/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation_type_checker.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 15:01:04 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/03 10:56:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_rotate_type_ab(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	int		moves;
	t_stack	*current_node;

	if (!stack_a || !stack_b)
		return (-1);
	current_node = stack_a;
	i = -1;
	while (current_node)
	{
		moves = ft_calc_rarb_b(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rrarrb_b(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rarrb_b(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rrarb_b(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		current_node = current_node->next;
	}
	return (i);
}

int	ft_rotate_type_ba(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	int		moves;
	t_stack	*current_node;

	if (!stack_a || !stack_b)
		return (-1);
	current_node = stack_b;
	i = -1;
	while (current_node)
	{
		moves = ft_calc_rarb_a(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rrarrb_a(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rarrb_a(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		moves = ft_calc_rrarb_a(stack_a, stack_b, current_node->nbr);
		if (moves != -1 && (i == -1 || i > moves))
			i = moves;
		current_node = current_node->next;
	}
	return (i);
}
