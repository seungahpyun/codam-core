/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:31 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 15:26:50 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <unistd.h>

void	ft_pa(t_stack **stack_a, t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_b)
		return ;
	temp = *stack_a;
	*stack_a = *stack_b;
	*stack_b = (*stack_b)->next;
	(*stack_a)->next = temp;
	if (print_flag == 0)
		ft_putendl_fd("pa", STDOUT_FILENO);
}

void	ft_pb(t_stack **stack_a, t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_a)
		return ;
	temp = *stack_b;
	*stack_b = *stack_a;
	*stack_a = (*stack_a)->next;
	(*stack_b)->next = temp;
	if (print_flag == 0)
		ft_putendl_fd("pb", STDOUT_FILENO);
}
